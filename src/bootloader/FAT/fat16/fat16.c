#include "fat16.h"
#include "fat16_types.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Estructura para almacenar la información del sector de arranque
#pragma pack(push, 1)
typedef struct {
    uint8_t  jump[3];                // Código de salto
    char     oem[8];                 // Nombre del OEM
    uint16_t bytes_per_sector;       // Bytes por sector
    uint8_t  sectors_per_cluster;    // Sectores por cluster
    uint16_t reserved_sectors;       // Sectores reservados
    uint8_t  num_fats;               // Número de tablas FAT
    uint16_t root_entries;           // Número de entradas en el directorio raíz
    uint16_t total_sectors;          // Número total de sectores
    uint8_t  media_descriptor;       // Descriptor de medios
    uint16_t sectors_per_fat;        // Sectores por FAT
    uint16_t sectors_per_track;      // Sectores por pista
    uint16_t num_heads;              // Número de cabezas
    uint32_t hidden_sectors;         // Sectores ocultos
    uint32_t large_sectors;          // Número de sectores grandes
    uint8_t  drive_number;           // Número de unidad
    uint8_t  reserved;               // Reservado
    uint8_t  boot_signature;         // Firma de arranque
    uint32_t volume_id;              // ID del volumen
    char     volume_label[11];       // Etiqueta del volumen
    char     fs_type[8];             // Tipo de sistema de archivos
} BootSector;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    char     filename[8];            // Nombre del archivo
    char     ext[3];                 // Extensión del archivo
    uint8_t  attributes;             // Atributos del archivo
    uint8_t  reserved;               // Reservado
    uint8_t  creation_time_tenths;   // Tiempo de creación (décimas de segundo)
    uint16_t creation_time;          // Tiempo de creación
    uint16_t creation_date;          // Fecha de creación
    uint16_t last_access_date;       // Fecha del último acceso
    uint16_t first_cluster_high;     // Primer cluster alto
    uint16_t write_time;             // Tiempo de escritura
    uint16_t write_date;             // Fecha de escritura
    uint16_t first_cluster_low;      // Primer cluster bajo
    uint32_t file_size;              // Tamaño del archivo
} DirectoryEntry;
#pragma pack(pop)typedef struct {
    uint16_t entries[FAT16_MAX_CLUSTERS];  // Entradas de la tabla FAT
} FAT12Table;

int update_fat(FILE *disk, FAT16Table *fat, BootSector *boot_sector) {
    fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
    if (fwrite(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error actualizando la FAT");
        return -1;
    }
    return 0;
}int read_boot_sector(FILE *disk, BootSector *boot_sector) {
    fseek(disk, 0, SEEK_SET);
    if (fread(boot_sector, sizeof(BootSector), 1, disk) != 1) {
        perror("Error leyendo el sector de arranque");
        return -1;
    }
    return 0;
}

// Definiciones de macros
#define SECTOR_SIZE 512
#define CLUSTER_SIZE 4096
#define FAT12_MAX_CLUSTERS 4085
int create_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT16Table *fat) {
    // Buscar una entrada libre en el directorio raíz
    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (dir_entry.filename[0] == 0x00 || dir_entry.filename[0] == 0xE5) {
            // Encontrar un cluster libre en la FAT
            int free_cluster = find_free_cluster(fat);
            if (free_cluster == -1) {
                fprintf(stderr, "No hay clusters libres disponibles.\n");
                return -1;
            }

            // Marcar el cluster como final de archivo en la FAT
            fat->entries[free_cluster] = 0xFFF;

            // Crear la entrada del directorio
            memset(&dir_entry, 0, sizeof(DirectoryEntry));
            strncpy(dir_entry.filename, filename, 8);
            dir_entry.first_cluster_low = free_cluster;
            dir_entry.file_size = 0; // Tamaño inicial del archivo

            // Escribir la entrada del directorio en el disco
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);

            // Actualizar la FAT en el disco
            update_fat(disk, fat, boot_sector);

            return 0;
        }
    }

    fprintf(stderr, "No hay entradas libres en el directorio raíz.\n");
    return -1;
}

int find_free_cluster(FAT16Table *fat) {
    for (int i = 2; i < FAT12_MAX_CLUSTERS; i++) {
        if (fat->entries[i] == 0x000) {
            return i;
        }
    }
    return -1;
}

int delete_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT16Table *fat) {
    // Buscar la entrada del archivo en el directorio raíz
    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (strncmp(dir_entry.filename, filename, 8) == 0) {
            // Marcar la entrada del directorio como eliminada
            dir_entry.filename[0] = 0xE5;
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);

            // Liberar los clusters en la FAT
            uint16_t cluster = dir_entry.first_cluster_low;
            while (cluster < 0xFF8) {
                uint16_t next_cluster = fat->entries[cluster];
                fat->entries[cluster] = 0x000;
                cluster = next_cluster;
            }

            // Actualizar la FAT en el disco
            update_fat(disk, fat, boot_sector);

            return 0;
        }
    }

    fprintf(stderr, "Archivo no encontrado.\n");
    return -1;
}

