#ifndef __OSCA_LIBC_LIMITS_H__
#  define   CHAR_MAX                  (127)
#  define   CHAR_MIN                 (-128)
#  define  UCHAR_MAX                  (255)

#  define   SHRT_MAX                (32767)
#  define   SHRT_MIN               (-32768)
#  define  USHRT_MAX                (65535)

#  define    INT_MAX           (2147483647)
#  define    INT_MIN          (-2147483648)
#  define   UINT_MAX           (4294967296)

#  define  LLONG_MAX  (9223372036854775807)
#  define  LLONG_MIN (-9223372036854775808)
#  define ULLONG_MAX (18446744073709551615)
#  if __POINTER_SIZE__ >= 8
#    define LONG_MAX LLONG_MAX
#    define LONG_MIN LLONG_MIN
#  else
#    define LONG_MAX   INT_MAX
#    define LONG_MIN   INT_MIN
#  endif
#  define __OSCA_LIBC_LIMITS_H__                    1
#endif