#ifndef __OSCA_X86_FPU_API_H__
#  include <stdbool.h>
#  include <stdint.h>
   extern void __kfpu_beg(void);
   extern void __kfpu_end(void);
   extern void   kfpu_beg(void);
   extern void   kfpu_end(void);
   extern bool irq_fpu_us(void);
   
   extern int cpu_has_xft(u64 xft_mask, const char **ft_name);
#  define __OSCA_X86__FPU_API_H__                       1
#endif