int list_directory(FILE *disk, BootSector *boot_sector) {
    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (dir_entry.filename[0] != 0x00 && dir_entry.filename[0] != 0xE5) {
            printf("%.8s.%.3s\n", dir_entry.filename, dir_entry.ext);
        }
    }
    return 0;
}int main() {
    FILE *disk = fopen("disk.img", "rb+");
    if (disk == NULL) {
        perror("Error al abrir el archivo de disco");
        return -1;
    }

    BootSector boot_sector;
    FAT16Table fat;

    if (read_boot_sector(disk, &boot_sector) != 0) {
        fclose(disk);
        return -1;
    }

    if (read_fat(disk, &fat, &boot_sector) != 0) {
        fclose(disk);
        return -1;
    }

    // Crear un archivo
    if (create_file(disk, "NEWFILE", &boot_sector, &fat) != 0) {
        fclose(disk);
        return -1;
    }

    // Eliminar un archivo
    if (delete_file(disk, "NEWFILE", &boot_sector, &fat) != 0) {
        fclose(disk);
        return -1;
    }

    // Listar directorios
    list_directory(disk, &boot_sector);

    fclose(disk);
    return 0;
}
FILE *disk_file; // Archivo global para manejar la imagen del disco
FAT16_BootSector boot_sector; // Estructura global del sector de arranque

/**
 * Lee el sector de arranque del disco y almacena la información en una estructura FAT12_BootSector.
 *
 * @param boot_sector Puntero a la estructura FAT12_BootSector donde se almacenará la información.
 * @return 0 si la lectura es exitosa, -1 en caso de error.
 */
int fat12_readBootSector(FAT16_BootSector *boot_sector) {
    // Posiciona el puntero de archivo al inicio del disco
    if (fseek(disk_file, 0, SEEK_SET) != 0) {
        perror("Error al posicionar el puntero del archivo");
        return -1;
    }

    // Lee el sector de arranque del disco
    if (fread(boot_sector, sizeof(FAT16_BootSector), 1, disk_file) != 1) {
        perror("Error al leer el sector de arranque");
        return -1;
    }

    return 0;
}

/**
 * Lee una tabla FAT del disco.
 *
 * @param fat_number Número de la FAT a leer (1 o 2).
 * @param buffer Buffer para almacenar los datos leídos.
 * @param offset Offset desde el inicio de la FAT.
 * @param size Tamaño de los datos a leer.
 * @return 0 si la lectura es exitosa, -1 en caso de error.
 */
int fat12_readFAT(int fat_number, void *buffer, uint32_t offset, uint32_t size) {
    // Verifica que el número de FAT sea válido (1 o 2)
    if (fat_number < 1 || fat_number > 2) {
        fprintf(stderr, "Número de FAT no válido. Debe ser 1 o 2.\n");
        return -1;
    }

    // Calcula la posición en el disco desde donde leer la tabla FAT
    uint32_t fat_start = (fat_number - 1) * boot_sector.fat_size * boot_sector.sector_size;
    uint32_t position = fat_start + offset;

    // Posiciona el puntero de archivo en la posición calculada
    if (fseek(disk_file, position, SEEK_SET) != 0) {
        perror("Error al posicionar el puntero del archivo");
        return -1;
    }

    // Lee los datos de la tabla FAT desde la posición calculada
    if (fread(buffer, size, 1, disk_file) != 1) {
        perror("Error al leer la tabla FAT");
        return -1;
    }

    return 0;
}

/**
 * Lee el directorio raíz del disco.
 *
 * @param buffer Buffer para almacenar los datos leídos.
 * @param offset Offset desde el inicio del directorio raíz.
 * @param size Tamaño de los datos a leer.
 * @return 0 si la lectura es exitosa, -1 en caso de error.
 */
int fat12_readRootDirectory(void *buffer, uint32_t offset, uint32_t size) {
    // Calcula la posición en el disco desde donde leer el directorio raíz
    uint32_t root_dir_start = (boot_sector.num_fats * boot_sector.fat_size + 1) * boot_sector.sector_size;
    uint32_t position = root_dir_start + offset;

    // Posiciona el puntero de archivo en la posición calculada
    if (fseek(disk_file, position, SEEK_SET) != 0) {
        perror("Error al posicionar el puntero del archivo");
        return -1;
    }

    // Lee los datos del directorio raíz desde la posición calculada
    if (fread(buffer, size, 1, disk_file) != 1) {
        perror("Error al leer el directorio raíz");
        return -1;
    }

    return 0;
}

/**
 * Lee un archivo desde el sistema de archivos FAT12.
 *
 * @param filename Nombre del archivo a leer.
 * @param buffer Buffer para almacenar el contenido del archivo.
 * @param buffer_size Tamaño del buffer.
 * @return 0 si la lectura es exitosa, -1 en caso de error.
 */
