#ifndef DISK_H
#define DISK_H

#include <stdint.h>

// Declaración de funciones para el acceso al disco
void disk_init(const char *diskImage);
void disk_readSector(uint32_t sectorNumber, uint8_t *buffer, uint32_t sectorSize);
void disk_writeSector(uint32_t sectorNumber, const uint8_t *buffer, uint32_t sectorSize);

#endif // DISK_H
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
}