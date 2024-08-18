extern void terminal_writestring(const char*);

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <string.h>
#include <pmm/pmm.h>

#if !defined( __KERNEL_START_ADDRESS__ ) && !defined( __KERNEL_END_ADDRESS__ )
#  if    __POINTER_SIZE__ == 2
#    define __KERNEL_START_ADDRESS__  0x00000000
#    define  __KERNEL_END_ADDRESS__   0x00003FFF
#  elif  __POINTER_SIZE__ == 4
#    define __KERNEL_START_ADDRESS__  0x00100000
#    define  __KERNEL_END_ADDRESS__   0x3FFFFFFF
#  elif  __POINTER_SIZE__ == 8
#    define __KERNEL_START_ADDRESS__  0x00100000
#    define  __KERNEL_END_ADDRESS__   0xBFFFFFFF
#  endif
#endif

#if !defined( __USER_START_ADDRESS__ ) && !defined( __USER_START_ADDRESS__ )
#  if    __POINTER_SIZE__ == 2
#    define __USER_START_ADDRESS__    0x0000000000004000
#    define  __USER_END_ADDRESS__     0x000000000000FFFF
#  elif  __POINTER_SIZE__ == 4
#    define __USER_START_ADDRESS__    0x0000000000400000
#    define  __USER_END_ADDRESS__     0x0000000000600000
#  elif  __POINTER_SIZE__ == 8
#    define __USER_START_ADDRESS__    0x00000000C0000000
#    define  __USER_END_ADDRESS__     0x0007FFFFFFFFFFFF
#  endif
#endif

#if !defined( BFNUM ) && !defined( AFNUM )
#  if    __POINTER_SIZE__ == 2
#    define BFNUM    0xBFDA
#    define AFNUM    0xAFDB
#  elif  __POINTER_SIZE__ == 4
#    define BFNUM    0xDBEEFADA
#    define AFNUM    0xBEEFDAAD
#  elif  __POINTER_SIZE__ == 8
#    define BFNUM    0xADEADBEEFADEADDA
#    define AFNUM    0xABEEFDEADADADEDA
#  endif
#endif

static const size_t heap = (size_t)(__USER_START_ADDRESS__ - sizeof(struct pm_region_t));

static bool umap_init = true;

void *malloc(size_t sz) {
    if (umap_init) {
        // Verifica la dirección de inicio y el tamaño
        if (__USER_START_ADDRESS__ - sizeof(struct pm_region_t) >= __USER_END_ADDRESS__) {
            return NULL; // Error: dirección de inicio es demasiado cercana al final
        }

        // Inicializa el heap
        if (!mmap_init(heap, __USER_START_ADDRESS__,
                       (size_t)(__USER_END_ADDRESS__ - __USER_START_ADDRESS__),
                       (size_t)(__USER_END_ADDRESS__ - __USER_START_ADDRESS__),
                       (uintptr_t)( REG_ALLOC | ( USER_BLK << (__bit_sizeof(uintptr_t) >> 1) ) ),
                       BFNUM, AFNUM, (void*)(&malloc), " ")) {
            return NULL; // Error: mmap_init falló
        }
        umap_init = false;
    }

    return mmap_alloc(heap, sz, (void*)(&malloc), " ");
}

void *realloc(void* ptr, size_t sz) {
    if (umap_init) {
        // Verifica la dirección de inicio y el tamaño
        if (__USER_START_ADDRESS__ - sizeof(struct pm_region_t) >= __USER_END_ADDRESS__) {
            return NULL; // Error: dirección de inicio es demasiado cercana al final
        }

        // Inicializa el heap
        if (!mmap_init(heap, __USER_START_ADDRESS__,
                       (size_t)(__USER_END_ADDRESS__ - __USER_START_ADDRESS__),
                       (size_t)(__USER_END_ADDRESS__ - __USER_START_ADDRESS__),
                       (uintptr_t)( REG_ALLOC | ( USER_BLK << (__bit_sizeof(uintptr_t) >> 1) ) ),
                       BFNUM, AFNUM, (void*)(&malloc), " ")) {
            return NULL; // Error: mmap_init falló
        }
        umap_init = false;

      return mmap_realloc(heap, ptr, sz, (void*)(&realloc), " ");
    }

  return mmap_realloc(heap, ptr, sz, (void*)(&realloc), " ");
}

void free(void* ptr) {
  if (umap_init) {
    mmap_init(heap, __USER_START_ADDRESS__, \
      (size_t)(__USER_END_ADDRESS__ - __USER_START_ADDRESS__) >> 2, \
      (size_t)(__USER_END_ADDRESS__ - __USER_START_ADDRESS__), \
      (uintptr_t)( REG_ALLOC | ( USER_BLK << (__bit_sizeof(uintptr_t) >> 1) ) ), \
      BFNUM, AFNUM, (void*)(&realloc), " " );
    umap_init = false;
  }

  return mmap_free(heap, ptr, &free, " ");
}