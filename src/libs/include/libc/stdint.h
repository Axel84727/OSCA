#ifndef __OSCA_LIBC_STDINT_H__
#  include <libc/stdbool.h>
#  if !defined(  __int_types_defined ) \
   && !defined( __uint_types_defined )
#    define   __i8                              char
#    define  __i16                             short
#    define  __i32                               int
#    if defined( __STDC__ )
#      define __i64                         long int
#    else
#      define __i64                    long long int
#    endif

     typedef   signed  __i8      byte,  i8,   int8_t;
     typedef   signed __i16      word, i16,  int16_t;
     typedef   signed __i32     dword, i32,  int32_t;
     typedef   signed __i64     qword, i64,  int64_t;

     typedef unsigned  __i8     ubyte,  u8,  uint8_t;
     typedef unsigned __i16     uword, u16, uint16_t;
     typedef unsigned __i32    udword, u32, uint32_t;
     typedef unsigned __i64    uqword, u64, uint64_t;

/* Definidos como macros para mantener la compatibilidad con C++ (no forman parte del estandar C) */
#    define   char16_t int16_t
#    define   char32_t int32_t
#    define   char64_t int64_t

#    if __POINTER_SIZE__ <= 2
#      define wchar_t  int16_t
#    elif __POINTER_SIZE__ == 4
#      define wchar_t  int32_t
#    else
#      define wchar_t  int64_t
#    endif

#    define  __int_types_defined                TRUE
#    define __uint_types_defined                TRUE
#  endif
#  define __OSCA_LIBC_STDINT_H__                TRUE
#endif