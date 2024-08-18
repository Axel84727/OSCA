#ifndef __OSCA_LIBC_STDINT_H__
#  if !defined(  __int_types_defined ) \
   && !defined( __uint_types_defined )
#    define   __int8                     char
#    define  __int16                    short
#    define  __int32                      int
#    if __STDC_VERSION__ <= 199409L || defined(__GNUC__)
#      define  __int64               long int
#    else
#      define  __int64          long long int
#    endif
#    define  __int_types_defined            1
#    define  __uint8           unsigned  char
#    define __uint16           unsigned short
#    define __uint32           unsigned   int
#    if __STDC_VERSION__ <= 199409L || defined(__GNUC__)
#      define __uint64      long unsigned int
#    else
#      define __uint64 unsigned long long int
#    endif
#    define __uint_types_defined            1
#  endif

   typedef   __int8    int8_t,  i8,   char_t;
   typedef  __int16   int16_t, i16,  short_t;
   typedef  __int32   int32_t, i32,    int_t;
   typedef  __int64   int64_t, i64,   long_t;

   typedef  __uint8   uint8_t,  u8,  uchar_t;
   typedef __uint16  uint16_t, u16, ushort_t;
   typedef __uint32  uint32_t, u32,   uint_t;
   typedef __uint64  uint64_t, u64,  ulong_t;

#  if defined( __INTPTR_TYPE__ ) && defined( __UINTPTR_TYPE__ )
#    undef  __INTPTR_TYPE__
#    undef __UINTPTR_TYPE__
#  endif
#  if   __POINTER_SIZE__ == 4 || __POINTER_WIDTH__ == 32
#    define  __INTPTR_TYPE__          __int32
#    define __UINTPTR_TYPE__         __uint32
#    define  __HLFPTR_TYPE__          __int16
#    define __UHLFPTR_TYPE__         __uint16
#  elif __POINTER_SIZE__ == 8 || __POINTER_WIDTH__ == 64
#    define  __INTPTR_TYPE__          __int64
#    define __UINTPTR_TYPE__         __uint64
#    define  __HLFPTR_TYPE__          __int32
#    define __UHLFPTR_TYPE__         __uint32
#  elif __POINTER_SIZE__ == 2 || __POINTER_WIDTH__ == 16
#    define  __INTPTR_TYPE__          __int16
#    define __UINTPTR_TYPE__         __uint16
#    define  __HLFPTR_TYPE__           __int8
#    define __UHLFPTR_TYPE__          __uint8
#  else
#    define  __INTPTR_TYPE__           __int8
#    define __UINTPTR_TYPE__          __uint8
#    define  __HLFPTR_TYPE__           __int8
#    define __UHLFPTR_TYPE__          __uint8
#  endif

   typedef  __INTPTR_TYPE__   intptr_t, iptr;
   typedef __UINTPTR_TYPE__  uintptr_t, uptr;

   typedef  __HLFPTR_TYPE__  hlfptr_t,  hptr;
   typedef __UHLFPTR_TYPE__ uhlfptr_t, uhptr;

#  define __OSCA_LIBC_STDINT_H__            1
#endif