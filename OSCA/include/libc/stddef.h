#ifndef __OSCA_LIBC_STDDEF_H__
#  ifndef __POINTER_SIZE__
#    if   __POINTER_WIDTH__ == 16 || __SIZEOF_POINTER__ == 2
#      define __POINTER_SIZE__           2
#    elif __POINTER_WIDTH__ == 32 || __SIZEOF_POINTER__ == 4
#      define __POINTER_SIZE__           4
#    elif __POINTER_WIDTH__ == 64 || __SIZEOF_POINTER__ == 8
#      define __POINTER_SIZE__           8
#    else
#      define __POINTER_SIZE__           1
#    endif
#  endif

#  ifndef __SIZEOF_POINTER__
#    define __SIZEOF_POINTER__ __POINTER_SIZE__
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

#  ifdef __PTRDIFF_TYPE__
#    undef __PTRDIFF_TYPE__
#  endif
#  define  __PTRDIFF_TYPE__ \
                    unsigned __SIZE_TYPE__

   typedef unsigned __SIZE_TYPE__  size_t;
   typedef          __SIZE_TYPE__ ssize_t;

   typedef  __PTRDIFF_TYPE__    ptrdiff_t;

#  ifndef NULL
#    if defined( __cplusplus )
#      define NULL                      0L
#    else
#      define NULL             ((void*)0L)
#    endif
#  endif
#  define __OSCA_LIBC_STDDEF_H__         1
#endif