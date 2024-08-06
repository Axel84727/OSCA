#ifndef __OSCA_LIBC_STDARG_H__
#  include <libc/sys/cdefs.h> /* For EXTC definition */
#  include <libc/stdint.h>
#  include <libc/stddef.h>
#  if !defined( __stdarg_internal_defined )
     typedef void* va_list;

     EXTC void  __va_start( va_list _ap, size_t _rp  );
     EXTC void*   __va_arg( va_list* _ap, size_t _as );
     EXTC void    __va_end( va_list _ap              );
#    define __stdarg_internal_defined        TRUE
#  endif

#  if !defined( __stdarg_external_defined )
#    define va_start( _ap, _rp ) \
                           __va_start( _ap, _rp )
#    define   va_arg( _ap, _as ) \
                            __va_arg( &_ap, _rp )
#    define   va_end( _ap      ) \
                             __va_end( _ap      )
#    define __stdarg_external_defined        TRUE
#  endif

#  define __OSCA_LIBC_STDARG_H__             TRUE
#endif