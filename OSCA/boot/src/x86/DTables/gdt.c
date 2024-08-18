#include <x86/DTables/gdt.h>
#include <stdbool.h>
#include <string.h>

struct gdtr { u16 limit; u32 base; } __packed;

struct gdt { struct gdt_args *args; struct gdtr  gdt_ptr; bool builded; } __packed;

static struct gdt GlobalDescriptorTable;

size_t __builtin_gdt_size(void *a0) {
  if (!a0) { return 0; }

  struct gdt *descriptor = (struct gdt *)(a0);

  return (size_t)(descriptor->gdt_ptr.limit - descriptor->gdt_ptr.base);
}

struct gdt_args __builtin_gdt_args(void *a0) {
  if (!a0) { return GlobalDescriptorTable.args; }

  return ((struct gdt *)a0)->args;
}

uint64_t *__builtin_gdt_build(struct gdt_args a0) {
  if (GlobalDescriptorTable.builded) {
    memcpy((void *)&(GlobalDescriptorTable.args), (void *)&a0, sizeof(struct gdt_args));
    return (uint64_t *)&(GlobalDescriptorTable.gdt_ptr);
  }

  if (a0.llow < (a0.blow)) { return NULL; }

  memcpy((void *)&GlobalDescriptorTable.args, (void *)&a0, sizeof(struct gdt_args));
  GlobalDescriptorTable.gdt_ptr.base  = (uintptr_t)&(gdt_ptr);
  GlobalDescriptorTable.gdt_ptr.limit = sizeof(struct gdt)
  return (uint64_t *)&(GlobalDescriptorTable.gdt_ptr);
}