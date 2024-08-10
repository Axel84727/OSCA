#ifndef __OSCA_LIBC_STDBOOL_H__
#  include <sys/cdefs.h>
#  if !defined( __bool_true_false_are_defined )
#    ifndef __cplusplus
#      if __STDC_VERSION__ <= 199409L
         typedef unsigned char bool;
#        define  true              1
#        define false              0
#      else
         typedef enum boolean {
           false=0,
            true=1
         } __packed bool;
#      endif
#    endif
#    define __bool_true_false_are_defined               1
#  endif

#  define  TRUE                 true
#  define FALSE                false
#  define __SIZEOF_BOOL__                               1
#  define _Bool                 bool
#  define __OSCA_LIBC_STDBOOL_H__                       1
#endif