int fat12_readFile(const char *filename, void *buffer, uint32_t buffer_size) {
    // Implementa la lógica para localizar el archivo en el directorio raíz
    uint32_t root_dir_start = (boot_sector.num_fats * boot_sector.fat_size + 1) * boot_sector.sector_size;
    uint32_t root_dir_size = boot_sector.sector_size * boot_sector.total_clusters;
    uint8_t entry[32]; // Tamaño de una entrada en el directorio raíz
    uint32_t file_start_cluster = 0;
    uint32_t file_size = 0;

    for (uint32_t i = 0; i < root_dir_size / 32; i++) {
        // Posiciona el puntero de archivo en la posición de la entrada actual
        if (fseek(disk_file, root_dir_start + i * 32, SEEK_SET) != 0) {
            perror("Error al posicionar el puntero del archivo");
            return -1;
        }

        // Lee la entrada del directorio raíz
        if (fread(entry, 32, 1, disk_file) != 1) {
            perror("Error al leer la entrada del directorio raíz");
            return -1;
        }

        // Compara el nombre del archivo con la entrada del directorio
        if (strncmp((char *)entry, filename, strlen(filename)) == 0) {
            // Archivo encontrado
            file_start_cluster = entry[26] | (entry[27] << 8);                                // Clúster de inicio del archivo
            file_size = entry[28] | (entry[29] << 8) | (entry[30] << 16) | (entry[31] << 24); // Tamaño del archivo
            break;
        }
    }

    if (file_start_cluster == 0) {
        fprintf(stderr, "Archivo no encontrado\n");
        return -1;
    }

    // Lee el contenido del archivo utilizando la información obtenida de la tabla FAT
    uint32_t bytes_read = 0;
    uint32_t cluster = file_start_cluster;

    while (bytes_read < file_size && bytes_read < buffer_size) {
        // Calcula la posición en el disco del clúster actual
        uint32_t cluster_position = (1 + boot_sector.num_fats * boot_sector.fat_size + boot_sector.total_clusters + (cluster - 2) * boot_sector.cluster_size) * boot_sector.sector_size;

        // Posiciona el puntero de archivo en la posición calculada
        if (fseek(disk_file, cluster_position, SEEK_SET) != 0) {
            perror("Error al posicionar el puntero del archivo");
            return -1;
        }

        // Lee el contenido del clúster en el buffer
        uint32_t bytes_to_read = boot_sector.cluster_size * boot_sector.sector_size;
        if (bytes_read + bytes_to_read > file_size) {
            bytes_to_read = file_size - bytes_read;
        }
        if (fread((uint8_t *)buffer + bytes_read, bytes_to_read, 1, disk_file) != 1) {
            perror("Error al leer el contenido del archivo");
            return -1;
        }

        bytes_read += bytes_to_read;

        // Lee el siguiente clúster de la tabla FAT
        int read_boot_sector(FILE *disk, BootSector *boot_sector) {



        }
            fseek(disk, 0, SEEK_SET);
            if (fread(boot_sector, sizeof(BootSector), 1, disk) != 1) {
                perror("Error leyendo el sector de arranque");
                return -1;
            }
            return 0;
        }
        
        int read_fat(FILE *disk, FAT16Table *fat, BootSector *boot_sector) {
            fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
            if (fread(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
                perror("Error leyendo la FAT");
                return -1;
            }
            return 0;
        }
        
        int read_cluster(FILE *disk, void *buffer, uint32_t cluster, BootSector *boot_sector) {
            uint32_t cluster_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat + (cluster - 2) * boot_sector->sectors_per_cluster) * SECTOR_SIZE;
            fseek(disk, cluster_offset, SEEK_SET);
            if (fread(buffer, boot_sector->sectors_per_cluster * SECTOR_SIZE, 1, disk) != 1) {
                perror("Error leyendo el cluster");
                return -1;
            }
            return 0;
        }
        
                // Búsqueda de clusters libres
        int find_free_cluster(FAT12Table *fat) {
            for (int i = 2; i < FAT12_MAX_CLUSTERS; i++) {
                if (fat->entries[i] == 0x000) {
                    return i;
                }
            }
            return -1;
        }

        // Actualización de FAT
        int update_fat(FILE *disk, FAT12Table *fat, BootSector *boot_sector) {
            fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
            if (fwrite(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
                perror("Error actualizando la FAT");
                return -1;
            }
            return 0;
        }

        fat12_readFAT(1, &cluster, cluster * 2, 2);
        // Verifica si la entrada está vacía
        if (entry[0] == 0x00 || entry[0] == 0xE5) {
            // Escribe el nombre del archivo en la entrada
            memset(entry, 0, 32);
            uint32_t previous_cluster = 0;
            uint32_t bytes_written = 0;
            while (bytes_written < buffer_size) {
                // Encuentra el siguiente clúster libre
                for (; cluster < boot_sector.total_clusters; cluster++) {
                    uint16_t fat_entry;
                    fat12_readFAT(1, &fat_entry, cluster * 2, 2);
                    if (fat_entry == 0x000) {
                        break;
                    }
                }
                if (cluster >= boot_sector.total_clusters) {
                    fprintf(stderr, "No hay espacio suficiente en el disco para escribir el archivo\n");
                    return -1;
                }
                // Escribe el clúster en la tabla FAT
                if (previous_cluster != 0) {
                    fat12_writeFAT(1, previous_cluster, cluster);
                }
                previous_cluster = cluster;
                // Escribe los datos en el clúster
            }
            dir_entry.filename[0] = 0xE5;
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            // Liberar los clusters en la FAT
            update_fat(disk, fat, boot_sector);
            return 0;
        }
        cluster &= 0x0FFF; // FAT12 usa 12 bits por entrada
        if (cluster >= 0xFF8) { // Último clúster en la cadena
            break;
        }
    }

    int create_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT16Table *fat) {
        // Buscar una entrada libre en el directorio raíz
        DirectoryEntry dir_entry;
        uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
        fseek(disk, root_dir_offset, SEEK_SET);
        for (int i = 0; i < boot_sector->root_entries; i++) {
            fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            if (dir_entry.filename[0] == 0x00 || dir_entry.filename[0] == 0xE5) {
                // Encontrar un cluster libre en la FAT
                int free_cluster = find_free_cluster(fat);
                if (free_cluster == -1) {
                    fprintf(stderr, "No hay clusters libres disponibles.\n");
                    return -1;
                }
    
                // Marcar el cluster como final de archivo en la FAT
                fat->entries[free_cluster] = 0xFFF;
    
                // Crear la entrada del directorio
                memset(&dir_entry, 0, sizeof(DirectoryEntry));
                strncpy(dir_entry.filename, filename, 8);
                dir_entry.first_cluster_low = free_cluster;
                dir_entry.file_size = 0; // Tamaño inicial del archivo
    
                // Escribir la entrada del directorio en el disco
                fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
                fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
    
                // Actualizar la FAT en el disco
                update_fat(disk, fat, boot_sector);
    
                return 0;
            }
        }
    
        fprintf(stderr, "No hay entradas libres en el directorio raíz.\n");
        return -1;
    }
}

