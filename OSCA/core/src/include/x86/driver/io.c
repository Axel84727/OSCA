#include <x86/driver/io.h>

void    outb(uint16_t port,  uint8_t value) {
  asm volatile("outb %0, %1\n" : : "a"(value), "Nd"(port));
}

void    outw(uint16_t port, uint16_t value) {
  asm volatile("outw %0, %1\n" : : "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port) {
  uint8_t value;
  asm volatile("inb %1, %0\n" : "=a"(value) : "Nd"(port));
  return value;
}

uint16_t inw(uint16_t port) {
  uint16_t value;
  asm volatile("inw %1, %0\n" : "=a"(value) : "Nd"(port));
  return value;
}

uint32_t read_crn(uint8_t reg) {
  uint32_t cr;
  switch (reg) {
    default: case 0: {
      asm volatile("mov %%cr0, %0\n" : "=r"(cr));
      break;
    }

    case 1: {
      asm volatile("mov %%cr1, %0\n" : "=r"(cr));
      break;
    }

    case 2: {
      asm volatile("mov %%cr2, %0\n" : "=r"(cr));
      break;
    }

    case 3: {
      asm volatile("mov %%cr3, %0\n" : "=r"(cr));
      break;
    }
  }

  return cr;
}

void write_crn(uint8_t reg, uint32_t value) {
  switch ( reg ) {
    default: case 0: {
      asm volatile("mov %0, %%cr0\n" : : "r"(value));
      break;
    }

    case 1: {
      asm volatile("mov %0, %%cr1\n" : : "r"(value));
      break;
    }

    case 2: {
      asm volatile("mov %0, %%cr2\n" : : "r"(value));
      break;
    }

    case 3: {
      asm volatile("mov %0, %%cr3\n" : : "r"(value));
      break;
    }
  }
}

uint32_t* read_cpuid(void) {
  static uint32_t cpuid[4];
  cpuid[0] = 1, cpuid[1] = 1, cpuid[2] = 1, cpuid[3] = 1;
  asm volatile("cpuid\n" : "=a"(cpuid[0]), "=b"(cpuid[1]), "=c"(cpuid[2]), "=d"(cpuid[3]));
  return cpuid;
}
