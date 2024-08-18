#ifndef __OSCA_CORE_PMM_H__
#  include <stdbool.h>
#  include <stddef.h>
#  include <stdint.h>

#  define CAST2_MDATA(BLK_TYPE, REG_STATUS) \
  ((uintptr_t)BLK_TYPE | ((uintptr_t)REG_STATUS >> (__bit_sizeof(uintptr_t) >> 1)))

#  define CAST2_TYPE(MDATA) \
  ((uintptr_t)MDATA >> (__bit_sizeof(uintptr_t) >> 1))

#  define CAST2_STATUS(MDATA) \
  ((uintptr_t)MDATA ^ CAST2_TYPE(MDATA) )

#  if !defined(KRNL_BLK)  && !defined(USER_BLK) && !defined(DRIV_BLK)  \
   && !defined(REG_UNMAP) && !defined(REG_FREE) && !defined(REG_ALLOC) \
   && !defined(REG_RES)
#    define KRNL_BLK  0
#    define USER_BLK  1
#    define DRIV_BLK  2

#    define REG_UNMAP 0
#    define REG_REL   1
#    define REG_ALLOC 2
#    define REG_RES   3
#  endif

   extern bool   mmap_init(uintptr_t addr, uintptr_t baddr, \
     size_t bsize, size_t rsize, uintptr_t mdata, uintptr_t canary1, uintptr_t canary2);

   extern bool mmap_add_regs(uintptr_t baddr, uintptr_t *regs, size_t sz);
   extern bool mmap_rem_regs(uintptr_t baddr, uintptr_t *regs, size_t sz);

   extern void   *mmap_alloc(uintptr_t addr, size_t size, void *func, const char *name);
   extern void *mmap_realloc(uintptr_t addr, void *ptr, size_t size, void *func, const char *name);
   extern void     mmap_free(uintptr_t addr, void *ptr, void *func, const char *name);

   extern bool mmap_release(uintptr_t baddr, void *func);

   extern ptrdiff_t mmap_installed_sys(void);
#  define __OSCA_CORE_PMM_H__               1
#endif