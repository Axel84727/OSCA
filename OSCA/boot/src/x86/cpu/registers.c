#include <x86/cpu/registers.h>

static struct cpu16r dumpCode16(void) {
  struct cpu16r reg;
  asm volatile(
    "movw %%ax, %0\n\t" /* Store AX in reg.regs[0] */
    "movw %%bx, %1\n\t" /* Store BX in reg.regs[1] */
    "movw %%cx, %2\n\t" /* Store CX in reg.regs[2] */
    "movw %%dx, %3\n\t" /* Store DX in reg.regs[3] */

    "movw %%si, %4\n\t" /* Store SI in reg.regs[4] */
    "movw %%di, %5\n\t" /* Store DI in reg.regs[5] */
    "movw %%bp, %6\n\t" /* Store BP in reg.regs[6] */
    "call 1f\n\t" /* Label used to push IP to stack */
    "1:\n\tpopw %7\n\t" /* Store IP in reg.regs[7] */
    "movw %%sp, %8\n\t" /* Store SP in reg.regs[8] */

    "movw %%cs, %9\n\t" /* Store CS in reg.regs[9] */
    "movw %%ds, %10\n\t" /* Store DS in reg.regs[10] */
    "movw %%es, %11\n\t" /* Store ES in reg.regs[11] */
    "movw %%fs, %12\n\t" /* Store FS in reg.regs[12] */
    "movw %%gs, %13\n\t" /* Store GS in reg.regs[13] */
    "movw %%ss, %14\n\t" /* Store SS in reg.regs[14] */

    : "=m"(reg.regs[0]),
      "=m"(reg.regs[1]),
      "=m"(reg.regs[2]),
      "=m"(reg.regs[3]),
      "=m"(reg.regs[4]),
      "=m"(reg.regs[5]),
      "=m"(reg.regs[6]),
      "=m"(reg.regs[7]),
      "=m"(reg.regs[8]),
      "=m"(reg.regs[9]),
      "=m"(reg.regs[10]),
      "=m"(reg.regs[11]),
      "=m"(reg.regs[12]),
      "=m"(reg.regs[13]),
      "=m"(reg.regs[14])
    :
    : "memory"
  );

  return reg;
}

#if defined(__i386__) || __POINTER_SIZE__ >= 4
static struct cpu32r dumpCode32(void) {
  struct cpu32r reg;
  asm volatile(
    "movl %%eax, %0\n\t" /* Store EAX in reg.regs[0] */
    "movl %%ebx, %1\n\t" /* Store EBX in reg.regs[1] */
    "movl %%ecx, %2\n\t" /* Store ECX in reg.regs[2] */
    "movl %%edx, %3\n\t" /* Store EDX in reg.regs[3] */
    "movl %%esi, %4\n\t" /* Store ESI in reg.regs[4] */
    "movl %%edi, %5\n\t" /* Store EDI in reg.regs[5] */
    "movl %%ebp, %6\n\t" /* Store EBP in reg.regs[6] */
    "call 1f\n\t" /* Label used to push IP to stack */
    "1:\n\tpopl %7\n\t"  /* Store EIP in reg.regs[7] */
    "movl %%esp, %8\n\t" /* Store ESP in reg.regs[8] */
    : "=m"(reg.regs[0]),
      "=m"(reg.regs[1]),
      "=m"(reg.regs[2]),
      "=m"(reg.regs[3]),
      "=m"(reg.regs[4]),
      "=m"(reg.regs[5]),
      "=m"(reg.regs[6]),
      "=m"(reg.regs[7]),
      "=m"(reg.regs[8])
    :
    : "memory"
  );

  return reg;
}
#endif

#if defined(__x86_64__) || __POINTER_SIZE__ == 8
static struct cpu64r dumpCode64(void) {
  struct cpu64r reg;
  asm volatile(
    "movq %%rax, %0\n\t" /* Store RAX in reg.regs[0] */
    "movq %%rbx, %1\n\t" /* Store RBX in reg.regs[1] */
    "movq %%rcx, %2\n\t" /* Store RCX in reg.regs[2] */
    "movq %%rdx, %3\n\t" /* Store RDX in reg.regs[3] */
    "movq %%rsi, %4\n\t" /* Store RSI in reg.regs[4] */
    "movq %%rdi, %5\n\t" /* Store RDI in reg.regs[5] */
    "movq %%rbp, %6\n\t" /* Store RBP in reg.regs[6] */
    "call 1f\n\t" /* Label used to push IP to stack */
    "1:\n\tpopq %7\n\t"  /* Store EIP in reg.regs[7] */
    "movl %%rsp, %8\n\t" /* Store RSP in reg.regs[8] */
    : "=m"(reg.regs[0]),
      "=m"(reg.regs[1]),
      "=m"(reg.regs[2]),
      "=m"(reg.regs[3]),
      "=m"(reg.regs[4]),
      "=m"(reg.regs[5]),
      "=m"(reg.regs[6]),
      "=m"(reg.regs[7]),
      "=m"(reg.regs[8])
    :
    : "memory"
  );

  return reg;
}
#endif

struct cpur dumpCPU(void) {
}