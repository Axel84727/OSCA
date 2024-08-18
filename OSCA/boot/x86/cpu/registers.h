#ifndef __OSCA_BOOT_X86_CPU_REGISTERS_H__
#  include <stdint.h>
#  include <stddef.h>
#  include <sys/cdefs.h>
   struct cpu16r {
      union {
        struct { u8 l, h; } __packed;

        u16 reg; /* 0-3 (4) <=> General purpose, 4-8 (5) <=> Index/pointers (SI, DI, BP, IP, SP), */
      } regs[0x0F]; /* 9-14 (6) <=> Segments (CS;DS;ES;FS;GS;SS) */
   } __packed;

   struct cpu32r {
      union {
        struct { u16 l, h; } __packed;

        u32 reg; /* 0-3 <=> General purpose, 4-8 <=> Index/pointers (SI;DI;BP;IP;SP) */
      } regs[0x09]; /* NOTE: Segments are only 16-bit */
   } __packed;

   struct cpu64r {
      union {
        struct { u32 l, h; } __packed;

        u64 reg; /* 0-3 <=> General purpose, 4-8 <=> Index/pointers (SI;DI;BP;IP;SP) */
      } regs[0x09];
   } __packed;

   struct cpur {
      struct cpu16r code16;
#     if   defined(__i386__) || defined(__x86_64__) || __POINTER_SIZE__ >= 4
      struct cpu32r code32;
#     endif
#     if   defined(__x86_64__) || __POINTER_SIZE__ == 8
      struct cpu64r code64;
#     endif
   } __packed;

   struct cpur dumpCPU(void);
#  define __OSCA_BOOT_X86_CPU_REGISTERS_H__
#endif