#ifndef __OSCA_LIBC_STDIO_H__
#  include <stddef.h>
#  include <stdarg.h>

   typedef struct _file FILE;

   int    printf(const char *fmt, ...);
   int   sprintf(char *str, const char *fmt, ...);
   int  snprintf(char *str, size_t n, const char *fmt, ...);
   int   vprintf(char *str, const char *fmt, va_list args);
   int vsnprintf(char *str, size_t n, const char *fmt, va_list args);
   int  fprintf(FILE *stm, const char *fmt, ...);
  
   extern FILE* stderr;
   extern FILE*  stdin;
   extern FILE* stdout;

#  define fprintf( a, b, ... ) (void)0
#  define stderr  0

#  define __OSCA_LIBC_STDIO_H__                 1
#endif