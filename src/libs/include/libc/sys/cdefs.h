#ifndef __OSCA_LIBC_SYS_CDEFS_H__
#  include <libc/stddef.h> /* For __POINTER_SIZE__ */
#  include <libc/stdbool.h>
#  ifndef __cdefs_macros_defined
#    define __bit_sizeof( _t ) ( sizeof( _t ) << 3 )
#    define __align_to( _n, _al ) ( ( ( _n ) + ( _al ) - 1 ) & ~( ( _al ) - 1 ) )
#    define __align( _n ) __align_to( _n, __POINTER_SIZE__ )
#    ifdef __GNUC__
#      define __packed __attribute__( ( packed ) )
#    else
#      define __packed        
#    endif
#    define __cdefs_macros_defined                 TRUE
#  endif
#  define __OSCA_LIBC_SYS_CDEFS_H__             TRUE
#endif