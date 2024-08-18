#ifndef __OSCA_LIBC_STRING_H__
#  include <stdbool.h>
#  include <stddef.h>
#  include <stdint.h>

  extern size_t              wcslen( const char* buf                                  );
  extern size_t              strlen( const char* buf                                  );
  extern void*               memcpy( void* dest, const void* src, size_t n            );
  extern void*               memset( void* dest, int c, size_t count                  );
  extern int                 memcmp( const void* buf1, const void* buf2, size_t count );
  extern int                 strcmp( const char* buf, const char* buf2                );
  extern char*               strchr( const char* buf, int c                           );
  extern char*               strtok(       char* str, const char* delim               );

#  define  strcpy( _dest, _src     ) \
                 ((char*)memcpy( (void*)(&_dest), (void*)(&_src), strlen(_src) ))

#  define strncpy( _dest, _src, _n ) \
                 ((char*)memcpy( (void*)(&_dest), (void*)(&_src), _n ))
#  define __OSCA_LIBC_STRING_H__
#endif