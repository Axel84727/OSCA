#ifndef __OSCA_BOOT_X86_DTABLES_GDT_H__
#  include <stddef.h>
#  include <stdint.h>
#  include <sys/cdefs.h>
#  define GDT_ADDR gdt_ptr
#  define GDT_SIZE __builtin_gdt_size(gdt_ptr)
#  define GDT_ARGS __builtin_gdt_args(gdt_ptr)

   extern uint64_t *gdt_ptr;
   struct gdt_args { 
    u16 llow, blow; 
    u8 bmid, acc, gra, bhi; 
#   if defined(__x86_64__) || __POINTER_SIZE__ == 8
    u32 res1, bup, res2;
#   endif
   } __packed;
   extern __forceinline size_t __builtin_gdt_size(void *);
   extern __forceinline struct gdt_args __builtin_gdt_args(void *);
   extern __forceinline uint64_t *__builtin_gdt_build(struct gdt_args);

#  define __OSCA_BOOT_X86_DTABLES_GDT_H__               1
#endif