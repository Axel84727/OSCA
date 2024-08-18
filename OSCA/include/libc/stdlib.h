#ifndef __OSCA_LIBC_STDLIB_H__
#  include <stddef.h>

#  if DEBUG
#    include <stdio.h>
#    if __STDC_VERSION__ <= 199409L
#      define assert( _c, _v, _f ) \
         if ( !(_c) ) { do { fprintf( \
            stderr, __ASSERTION_MESSAGE__, _v, _f, __FILE__, __LINE__ \
         );   } while(0); }
#    else
#      define assert( _c, _v     ) \
    if ( !(_c) ) { do { fprintf( \
      stderr, __ASSERTION_MESSAGE__, _v, __FUNC__, __FILE__, __LINE__ \
    ); } while(0); }
#    endif
#  else
#    define assert( _c, _v, ... ) ((void)0x0000)
#  endif

   extern void*  malloc( size_t s           );
   extern void* realloc( void* p, size_t s  );
   extern void*  calloc( size_t s, size_t e );
   extern void     free( void*  p           );

   extern int               atoi(const char *);
   extern long              atol(const char *);
   extern double            atof(const char *);
   extern long            strtol(const char *, char **, int);
   extern unsigned long  strtoul(const char *, char **, int);
#  if  __STDC_VERSION__ <= 199409L
#    define atoll       atol
#    define strtoll   strtol
#    define strtoull strtoul
#  else
   extern long long             atoll(const char *);
   extern long long           strtoll(const char *, char **, int);
   extern unsigned long long strtoull(const char *, char **, int);
#  endif

#  define __OSCA_LIBC_STDLIB_H__            1
#endif