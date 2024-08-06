#include <libc/stdarg.h>
#include <libc/stdint.h>
#include <libc/stddef.h>
#include <libc/stdlib.h>
#include <libc/vector.h>

#ifdef __stdarg_internal_defined
  struct __va_list {
    intptr_t*  saddr;
    ptrdiff_t offset : ( __bit_sizeof( ptrdiff_t ) - 1 );
    bool      isnull : 1;
  } __packed; /* sizeof( struct __va_list ) = ( __POINTER_SIZE__ * 2 ) */

  static struct vector __va_lists;

  static size_t i, sz;

  void __va_start( va_list a1, size_t a2 ) {
    if ( a1 == NULL || a2 == 0 ) { return; }

    if ( __va_lists.size == 0 ) { initv( &__va_lists, sizeof( struct __va_list ) * __POINTER_SIZE__ ) }

    struct __va_list              out;
    out.saddr  =    (intptr_t*)( a1 );
    out.offset =    (ptrdiff_t)( a2 );
    out.isnull = (bool)( a1 == NULL );

    struct __va_list* vl = findv( __va_lists, out );
    if ( vl != NULL ) {
      if ( vl->isnull ) {
        popbv( __va_lists, void );
      }

      return;
    }

    pushbv( __va_lists, out );
  }

  void*  __va_arg( va_list* a1, size_t a2 ) {
    if ( a1 == NULL || a2 == 0 || __va_lists.arr == NULL ) { return NULL; }

    struct __va_list* sm = NULL;
    i = 0;
    sz = __va_lists.size / sizeof( struct __va_list );
#   if __POINTER_SIZE__ == 2
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i     ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i     ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i     ] );
        }
  
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 1 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 1 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 1 ] );
        }
      }
#   elif __POINTER_SIZE__ == 4
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i     ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i     ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i     ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 1 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 1 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 1 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 2 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 2 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 2 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 3 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 3 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 3 ] );
        }
      }
#   elif __POINTER_SIZE__ == 8
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i     ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i     ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i     ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 1 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 1 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 1 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 2 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 2 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 2 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 3 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 3 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 3 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 4 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 4 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 4 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 5 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 5 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 5 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 6 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 6 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 6 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 7 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 7 ].offset     ) == (ptrdiff_t*)( *a1 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 7 ] );
        }
      }
#   endif
    for ( ; i < sz; i++ ) {
      if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i ].saddr + \
             (struct __va_list*)( __va_lists.arr )[ i ].offset    ) == (ptrdiff_t*)( *a1 ) ) {
        sm = &( (struct __va_list*)( __va_lists.arr )[ i ] );
      }
    }

    if ( sm == NULL ) { return NULL; }

    sm->offset += a2;
    byte* out = (byte*)( *a1 + a2 );
    *a1 += a2;
    return out;
  }

  void   __va_end( va_list a0            ) {
    if ( a0 == NULL || __va_lists.arr == NULL ) { return NULL; }

    struct __va_list* sm = NULL;
    i = 0;
    sz = __va_lists.size / sizeof( struct __va_list );
#   if __POINTER_SIZE__ == 2
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i     ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i     ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i     ] );
        }
  
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 1 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 1 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 1 ] );
        }
      }
#   elif __POINTER_SIZE__ == 4
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i     ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i     ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i     ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 1 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 1 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 1 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 2 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 2 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 2 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 3 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 3 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 3 ] );
        }
      }
#   elif __POINTER_SIZE__ == 8
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i     ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i     ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i     ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 1 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 1 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 1 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 2 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 2 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 2 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 3 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 3 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 3 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 4 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 4 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 4 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 5 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 5 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 5 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 6 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 6 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 6 ] );
        }

        if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i + 7 ].saddr  + \
               (struct __va_list*)( __va_lists.arr )[ i + 7 ].offset     ) == (ptrdiff_t*)( a0 ) ) {        
          sm = &( (struct __va_list*)( __va_lists.arr )[ i + 7 ] );
        }
      }
#   endif
    for ( ; i < sz; i++ ) {
      if ( (ptrdiff_t*)( (struct __va_list*)( __va_lists.arr )[ i ].saddr + (struct __va_list*)( __va_lists.arr )[ i ].offset ) == (ptrdiff_t*)( a0 ) ) {
        sm = &( (struct __va_list*)( __va_lists.arr )[ i ] );
      }
    }

    if ( sm == NULL ) { return; }

    memset( sm->saddr, 0, sm->offset );
  }
#endif