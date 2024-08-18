# LIBC
mkdir -p obj/include
mkdir -p obj/include/libc
mkdir -p obj/include/libcc
mkdir -p obj/include/libc/extras

C_COMPILER="clang"
CFLAGS="-static -target i686-none-elf -nostdlib -Iinclude/libc -Icore/include -c -o"

echo ""
echo "[OSCA]: Building  LIBC from scratch!"
for file in include/src/libc/*.c; do
  if [ -f "$file" ]; then
    base_name=$(basename "$file" .c)
    echo "[OSCA  LIBC]: Compiling $file source!"
    $C_COMPILER   $CFLAGS "obj/include/libc/${base_name}.o" "$file"
  fi
done

for file in include/src/libc/extras/*.c; do
  if [ -f "$file" ]; then
    base_name=$(basename "$file" .c)
    echo "[OSCA  LIBC]: Compiling $file source!"
    $C_COMPILER   $CFLAGS "obj/include/libc/extras/${base_name}.o" "$file"
  fi
done

echo "[OSCA]: Successfully builded  LIBC from scratch!"
# LIBCC
CC_COMPILER="clang++"
CFLAGS="-static -target i686-none-elf -nostdlib -Iinclude/libcc -c -o"

echo ""
echo "[OSCA]: Building LIBCC from scratch!"
for file in include/src/libcc/*.cc; do
  if [ -f "$file" ]; then
    base_name=$(basename "$file" .cc)
    echo "[OSCA LIBCC]: Compiling $file source!"
    $CC_COMPILER $CCFLAGS "obj/include/libcc/${base_name}.o" "$file"
  fi
done

echo "[OSCA]: Successfully builded LIBCC from scratch!"
echo ""