/**
 * Escribe un archivo en el sistema de archivos FAT12.
 *
 * @param filename Nombre del archivo a escribir.
 * @param buffer Buffer con el contenido del archivo.
 * @param buffer_size Tamaño del buffer.
 * @return 0 si la escritura es exitosa, -1 en caso de error.
 */
int fat12_writeFile(const char *filename, const void *buffer, uint32_t buffer_size) {
    // Encuentra espacio libre en el directorio raíz
    uint32_t root_dir_start = (boot_sector.num_fats * boot_sector.fat_size + 1) * boot_sector.sector_size;
    uint32_t root_dir_size = boot_sector.sector_size * boot_sector.total_clusters;
    uint8_t entry[32]; // Tamaño de una entrada en el directorio raíz

    for (uint32_t i = 0; i < root_dir_size / 32; i++) {
        // Posiciona el puntero de archivo en la posición de la entrada actual

        int read_cluster(FILE *disk, void *buffer, uint32_t cluster, BootSector *boot_sector) {
            uint32_t cluster_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat + (cluster - 2) * boot_sector->sectors_per_cluster) * SECTOR_SIZE;
            fseek(disk, cluster_offset, SEEK_SET);
            if (fread(buffer, boot_sector->sectors_per_cluster * SECTOR_SIZE, 1, disk) != 1) {
                perror("Error leyendo el cluster");
                return -1;
            }
            return 0;
        }
        if (fseek(disk_file, root_dir_start + i * 32, SEEK_SET) != 0) {
            perror("Error al posicionar el puntero del archivo");
            return -1;
        }

        int list_directory(FILE *disk, BootSector *boot_sector) {
            DirectoryEntry dir_entry;
            uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
            fseek(disk, root_dir_offset, SEEK_SET);
            for (int i = 0; i < boot_sector->root_entries; i++) {
                fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
                if (dir_entry.filename[0] != 0x00 && dir_entry.filename[0] != 0xE5) {
                    printf("%.8s.%.3s\n", dir_entry.filename, dir_entry.ext);
                }
            }
            return 0;
        }

        uint32_t previous_cluster = 0;
        uint32_t bytes_written = 0;

        // Lee la entrada del directorio raíz
        if (fread(entry, 32, 1, disk_file) != 1) {
            perror("Error al leer la entrada del directorio raíz");
            return -1;
        }

        // Verifica si la entrada está vacía
        if (entry[0] == 0x00 || entry[0] == 0xE5) {
            // Escribe el nombre del archivo en la entrada
            memset(entry, 0, 32);
            strncpy((char *)entry, filename, strlen(filename));

            // Encuentra clústeres libres en la FAT
            uint32_t cluster = 2;
            uint32_t previous_cluster = 0;
            uint32_t bytes_written = 0;

            while (bytes_written < buffer_size) {
                // Encuentra el siguiente clúster libre
                for (; cluster < boot_sector.total_clusters; cluster++) {
                    uint16_t fat_entry;
                    fat12_readFAT(1, &fat_entry, cluster * 2, 2);
                    if (fat_entry == 0x000) {
                        break;
                    }
                }

                if (cluster >= boot_sector.total_clusters) {
                    fprintf(stderr, "No hay espacio suficiente en el disco para escribir el archivo\n");
                    return -1;
                }

                // Escribe el clúster en la tabla FAT
                if (previous_cluster != 0) {
                    fat12_writeFAT(1, previous_cluster, cluster);
                }
                previous_cluster = cluster;

                // Escribe los datos en el clúster

                }

                uint32_t bytes_to_write = boot_sector.cluster_size * boot_sector.sector_size;
                if (bytes_written + bytes_to_write > buffer_size) {
                    bytes_to_write = buffer_size - bytes_written;
                }
                if (fwrite((uint8_t *)buffer + bytes_written, bytes_to_write, 1, disk_file) != 1) {
                    perror("Error al escribir el contenido del archivo");



            }

            // Marca el último clúster en la tabla FAT
            fat12_writeFAT(1, previous_cluster, 0xFFF);

            // Escribe el clú            int delete_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT12Table *fat) {
                // Buscar la entrada del archivo en el directorio raíz



                for (int i = 0; i < boot_sector->root_entries; i++) {
                    fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
                    if (strncmp(dir_entry.filename, filename, 8) == 0) {
                        // Marcar la entrada del directorio como eliminada
                        dir_entry.filename[0] = 0xE5;
                        fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
                        fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            
                        // Liberar los clusters en la FAT
                        uint16_t cluster = dir_entry.first_cluster_low;
                        while (cluster < 0xFF8) {
                            uint16_t next_cluster = fat->entries[cluster];
                            fat->entries[cluster] = 0x000;
                            cluster = next_cluster;
                        }
            
                        // Actualizar la FAT en el disco
                        update_fat(disk, fat, boot_sector);
            
                        return 0;
                    }
                }
            
                fprintf(stderr, "Archivo no encontrado.\n");
                return -1;
            }            int main() {
                FILE *disk = fopen("disk.img", "rb+");
                if (disk == NULL) {
                    perror("Error al abrir el archivo de disco");
                    return -1;
                }
            
                BootSector boot_sector;
                FAT12Table fat;
            
                if (read_boot_sector(disk, &boot_sector) != 0) {
                    fclose(disk);
                    return -1;
                }
            
                fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
                if (fread(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
                    perror("Error leyendo la FAT");
                    fclose(disk);
                    return -1;
                }
            
                // Crear un archivo
                if (create_file(disk, "NEWFILE", &boot_sector, &fat) != 0) {
                    fclose(disk);
                    return -1;
                }
            
                // Eliminar un archivo
                if (delete_file(disk, "NEWFILE", &boot_sector, &fat) != 0) {
                    fclose(disk);
                    return -1;
                }
            
                fclose(disk);
                return 0;
            }ster de inicio y el tamaño del archivo en la entrada del directorio
            entry[26] = cluster & 0xFF;
            entry[27] = (cluster >> 8) & 0xFF;
            entry[28] = buffer_size & 0xFF;
            entry[29] = (buffer_size >> 8) & 0xFF;
            entry[30] = (buffer_            uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
            fseek(disk, root_dir_offset, SEEK_SET);
            for (int i = 0; i < boot_sector->root_entries; i++) {
                fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
                if (dir_entry.filename[0] != 0x00 && dir_entry.filename[0] != 0xE5) {
                    printf("%.8s.%.3s\n", dir_entry.filename, dir_entry.ext);
                }
            }
            return 0;
            }size >> 16) & 0xFF;
            entry[31] = (buffer_size >> 24) & 0xFF;

            // Guarda la entrada actualizada en el directorio raíz
            if (fseek(disk_file, root_dir_start + i * 32, SEEK_SET) != 0) {
                perror("Error al posicionar el puntero del archivo");
                return -1;
            }
            if (fwrite(entry, 32, 1, disk_file) != 1) {
                perror("Error al escribir la entrada del directorio raíz");
                return -1;
            }

            break;
        }
    }

    return 0;
}

