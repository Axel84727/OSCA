---

# Proyecto E.N.I.G.M.A.-OS
E.V.E.R.E.S.T.-OS (Enhanced Virtualized Enterprise Real-time Extensible System Technology)

Este proyecto contiene un bootloader básico escrito en ensamblador, configurado para construirse con SCons. El bootloader soporta varios sistemas de archivos, incluyendo FAT12, FAT16 y FAT32.

**Nota:** Este código forma parte de un código fuente en desarrollo para un sistema operativo más amplio. Actualmente, se está construyendo y se invita a los colaboradores a unirse para expandir y mejorar el proyecto.

## Descripción

El bootloader es un programa que se ejecuta al inicio del proceso de arranque del sistema. Su función principal es inicializar el entorno y cargar un segundo stage desde el disco.

## Requisitos

- **SCons**: Herramienta de construcción de software.
- **Assembler**: Herramienta para compilar archivos en lenguaje ensamblador.
- **Entorno de emulación o hardware para pruebas**: Por ejemplo, QEMU o VirtualBox.

## Estructura del Proyecto

- **build_scripts/utility.py**: Contiene funciones útiles para la construcción, como `GlobRecursive`.
- **linker.ld**: Script de enlace que define la disposición de la memoria.
- **stage1.map**: Archivo de mapa generado durante el proceso de enlace.
- ***.asm**: Archivos de ensamblador que contienen el código del bootloader.

## Estructura del Código

- **build_scripts/build.py**:
  - Configura el entorno de construcción con SCons.
  - Compila y enlaza archivos de ensamblador para crear el bootloader.

- **bootloader.asm**:
  - **.fsjump**: Salta al inicio del bootloader.
  - **.fsheaders**: Configura los encabezados del sistema de archivos.
  - **.entry**: Inicializa el entorno y maneja el disco.
  - **.text**: Contiene el código principal del bootloader.
  - **.rodata** y **.data**: Datos y mensajes utilizados por el bootloader.
  - **.bss**: Espacio reservado para datos no inicializados.

## Contribuciones

Este proyecto está en desarrollo y estamos buscando colaboradores para expandirlo. Si estás interesado en contribuir, realiza un fork del repositorio y envía un pull request. Tu participación es muy apreciada.

## Licencia

Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo `LICENSE` para obtener más detalles.

---

