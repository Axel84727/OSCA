#ifndef __OSCA_BOOT_X86_BOOT_H__
#  include <stdint.h>

#  define BOOT_SECTOR_SIZE 512
#  define BOOT_ENTRY_ADDR  0x7C00

#  define REG_CR0     read_crn(0)
#  define REG_CR3     read_crn(3)
#  define REG_CR4     read_crn(4)

#  define GDT_ADDR   &gdt_ptr
#  define IDT_ADDR   &idt_ptr

#  include <x86/DTables/gdt.h>
#  include <x86/DTables/idt.h>
#  include <x86/memory/pmm.h>

#  define __OSCA_BOOT_X86_BOOT_H__              1
#endif