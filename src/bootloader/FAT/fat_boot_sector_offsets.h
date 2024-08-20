#ifndef FAT_BOOT_SECTOR_OFFSETS_H
#define FAT_BOOT_SECTOR_OFFSETS_H

// Desplazamientos en el sector de arranque para FAT12/FAT16

// Desplazamiento para el campo "Jump instruction" (Instrucción de salto)
#define OFFSET_JUMP_INSTRUCTION      0x0000

// Desplazamiento para el campo "OEM name" (Nombre OEM)
#define OFFSET_OEM_NAME              0x0003

// Desplazamiento para el campo "Bytes per sector" (Bytes por sector)
#define OFFSET_BYTES_PER_SECTOR      0x000B

// Desplazamiento para el campo "Sectors per cluster" (Sectores por clúster)
#define OFFSET_SECTORS_PER_CLUSTER   0x000D

// Desplazamiento para el campo "Reserved sectors" (Sectores reservados)
#define OFFSET_RESERVED_SECTORS      0x000E

// Desplazamiento para el campo "Number of FATs" (Número de FATs)
#define OFFSET_NUMBER_OF_FATS        0x0010

// Desplazamiento para el campo "Root directory entries" (Entradas del directorio raíz)
#define OFFSET_ROOT_DIRECTORY_ENTRIES 0x0012

// Desplazamiento para el campo "Total sectors (16-bit)" (Total de sectores en 16 bits)
#define OFFSET_TOTAL_SECTORS_16      0x0014

// Desplazamiento para el campo "Media descriptor" (Descriptor de medios)
#define OFFSET_MEDIA_DESCRIPTOR      0x0016

// Desplazamiento para el campo "FAT size" (Tamaño de la FAT)
#define OFFSET_FAT_SIZE              0x0018

// Desplazamiento para el campo "Sectors per track" (Sectores por pista)
#define OFFSET_SECTORS_PER_TRACK     0x001A

// Desplazamiento para el campo "Number of heads" (Número de cabezales)
#define OFFSET_NUMBER_OF_HEADS       0x001C

// Desplazamiento para el campo "Hidden sectors" (Sectores ocultos)
#define OFFSET_HIDDEN_SECTORS        0x001E

// Desplazamiento para el campo "Total sectors (32-bit)" (Total de sectores en 32 bits)
#define OFFSET_TOTAL_SECTORS_32      0x0024

// Desplazamiento para el campo "Drive number" (Número de unidad)
#define OFFSET_DRIVE_NUMBER          0x0028

// Desplazamiento para el campo "Reserved" (Reservado)
#define OFFSET_RESERVED_1            0x0029

// Desplazamiento para el campo "Extended boot signature" (Firma extendida de arranque)
#define OFFSET_EXTENDED_BOOT_SIGNATURE 0x002A

// Desplazamiento para el campo "Volume ID" (Identificador del volumen)
#define OFFSET_VOLUME_ID             0x002B

// Desplazamiento para el campo "Volume label" (Etiqueta del volumen)
#define OFFSET_VOLUME_LABEL          0x002F

// Desplazamiento para el campo "File system type" (Tipo de sistema de archivos)
#define OFFSET_FILE_SYSTEM_TYPE      0x0038

// Desplazamiento para el campo "Boot code" (Código de arranque)
#define OFFSET_BOOT_CODE             0x0038

// Desplazamiento para el campo "Boot sector signature" (Firma del sector de arranque)
#define OFFSET_BOOT_SECTOR_SIGNATURE 0x01FE

#endif // FAT_BOOT_SECTOR_OFFSETS_H
