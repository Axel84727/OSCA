#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>

typedef void *va_list;

static size_t va_size =    0;
static va_list va_ptr = NULL;

void _va_start(va_list *a0, void *a1, size_t a2) {
  if (!a1 && !a2) { return ; }

  va_ptr = *a0;
  *a0 = a1 + __align_to( a2, sizeof(int) );
  va_size = __align_to(a2, sizeof(int));
  return;
}

void *_va_arg(va_list *a0, size_t a1) {
  if (!a0 || !(*a0) || !a1) { return NULL; }

  *a0 += __align_to( a1, sizeof(int) );
  va_size += __align_to(a1, sizeof(int));
  return (void *)(*a0 - a1);
}

void  _va_end(va_list *a0) {
  if (!a0 || !(*a0)) { return ; }

  memset(va_ptr, 0, va_size);
  *a0 = NULL;
}