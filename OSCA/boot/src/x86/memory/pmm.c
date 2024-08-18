#include <x86/memory/pmm.h>

static uintptr_t  saddr; /* Stack address */
static uintptr_t osaddr; /* Original stack address */

bool initStack(uintptr_t segment, uintptr_t addr) {
  if (!addr || addr > 0xFFFF || !segment) { return true; }

  asm volatile("movw %%sp, %0\n" : "=r"(osaddr));

  asm volatile("movw %0, %%ax\n" /* Move SS to AX */
               "movw %%ax, %%ss\n" /* Move AX value to SS */
               "movw %1, %%sp\n" /* Load SP at SP */
               :
               : "r"(segment), "r"(addr)
               : "ax", "memory" );

}