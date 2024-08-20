#ifndef FAT12_H
#define FAT12_H

#include <stdint.h>
#include <stdio.h>

#define SECTOR_SIZE 512
#define CLUSTER_SIZE 4096
#define FAT12_MAX_CLUSTERS 4085

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

typedef struct {
    char     filename[8];            // Nombre del archivo
    char     ext[3];                 // Extensión del archivo
    uint8_t  attributes;             // Atributos del archivo
    uint8_t  reserved;               // Reservado
    uint8_t  creation_time_tenths;   // Tiempo de creación (décimas de segundo)
    uint16_t creation_time;          // Tiempo de creación
    uint16_t creation_date;          // Fecha de creación
    uint16_t last_access_date;       // Fecha de último acceso
    uint16_t first_cluster_high;     // Primer cluster alto
    uint16_t write_time;             // Tiempo de escritura
    uint16_t write_date;             // Fecha de escritura
    uint16_t first_cluster_low;      // Primer cluster bajo
    uint32_t file_size;              // Tamaño del archivo
} DirectoryEntry;
#pragma pack(pop)

typedef struct {
    uint16_t entries[FAT12_MAX_CLUSTERS]; // Entradas de la tabla FAT12
} FAT12Table;

// Declaraciones de funciones para FAT12
int read_boot_sector(FILE *disk, BootSector *boot_sector);
int read_fat(FILE *disk, FAT12Table *fat, BootSector *boot_sector);
int read_cluster(FILE *disk, void *buffer, uint32_t cluster, BootSector *boot_sector);
int create_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT12Table *fat);
int delete_file(FILE *disk, const char *filename, BootSector *boot_sector, FAT12Table *fat);
int list_directory(FILE *disk, BootSector *boot_sector);

#endif // FAT12_H