// Búsqueda de clusters libres
int find_free_cluster(FAT12Table *fat) {
    for (int i = 2; i < FAT12_MAX_CLUSTERS; i++) {
        if (fat->entries[i] == 0x000) {
            return i;
        }
    }
    return -1;
}

// Actualización de FAT
int update_fat(FILE *disk, FAT12Table *fat, BootSector *boot_sector) {
    fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
    if (fwrite(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error actualizando la FAT");
        return -1;
    }
    return 0;
}7] = (cluster >> 8) & 0xFF;
            entry[28] = buffer_size & 0xFF;
            entry[29] = (buffer_size >> 8) & 0xFF;
            entry[30] = (buffer_size >> 16) & 0xFF;
            entry[31] = (buffer_size >> 24) & 0xFF;

            // Guarda la entrada actualizada en el directorio raíz
            if (fseek(disk_file, root_dir_start + i * 32, SEEK_SET) != 0) {
                perror("Error al posicionar el puntero del archivo");
                return -1;
            }
            if (fwrite(entry, 32, 1, disk_file) != 1) {
                perror("Error al escribir la entrada del directorio raíz");
                return -1;
            }

            break;
        }
    }

    return 0;
}

/**
 * Escribe una entrada en la tabla FAT.
 *
 * @param fat_number Número de la FAT a escribir (1 o 2).
 * @param cluster Clúster que se va a escribir.
 * @param value Valor que se va a escribir en la tabla FAT.
 * @return 0 si la escritura es exitosa, -1 en caso de error.
 */
