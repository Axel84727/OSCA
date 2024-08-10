#!/bin/bash
set -e
# This is a build script for the current setup.
# For larger projects, you may want to consider using GNU Make

if [ -f "os.bin" ] && [ -f "iso/boot/os.bin" ]; then
  rm -r os.bin
  rm -r iso/boot/os.bin
fi

ASM="nasm"
ASMF="-f elf32 -o"
LD="ld.lld"
LDF="-static -nostdlib -T linker.ld -o"
C_COMPILER="clang"
CFLAGS="-static -target i686-none-elf -nostdlib -Iinclude/libc -c -o"
IS_16=1

include/build.sh

# Compile boot.asm with NASM
echo "[OSCA]: Building bootloader from scratch!"
$ASM $ASMF "obj/boot/boot.o" "iso/boot/boot.asm"

# Compile the kernel with clang. (Getting a GCC compiler on Replit is difficult, but clang supports many binary formats out of the box.)
echo "[OSCA]: Building kernel from scratch!"

IFILES=""
for file in core/src/*.c; do
  if [ -f "$file" ]; then
    IFILES+="$file "
  fi
done

$C_COMPILER $CFLAGS "obj/core/src/kernel.o" $IFILES

OFILES=""
OFILE="os.bin"

for file in obj/boot/*.o; do
  if [ -f "$file" ]; then
    OFILES+="$file "
  fi
done

for file in obj/include/libc/*.o; do
  if [ -f "$file" ]; then
    OFILES+="$file "
  fi
done

for file in obj/include/libcc/*.o; do
  if [ -f "$file" ]; then
    OFILES+="$file "
  fi
done

for file in obj/core/src/*.o; do
  if [ -f "$file" ]; then
    OFILES+="$file "
  fi
done

# Link
echo Linking
$LD $LDF $OFILE $OFILES

# Clean
echo Clean
rm -r $OFILES

# Make an ISO out of the kernel with grub-mkrescue
echo Making a bootable ISO
cp os.bin iso/boot/os.bin
grub2-mkrescue -o os.iso iso

# Boot it with QEMU
echo Booting os.iso
qemu-system-i386 -cdrom os.iso