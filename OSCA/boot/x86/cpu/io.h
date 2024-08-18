#ifndef __OSCA_BOOT_X86_CPU_IO_H__
#  include <stddef.h>
#  include <stdint.h>
   extern  uint8_t  inb(uint16_t port);
   extern uint16_t  inw(uint16_t port);
   extern uint32_t  inl(uint16_t port);

   extern     void outb(uint16_t port,  uint8_t value);
   extern     void outw(uint16_t port, uint16_t value);
   extern     void outl(uint16_t port, uint32_t value);
#  define __OSCA_BOOT_X86_CPU_IO_H__                1
#endif