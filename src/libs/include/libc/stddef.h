#ifndef __OSCA_LIBC_STDDEF_H__
#  include <libc/stdbool.h>

#  if   defined( __i386__   ) || defined( __arm__     ) \
   ||   defined( __powerpc__   ) || defined( __ppc__   ) || defined( __riscv   )
#    define __POINTER_SIZE__        4
#  elif defined( __x86_64__ ) || defined( __aarch64__ ) \
   ||   defined( __powerpc64__ ) || defined( __ppc64__ ) || defined( __riscv64 )
#    define __POINTER_SIZE__        8
#  elif defined( __x86_16__ ) || defined( __m68k__ )
#    define __POINTER_SIZE__        2
#  else
#    define __POINTER_SIZE__        1
#  endif

#  if !defined( __platform_types_defined )
/* Tecnicamente una CPU hipotetica de 8 bits
   tendria que manejar 64 KB como minimo debido a los
   estandares que impiden un limite tan despreciable como 255 bytes */
#    if __POINTER_SIZE__ == 1 || __POINTER_SIZE__ == 2
#      define __SIZE_TYPE__                      short
/* Una CPU de 32 bits maneja 4 GB generalmente */
#    elif __POINTER_SIZE__ ==  4
#      define __SIZE_TYPE__                        int
/* Una CPU de 64 bits maneja hasta un limite
   teorico de 16 EB, aunque en la practica nunca se
   alcanza por las restricciones fisicas de los
   componentes */
#    elif __POINTER_SIZE__ ==  8
#      if defined( __STDC__ )
#        define __SIZE_TYPE__                 long int
#      else
#        define __SIZE_TYPE__            long long int
#      endif
#    endif
#    define __platform_types_defined              TRUE
#  endif

/* __SIZE_TYPE__ contiene el tamano mas optimizado 
   dependiendo de la arquitectura de la CPU 
   (8, 16, 32 o 64 bits) */
   typedef unsigned __SIZE_TYPE__  size_t,  ptrdiff_t;
   typedef   signed __SIZE_TYPE__             ssize_t;

#  ifndef NULL
#    if !defined( __cplusplus )
#      define NULL                     ( ( void* )0L )
#    else
#      define NULL                                  0L
#    endif
#  endif

#  if defined( __cplusplus )
#    if __cplusplus < 201103L
#      define nullptr                             NULL
#    endif
#  else
#    define   nullptr                             NULL
#  endif

#  ifndef offsetof
/* Macro que obtiene el desplazamiento de un miembro
   en una estructura/union de tipo _m */
#    define offsetof( _t, _m ) \
                 (ptrdiff_t)( &( ( (_t*)NULL )->_m ) )
#  endif

#  define __OSCA_LIBC_STDDEF_H__                  TRUE
#endif