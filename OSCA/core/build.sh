#!/bin/bash
set -e

mkdir -p obj/core/src/include/libc
mkdir -p obj/core/src/include/pmm
mkdir -p obj/core/src/include/x86/driver

C_COMPILER="clang"
CFLAGS="-static -target i686-none-elf -nostdlib -Iinclude/libc -Icore/include -c -o"

echo ""
echo "[OSCA CORE]: Building Physical Memory Management module (PMM)"
for file in core/src/include/pmm/*.c; do
  if [ -f "$file" ]; then
    base_name=$(basename "$file" .c)
    echo "[OSCA PMM]: Compiling $file source!"
    $C_COMPILER $CFLAGS "obj/core/src/include/pmm/${base_name}.o" "$file"
  fi
done

echo "[OSCA CORE]: Physical Memory Management (PMM) module builded successfully!"
echo ""

echo ""
echo "[OSCA CORE]: Building X86 module"
for file in core/src/include/x86/driver/*.c; do
  if [ -f "$file" ]; then
    base_name=$(basename "$file" .c)
    echo "[OSCA X86]: Compiling $file source!"
    $C_COMPILER $CFLAGS "obj/core/src/include/x86/driver/${base_name}.o" "$file"
  fi
done

echo "[OSCA CORE]: X86 module builded successfully!"
echo ""

echo ""
echo "[OSCA CORE]: Building KERNEL"
for file in core/src/*.c; do
  if [ -f "$file" ]; then
    base_name=$(basename "$file" .c)
    echo "[OSCA KERNEL]: Compiling $file source!"
    $C_COMPILER $CFLAGS "obj/core/src/${base_name}.o" "$file"
  fi
done
echo "[OSCA CORE]: KERNEL builded successfully!"
echo ""