#include <stdio.h>
#include <stdint.h>

// Definición de constantes (ajustar según sea necesario)
#define FAT1_OFFSET 0x2000  // Offset de la FAT1 en el disco (ejemplo)
#define FAT2_OFFSET 0x4000  // Offset de la FAT2 en el disco (ejemplo)
#define SECTOR_SIZE 512     // Tamaño del sector en bytes (ejemplo)

// Función para leer una tabla FAT del disco
int fat12_readFAT(int fat_number, void *buffer, uint32_t offset, uint32_t size) {
    // Verifica que el número de FAT sea válido (1 o 2)
    if (fat_number < 1 || fat_number > 2) {
        fprintf(stderr, "Número de FAT no válido. Debe ser 1 o 2.\n");
        return -1;
    }

    // Calcula la posición en el disco desde donde leer la tabla FAT
    uint32_t fat_offset = (fat_number == 1) ? FAT1_OFFSET : FAT2_OFFSET;
    uint32_t read_position = fat_offset + offset;

    // Abre el archivo de disco (ajustar el nombre del archivo según sea necesario)
    FILE *disk_file = fopen("disk.img", "rb");
    if (disk_file == NULL) {
        perror("Error al abrir el archivo de disco");
        return -1;
    }

    // Mueve el puntero del archivo a la posición de lectura
    if (fseek(disk_file, read_position, SEEK_SET) != 0) {
        perror("Error al mover el puntero del archivo");
        fclose(disk_file);
        return -1;
    }

    // Lee los datos de la tabla FAT en el buffer
    if (fread(buffer, 1, size, disk_file) != size) {
        perror("Error al leer la tabla FAT");
        fclose(disk_file);
        return -1;
    }

    // Cierra el archivo de disco
    fclose(disk_file);

    return 0;
}#include "fat12.h"
#include <string.h>

int read_boot_sector(FILE *disk, BootSector *boot_sector) {
    fseek(disk, 0, SEEK_SET);
    if (fread(boot_sector, sizeof(BootSector), 1, disk) != 1) {
        perror("Error leyendo el sector de arranque");
        return -1;
    }
    return 0;
}

int read_fat(FILE *disk, FAT12Table *fat, BootSector *boot_sector) {
    if (disk == NULL || fat == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a read_fat\n");
        return -1;
    }

    fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
    if (fread(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error leyendo la FAT");
        return -1;
    }
    return 0;
}

int read_cluster(FILE *disk, void *buffer, uint32_t cluster, BootSector *boot_sector) {
    if (disk == NULL || buffer == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a read_cluster\n");
        return -1;
    }

    uint32_t cluster_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat + (cluster - 2) * boot_sector->sectors_per_cluster) * SECTOR_SIZE;
    fseek(disk, cluster_offset, SEEK_SET);
    if (fread(buffer, boot_sector->sectors_per_cluster * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error leyendo el cluster");
        return -1;
    }
    return 0;
}

int find_free_cluster(FAT12Table *fat) {
    for (int i = 2; i < FAT12_MAX_CLUSTERS; i++) {
        if (fat->entries[i] == 0x000) {
            return i;
        }
    }
    return -1;
}

int update_fat(FILE *disk, FAT12Table *fat, BootSector *boot_sector) {
    fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
    if (fwrite(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error actualizando la FAT");
        return -1;
    }
    return 0;
}

int create_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT12Table *fat) {
    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (dir_entry.filename[0] == 0x00 || dir_entry.filename[0] == 0xE5) {
            int free_cluster = find_free_cluster(fat);
            if (free_cluster == -1) {
                fprintf(stderr, "No hay clusters libres disponibles.\n");
                return -1;
            }
            fat->entries[free_cluster] = 0xFFF;
            memset(&dir_entry, 0, sizeof(DirectoryEntry));
            strncpy(dir_entry.filename, filename, 8);
            dir_entry.first_cluster_low = free_cluster;
            dir_entry.file_size = 0;
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            update_fat(disk, fat, boot_sector);
            return 0;
        }
    }
    fprintf(stderr, "No hay entradas libres en el directorio raíz.\n");
    return -1;
}

int delete_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT12Table *fat) {
    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (strncmp(dir_entry.filename, filename, 8) == 0) {
            dir_entry.filename[0] = 0xE5;
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            uint16_t cluster = dir_entry.first_cluster_low;
            while (cluster < 0xFF8) {
                uint16_t next_cluster = fat->entries[cluster];
                fat->entries[cluster] = 0x000;
                cluster = next_cluster;
            }
            update_fat(disk, fat, boot_sector);
            return 0;
        }
    }
    fprintf(stderr, "Archivo no encontrado.\n");
    return -1;
}

