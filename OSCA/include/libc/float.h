#ifndef __OSCA_LIBC_FLOAT_H__
#  include <stdint.h>
#  include <sys/cdefs.h>
#  if !defined(flt) && !defined(dbl) && !defined(ldbl)
#    define flt  float
#    define dbl double
#    if __STDC_VERSION__ <= 199409L
#      define ldbl      double
#    else
#      define ldbl long double
#    endif
#  endif

#  if !defined(i8) && !defined(i16) && !defined(i32) && !defined(i64)
#    define  i8  char
#    define i16 short
#    define i32   int
#    if __STDC_VERSION__ <= 199409L
#      define i64      long int
#    else
#      define i64 long long int
#    endif
#  endif

#  if __POINTER_SIZE__ >= 4 || (__SIZEOF_FLOAT__ >= 4 && __SIZEOF_DOUBLE__ >= 8)
#    define __NAN_INFINITY_SUPPORTED__              1
#  else
#    define __NAN_INFINITY_SUPPORTED__              0
#  endif

#  if __NAN_INFINITY_SUPPORTED__
   typedef union __float_repr_t {
      flt x;
      i32 y;
      struct {
#     if __LITTLE_ENDIAN__
        i8  s :  1;
        i8  e :  8;
        i32 m : 23;
#     else
        i32 m : 23;
        i8  e :  8;
        i8  s :  1;
#    endif
      } fpc;
   } __flt_repr_t;
#  else
   typedef union __float_repr_t {
      flt x;
      i16 y;
      struct {
#     if __LITTLE_ENDIAN__
        i8  s :  1;
        i8  e :  4;
        i16 m : 11;
#     else
        i16 m : 11;
        i8  e :  4;
        i8  s :  1;
#     endif
      } fpc;
   } __flt_repr_t;
#  endif

#  if __NAN_INFINITY_SUPPORTED__
   typedef union __double_repr_t {
      dbl x;
      i64 y;
      struct {
#     if __LITTLE_ENDIAN__
        i8  s :  1;
        i16 e : 11;
        i64 m : 52;
#     else
        i64 m : 52;
        i16 e : 11;
        i8  s :  1;
#     endif
      } fpc;
   } __dbl_repr_t;
#  else
   typedef union __double_repr_t {
      dbl x;
      i32 y;
      struct {
#     if __LITTLE_ENDIAN__
        i8  s :  1;
        i8  e :  8;
        i32 m : 23;
#     else
        i32 m : 23;
        i8  e :  8;
        i8  s :  1;
#     endif
      } fpc;
   } __dbl_repr_t;
#  endif
#  if __STDC_VERSION__ > 199409L
#    if __NAN_INFINITY_SUPPORTED__
     typedef union __long_double_repr_t {
        ldbl x;
#       if __LITTLE_ENDIAN__
          i64 x1; i64 x2;
#       else
          i64 x2; i64 x1;
#       endif
        struct {
#       if __LITTLE_ENDIAN__
          i64 m  : 64;
          i8  s  :  1;
          i16 e  : 15;
          i32 r1 : 16;
          i32 r0 : 32;
#       else
          i32 r0 : 32;
          i32 r1 : 16;
          i16 e  : 15;
          i8  s  :  1;
          i64 m  : 64;
#       endif
        } fpc;
     } __ldbl_repr_t;
#    else
     typedef union __long_double_repr_t {
        ldbl x;
        i64  y;
        struct {
#       if __LITTLE_ENDIAN__
          i8  s :  1;
          i16 e : 11;
          i64 m : 52;
#       else
          i64 m : 52;
          i16 e : 11;
          i8  s :  1;
#       endif
        } fpc;
     } __ldbl_repr_t;
#    endif
#  else
#    define __long_double_repr_t __double_repr_t
#    define __ldbl_repr_t           __dbl_repr_t
#  endif

#  define  FLT_MIN            1.17549e-38f
#  define  FLT_MAX            3.40282e+38f
#  define  FLT_EPSILON        1.19209e-07f
#  define  FLT_DIG            6
#  define  FLT_ROUNDS         1
#  define  FLT_RADIX          2
#  define  FLT_MANT_DIG      24
#  define  FLT_MIN_EXP     -125
#  define  FLT_MIN_10_EXP   -37
#  define  FLT_MAX_10_EXP    38
#  define  FLT_MAX_EXP      128

#  define  DBL_MIN            2.22507e-308
#  define  DBL_MAX            1.79769e+308
#  define  DBL_EPSILON        2.22045e-16
#  define  DBL_DIG           15
#  define  DBL_MANT_DIG      53
#  define  DBL_MIN_EXP    -1021
#  define  DBL_MIN_10_EXP  -307
#  define  DBL_MAX_10_EXP   308
#  define  DBL_MAX_EXP     1024

#  if __STDC_VERSION__ > 199409L
#    define LDBL_MIN   3.3621e-4932
#    define LDBL_MAX  1.18973e+4932
#    define LDBL_EPSILON 1.0842e-19
#    define LDBL_DIG             18
#    define LDBL_MANT_DIG        64
#    define LDBL_MIN_EXP     -16381
#    define LDBL_MIN_10_EXP   -4931
#    define LDBL_MAX_10_EXP    4932
#    define LDBL_MAX_EXP      16384
#  else
#    define LDBL_MIN         DBL_MIN
#    define LDBL_MAX         DBL_MAX
#    define LDBL_EPSILON     DBL_EPSILON
#    define LDBL_DIG         DBL_DIG
#    define LDBL_MANT_DIG    DBL_MANT_DIG
#    define LDBL_MIN_EXP     DBL_MIN_EXP
#    define LDBL_MIN_10_EXP  DBL_MIN_10_EXP
#    define LDBL_MAX_10_EXP  DBL_MAX_10_EXP
#    define LDBL_MAX_EXP     DBL_MAX_EXP
#  endif

   /* 
    * Builds an INFINITY value from scratch,
    * if not supported then build an special
    * mask that represent these values
    * 
    * \return an INFINITY special value
    */
   extern __forceinline flt __builtin_buildinf(void);

   /* 
    * Builds a NotANumber value from scratch,
    * if not supported, then build an special
    * mask that represent these values
    * 
    * \return an INFINITY special value
    */
   extern __forceinline flt __builtin_buildnan(void);

#  if __NAN_INFINITY_SUPPORTED__ || !__NAN_INFINITY_SUPPORTED__
#    define NAN      __builtin_buildnan()
#    define INFINITY __builtin_buildinf()
#  endif

#  undef   i8
#  undef  i16
#  undef  i32
#  undef  i64
#  undef  flt
#  undef  dbl
#  undef ldbl
#  define __OSCA_LIBC_FLOAT_H__                     1
#endif