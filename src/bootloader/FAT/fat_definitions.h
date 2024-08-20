#ifndef FAT_DEFINITIONS_H
#define FAT_DEFINITIONS_H

// Definiciones generales para el sistema de archivos FAT

// Tamaño máximo de una entrada de directorio (en bytes)
#define DIR_ENTRY_SIZE  32

// Tamaño de un clúster en bytes (usualmente 512, 1024, 2048, o 4096 bytes)
#define CLUSTER_SIZE    512

// Número de sectores por clúster (depende del tamaño del clúster y del tamaño del sector)
#define SECTORS_PER_CLUSTER (CLUSTER_SIZE / 512)

// Tamaño máximo de un archivo en FAT16 (en bytes)
// FAT16 usa 16 bits para los números de clúster, por lo que el tamaño máximo de un archivo es:
#define MAX_FILE_SIZE    (64 * 1024 * 1024) // 64 MiB

// Número de entradas en el directorio raíz en FAT12 y FAT16
#define ROOT_DIR_ENTRIES  512

// Número máximo de clústeres en FAT16
#define MAX_CLUSTERS      0xFFF5 // 2^16 - 1 para FAT16



// Valores para los atributos del archivo en la entrada del directorio
#define ATTR_READ_ONLY    0x01
#define ATTR_HIDDEN       0x02
#define ATTR_SYSTEM       0x04
#define ATTR_VOLUME_LABEL 0x08
#define ATTR_DIRECTORY    0x10
#define ATTR_ARCHIVE      0x20

// Máscara para obtener el número de clúster (de 12 bits) en FAT12
#define CLUSTER_MASK_FAT12 0x0FFF

// Máscara para obtener el número de clúster (de 16 bits) en FAT16
#define CLUSTER_MASK_FAT16 0xFFFF

// Valores de fin de archivo en FAT12/FAT16
#define END_OF_FILE_FAT12 0x0FFF
#define END_OF_FILE_FAT16 0xFFFF

// Valores reservados en FAT12/FAT16
#define RESERVED_FAT12    0xFF7
#define RESERVED_FAT16    0xFFF7

#endif // FAT_DEFINITIONS_H
