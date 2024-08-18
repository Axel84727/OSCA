#ifndef __OSCA_BOOT_X86_MEMORY_PMM_H__
#  include <stdbool.h>
#  include <stdint.h>
#  include <stddef.h>
   extern bool  initStack(uint16_t segment, uintptr_t addr);
   extern void   *smalloc(size_t sof);
   extern void  *srealloc(void *ptr, size_t sof);
   extern void      sfree(void *ptr);
#  define __OSCA_BOOT_X86_MEMORY_PMM_H__            1
#endif