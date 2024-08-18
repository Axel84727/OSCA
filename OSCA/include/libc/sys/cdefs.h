#ifndef __OSCA_LIBC_SYS_CDEFS_H__
#  ifndef __compatibility_macros
#    define __attribute                    __attribute__
#    if __STDC_VERSION__ <= 199409L
#      define __forceinline __attribute( (always_inline) )
#    else
#      define __forceinline inline __attribute( (always_inline) )
#    endif
#    define __packed             __attribute( (packed) )
#    define __alignas( _n ) __attribute( (aligned(_n)) )
#    define __align_to( _n, _al ) \
         ( ( ( _n ) + ( _al ) - 1 ) & ~( ( _al ) - 1 ) )
#    define __align( _n ) \
                      __align_to( _n, __POINTER_SIZE__ )
#    ifdef __cplusplus
#      define __extc                          extern "C"
#      define __ext_beg_decl                           {
#      define __ext_end_decl                           }
#    else
#      define __extc                                    
#      define __ext_beg_decl                            
#      define __ext_end_decl                            
#    endif
#    define   __roundup( _v, _m )  (((_v)+_m-1) & ~(_m-1))
#    define __rounddown( _v, _m )  (((_v))    &   ~(_m-1))
#    define __bit_sizeof( _t )   (size_t)(sizeof(_t) << 3)
#    define __compatibility_macros                     1
#  endif
#  define __OSCA_LIBC_SYS_CDEFS_H__                    1
#endif