#include <stdio.h>
#include <stdint.h>
#include "fat16.h"

int list_directory(FILE *disk, BootSector *boot_sector) {
    if (disk == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a list_directory\n");
        return -1;
    }

    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (dir_entry.filename[0] != 0x00 && dir_entry.filename[0] != 0xE5) {
            printf("%.8s.%.3s\n", dir_entry.filename, dir_entry.ext);
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdint.h>

// Definición de constantes (ajustar según sea necesario)
#define FAT1_OFFSET 0x2000  // Offset de la FAT1 en el disco (ejemplo)
#define FAT2_OFFSET 0x4000  // Offset de la FAT2 en el disco (ejemplo)
#define SECTOR_SIZE 512     // Tamaño del sector en bytes (ejemplo)

// Función para leer una tabla FAT del disco
int fat16_readFAT(int fat_number, void *buffer, uint32_t offset, uint32_t size) {
    // Verifica que el número de FAT sea válido (1 o 2)
    if (fat_number != 1 && fat_number != 2) {
        fprintf(stderr, "Número de FAT inválido: %d\n", fat_number);
        return -1;
    }

    // Calcula el offset correcto basado en el número de FAT
    uint32_t fat_offset = (fat_number == 1) ? FAT1_OFFSET : FAT2_OFFSET;

    // Abre el archivo de disco (ajustar el nombre del archivo según sea necesario)
    FILE *disk = fopen("disk.img", "rb");
    if (disk == NULL) {
        perror("Error abriendo el archivo de disco");
        return -1;
    }

    // Mueve el puntero del archivo al offset de la FAT
    fseek(disk, fat_offset + offset, SEEK_SET);

    // Lee la FAT en el buffer
    if (fread(buffer, size, 1, disk) != 1) {
        perror("Error leyendo la FAT");
        fclose(disk);
        return -1;
    }

    // Cierra el archivo de disco
    fclose(disk);
    return 0;
}

#include <stdio.h>
#include <stdint.h>

// Definición de constantes (ajustar según sea necesario)
#define FAT1_OFFSET 0x2000  // Offset de la FAT1 en el disco (ejemplo)
#define FAT2_OFFSET 0x4000  // Offset de la FAT2 en el disco (ejemplo)
#define SECTOR_SIZE 512     // Tamaño del sector en bytes (ejemplo)

// Función para leer una tabla FAT del disco
int fat12_readFAT(int fat_number, void *buffer, uint32_t offset, uint32_t size) {
    // Verifica que el número de FAT sea válido (1 o 2)
    if (fat_number < 1 || fat_number > 2) {
        fprintf(stderr, "Número de FAT no válido. Debe ser 1 o 2.\n");
        return -1;
    }

    // Calcula la posición en el disco desde donde leer la tabla FAT
    uint32_t fat_offset = (fat_number == 1) ? FAT1_OFFSET : FAT2_OFFSET;
    uint32_t read_position = fat_offset + offset;

    // Abre el archivo de disco (ajustar el nombre del archivo según sea necesario)
    FILE *disk_file = fopen("disk.img", "rb");
    if (disk_file == NULL) {
        perror("Error al abrir el archivo de disco");
        return -1;
    }

    // Mueve el puntero del archivo a la posición de lectura
    if (fseek(disk_file, read_position, SEEK_SET) != 0) {
        perror("Error al mover el puntero del archivo");
        fclose(disk_file);
        return -1;
    }

    // Lee los datos de la tabla FAT en el buffer
    if (fread(buffer, 1, size, disk_file) != size) {
        perror("Error al leer la tabla FAT");
        fclose(disk_file);
        return -1;
    }

    // Cierra el archivo de disco
    fclose(disk_file);

    return 0;    int create_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT12Table *fat) {
        // Buscar una entrada libre en el directorio raíz
        DirectoryEntry dir_entry;
        uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
        fseek(disk, root_dir_offset, SEEK_SET);
        for (int i = 0; i < boot_sector->root_entries; i++) {
            fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            if (dir_entry.filename[0] == 0x00 || dir_entry.filename[0] == 0xE5) {
                // Encontrar un cluster libre en la FAT
                int free_cluster = find_free_cluster(fat);
                if (free_cluster == -1) {
                    fprintf(stderr, "No hay clusters libres disponibles.\n");
                    return -1;
                }
    
                // Marcar el cluster como final de archivo en la FAT
                fat->entries[free_cluster] = 0xFFF;
    
                // Crear la entrada del directorio
                memset(&dir_entry, 0, sizeof(DirectoryEntry));
                strncpy(dir_entry.filename, filename, 8);
                dir_entry.first_cluster_low = free_cluster;
                dir_entry.file_size = 0; // Tamaño inicial del archivo
    
                // Escribir la entrada del directorio en el disco
                fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
                fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
    
                // Actualizar la FAT en el disco
                update_fat(disk, fat, boot_sector);
    
                return 0;
            }
        }
    
        fprintf(stderr, "No hay entradas libres en el directorio raíz.\n");
        return -1;
    }
}
// Cierra el archivo de disco
fclose(disk_file);

#include "fat16.h"
#include <string.h>

int read_boot_sector(FILE *disk, BootSector *boot_sector) {
    if (disk == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a read_boot_sector\n");
        return -1;
    }

    fseek(disk, 0, SEEK_SET);
    if (fread(boot_sector, sizeof(BootSector), 1, disk) != 1) {
        perror("Error leyendo el sector de arranque");
        return -1;
    }
    return 0;
}

int read_fat(FILE *disk, FAT16Table *fat, BootSector *boot_sector) {
    if (disk == NULL || fat == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a read_fat\n");
        return -1;
    }

    fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
    if (fread(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error leyendo la FAT");
        return -1;
    }
    return 0;
}

int read_cluster(FILE *disk, void *buffer, uint32_t cluster, BootSector *boot_sector) {
    if (disk == NULL || buffer == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a read_cluster\n");
        return -1;
    }

    uint32_t cluster_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat + (cluster - 2) * boot_sector->sectors_per_cluster) * SECTOR_SIZE;
    fseek(disk, cluster_offset, SEEK_SET);
    if (fread(buffer, boot_sector->sectors_per_cluster * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error leyendo el cluster");
        return -1;
    }
    return 0;
}

int find_free_cluster(FAT16Table *fat) {
    if (fat == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a find_free_cluster\n");
        return -1;
    }

    for (int i = 2; i < FAT16_MAX_CLUSTERS; i++) {
        if (fat->entries[i] == 0x0000) {
            return i;
        }
    }
    return -1;
}

int update_fat(FILE *disk, FAT16Table *fat, BootSector *boot_sector) {
    if (disk == NULL || fat == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a update_fat\n");
        return -1;
    }

    fseek(disk, boot_sector->reserved_sectors * SECTOR_SIZE, SEEK_SET);
    if (fwrite(fat->entries, boot_sector->sectors_per_fat * SECTOR_SIZE, 1, disk) != 1) {
        perror("Error actualizando la FAT");
        return -1;
    }
    return 0;
}

int create_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT16Table *fat) {
    if (disk == NULL || filename == NULL || boot_sector == NULL || fat == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a create_file\n");
        return -1;
    }

    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (dir_entry.filename[0] == 0x00 || dir_entry.filename[0] == 0xE5) {
            int free_cluster = find_free_cluster(fat);
            if (free_cluster == -1) {
                fprintf(stderr, "No hay clusters libres disponibles.\n");
                return -1;
            }
            fat->entries[free_cluster] = 0xFFFF;
            memset(&dir_entry, 0, sizeof(DirectoryEntry));
            strncpy(dir_entry.filename, filename, 8);
            dir_entry.first_cluster_low = free_cluster;
            dir_entry.file_size = 0;
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            update_fat(disk, fat, boot_sector);
            return 0;
        }
    }
    fprintf(stderr, "No hay entradas libres en el directorio raíz.\n");
    return -1;
}

