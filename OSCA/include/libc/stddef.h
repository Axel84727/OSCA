#ifndef __OSCA_LIBC_STDDEF_H__
#  ifndef __POINTER_SIZE__
#    if   __POINTER_WIDTH__ == 16
#      define __POINTER_SIZE__           2
#    elif __POINTER_WIDTH__ == 32
#      define __POINTER_SIZE__           4
#    elif __POINTER_WIDTH__ == 64
#      define __POINTER_SIZE__           8
#    else
#      define __POINTER_SIZE__           1
#    endif
#  endif

#  ifdef __SIZE_TYPE__
#    undef __SIZE_TYPE__
#  endif

#  if   __POINTER_SIZE__ <= 2
#    define __SIZE_TYPE__            short
#  elif __POINTER_SIZE__ == 4
#    define __SIZE_TYPE__              int
#  elif __POINTER_SIZE__ == 8
#    if __STDC_VERSION__ <= 199409L
#      define __SIZE_TYPE__       long int
#    else
#      define __SIZE_TYPE__  long long int
#    endif
#  endif

   typedef unsigned __SIZE_TYPE__  size_t;
   typedef          __SIZE_TYPE__ ssize_t;

#  ifndef NULL
#    if defined( __cplusplus )
#      define NULL                      0L
#    else
#      define NULL             ((void*)0L)
#    endif
#  endif
#  define __OSCA_LIBC_STDDEF_H__         1
#endif