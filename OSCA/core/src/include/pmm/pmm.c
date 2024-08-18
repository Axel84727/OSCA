extern void terminal_writestring(const char*);
#include <pmm/pmm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct pm_block_t {
  uintptr_t canary1;
  size_t prev_size;
  size_t size : (__bit_sizeof(size_t) - 1);
  bool   free : 1;
  uintptr_t canary2;

  struct pm_block_t* prev;
  struct pm_block_t* next;
} __packed;

struct pm_region_t {
  uintptr_t region_addr;
  union {
    struct {
#     if __LITTLE_ENDIAN__
      uintptr_t block_type   : (__bit_sizeof(uintptr_t) >> 1);
      uintptr_t block_status : (__bit_sizeof(uintptr_t) >> 1);
#     else
      uintptr_t block_status : (__bit_sizeof(uintptr_t) >> 1);
      uintptr_t block_type   : (__bit_sizeof(uintptr_t) >> 1);
#     endif
    } __packed;

    uintptr_t region_mdata;
  } __packed;

  size_t region_size;
  bool authorized; struct { uintptr_t *regs; size_t length; } __packed authorized_regs;
} __packed;

bool mmap_init(uintptr_t addr, uintptr_t baddr, size_t bsize, size_t rsize, uintptr_t mdata, uintptr_t canary1, uintptr_t canary2) {
    struct pm_region_t *reg = (struct pm_region_t *)addr;
    if (!addr || !baddr || bsize < sizeof(struct pm_block_t)) { return false; }
    if (CAST2_STATUS(mdata) == REG_RES && CAST2_TYPE(mdata) != USER_BLK ) { reg->authorized = true; }

    reg->region_addr   = baddr;
    struct pm_block_t *p0 = (struct pm_block_t*)baddr;
    p0->size = bsize - sizeof(struct pm_block_t);
    p0->next = NULL;
    p0->free = true;
    p0->canary1 = canary1;
    p0->canary2 = canary2;

    reg->region_mdata = mdata;
    reg->region_size = rsize;

    return true;
}

bool mmap_add_regs(uintptr_t addr, uintptr_t *regs, size_t length) {
  if (!addr || !regs || !length) { return true; }

  struct pm_region_t *reg = (struct pm_region_t *)(addr);
  if ( reg->block_type == USER_BLK || !reg->authorized \
  ||   reg->block_status == REG_UNMAP || reg->block_status == REG_REL ) { return true; }

  reg->authorized_regs.regs = regs, reg->authorized_regs.length = length;
  return false;
}

bool mmap_rem_regs(uintptr_t addr, uintptr_t *regs, size_t length) {
  if (!addr || !regs || !length) { return true; }

  struct pm_region_t *reg = (struct pm_region_t *)(addr);
  if ( reg->block_type == USER_BLK || !reg->authorized \
  ||   reg->block_status == REG_UNMAP || reg->block_status == REG_REL ) { return true; }

  reg->authorized_regs
}

void *mmap_alloc(uintptr_t addr, size_t size, void *func, const char *name) {
    struct pm_region_t *reg = (struct pm_region_t *)(addr);
    struct pm_block_t* current = (struct pm_block_t *)reg->region_addr;

    while (current) {
        if (current->free && current->size >= size) {
            // Si es necesario, dividir el bloque
            if (current->size > size + sizeof(struct pm_block_t)) {
                struct pm_block_t* new_block = (struct pm_block_t*)((char*)current + sizeof(struct pm_block_t) + size);
                new_block->size = current->size - size - sizeof(struct pm_block_t);
                new_block->next = current->next;
                new_block->free = true;
                new_block->canary1 = current->canary1;
                new_block->canary2 = current->canary2;

                current->size = size;
                current->next = new_block;
            }
            current->free = false;
            return (void*)((char*)current + sizeof(struct pm_block_t));
        }
        current = current->next;
    }

    // No se encontró un bloque adecuado
    return NULL;
}

void *mmap_realloc(uintptr_t addr, void *ptr, size_t size, void *func, const char *name) {
    if (!ptr && addr) {
        return mmap_alloc(addr, size, func, name);
    }

    struct pm_region_t *reg = (struct pm_region_t *)(addr);
    struct pm_block_t* block = (struct pm_block_t*)((char*)ptr - sizeof(struct pm_block_t));

    if (block->size >= size) {
        return ptr; // No se necesita redimensionar
    }

    void* new_ptr = mmap_alloc(addr, size, func, name);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
    }

    return new_ptr;
}

void mmap_free(uintptr_t addr, void *ptr, void *func, const char *name) {
    if (!ptr) { return; }

    struct pm_region_t *reg = (struct pm_region_t*)(addr);
    struct pm_block_t* block = (struct pm_block_t*)((char*)ptr - sizeof(struct pm_block_t));
    block->free = true;

    // Intentar fusionar con el siguiente bloque si es posible
    if (block->next && block->next->free) {
        block->size += sizeof(struct pm_block_t) + block->next->size;
        block->next = block->next->next;
    }

    // Intentar fusionar con el bloque anterior si es posible
    struct pm_block_t* current = (struct pm_block_t *)reg->region_addr;
    while (current) {
        if (current->next == block) {
            if (current->free) {
                current->size += sizeof(struct pm_block_t) + block->size;
                current->next = block->next;
            }
            break;
        }
        current = current->next;
    }
}

bool mmap_release(uintptr_t baddr, void *func) {
  if (!baddr) { return true; }
  struct pm_region_t *p0 = (struct pm_region_t *)(baddr - sizeof(struct pm_region_t));
  if (p0->block_status == REG_REL) { fprintf(stderr, __MMAP_REL_CODE_A__, func); return true; }
  else if (p0->block_status == REG_UNMAP) { fprintf(stderr, __MMAP_REL_CODE_B__, func); return true; }
  else if (p0->block_status == REG_RES) {  }
}

#if defined(__x86_64__) || defined(__i386__) || defined(__i686__)
#  include <x86/pmm/e820.h>

ptrdiff_t mmap_installed_sys(void) {
  return do_e820();  
}
#endif