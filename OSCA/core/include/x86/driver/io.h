#ifndef __OSCA_X86_DRIVER_IO_H__
#  include <sys/cdefs.h>
#  include <stddef.h>
#  include <stdint.h>
#  include <stdbool.h>

   extern __forceinline  void   outb(uint16_t port,  uint8_t value);
   extern __forceinline  void   outw(uint16_t port, uint16_t value);

   extern __forceinline  uint8_t inb(uint16_t port);
   extern __forceinline uint16_t inw(uint16_t port);

   extern __forceinline uint32_t  read_crn(uint8_t reg);
   extern __forceinline void write_crn(uint8_t reg, uint32_t value);

   extern __forceinline uint32_t* read_cpuid(void);
#  define __OSCA_X86_DRIVER_IO_H__              1
#endif