#ifndef __OSCA_LIBC_STDARG_H__
#  include <stddef.h>
#  include <stdint.h>
#  include <sys/cdefs.h>
  typedef void *va_list;

  extern void _va_start(va_list *, void *, size_t);
  extern void  *_va_arg(va_list *, size_t);
  extern void   _va_end(va_list *);

/* _bp_##_ap and _sz_bp_##_ap for clean stack with va_end (do not remove) */
#define va_start(AP, LARG) _va_start( &AP, (void *)(&LARG), sizeof(LARG) )

#define   va_arg(AP, TYPE) (*(TYPE *)_va_arg(&AP, sizeof(TYPE)))

#define   va_end(AP)  _va_end(&AP)

#  define __OSCA_LIBC_STDARG_H__            1
#endif