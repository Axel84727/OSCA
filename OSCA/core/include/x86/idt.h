#ifndef __OSCA_X86_IDT_H__
#  include <stdint.h>
   extern struct idt_entry;

   extern uint16_t get_idt_length(void);
   extern void     set_idt_length(uint16_t len);
   extern struct idt_entry get_idx_entry(uint16_t index);
   extern void set_idt_entry(uint16_t index, uint32_t base, uint16_t selector, uint8_t type_attr);
   extern void      idt_init(void);
   extern void     idt_clean(void);
#  define __OSCA_X86_IDT_H__                1
#endif