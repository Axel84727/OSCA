#ifndef __OSCA_LIBC_STRING_H__
#  include <stdbool.h>
#  include <stddef.h>
#  include <stdint.h>

  size_t              strlen( const char* buf                                  );
  void*               memcpy( void* dest, const void* src, size_t n            );
  void*               memset( void* dest, int c, size_t count                  );
  int                 memcmp( const void* buf1, const void* buf2, size_t count );
  int                 strcmp( const char* buf, const char* buf2                );
  char*               strchr( const char* buf, int c                           );
  char*               strtok(       char* str, const char* delim               );

#  define strcpy( _dest, _src ) \
                ((char*)memcpy( (void*)(&_dest), (void*)(&_src), strlen(_src) ))
#  define __OSCA_LIBC_STRING_H__
#endif