int delete_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT16Table *fat) {
    if (disk == NULL || filename == NULL || boot_sector == NULL || fat == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a delete_file\n");
        return -1;
    }

    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (strncmp(dir_entry.filename, filename, 8) == 0) {
            dir_entry.filename[0] = 0xE5;
            fseek(disk, root_dir_offset + i * sizeof(DirectoryEntry), SEEK_SET);
            fwrite(&dir_entry, sizeof(DirectoryEntry), 1, disk);
            uint16_t cluster = dir_entry.first_cluster_low;
            while (cluster < 0xFFF8) {
                uint16_t next_cluster = fat->entries[cluster];
                fat->entries[cluster] = 0x0000;
                cluster = next_cluster;
            }
            update_fat(disk, fat, boot_sector);
            return 0;
        }
    }
    fprintf(stderr, "Archivo no encontrado.\n");
    return -1;
}

int list_directory(FILE *disk, BootSector *boot_sector) {
    if (disk == NULL || boot_sector == NULL) {
        fprintf(stderr, "Parámetro nulo pasado a list_directory\n");
        return -1;
    }

    DirectoryEntry dir_entry;
    uint32_t root_dir_offset = (boot_sector->reserved_sectors + boot_sector->num_fats * boot_sector->sectors_per_fat) * SECTOR_SIZE;
    fseek(disk, root_dir_offset, SEEK_SET);
    for (int i = 0; i < boot_sector->root_entries; i++) {
        fread(&dir_entry, sizeof(DirectoryEntry), 1, disk);
        if (dir_entry.filename[0] != 0x00 && dir_entry.filename[0] != 0xE5) {
            printf("%.8s.%.3s\n", dir_entry.filename, dir_entry.ext);
        }
    }
    return 0;
}
