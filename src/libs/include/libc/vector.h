#ifndef __OSCA_LIBC_VECTOR_H__
#  include <libc/stdbool.h>
#  include <libc/stddef.h>
#  include <libc/stdint.h>

  struct vector {
    byte*        arr;
    size_t      size;
    size_t  capacity;
    size_t frontsize;
    size_t  lastsize;
  } __packed;

  EXTC void                      init_vector( struct vector* vec, size_t cap             );
  EXTC void                 push_back_vector( byte* vec, byte* src, size_t n             );
  EXTC void                push_front_vector( byte* vec, byte* src, size_t n             );
  EXTC byte*                 pop_back_vector( byte* vec                                  );
  EXTC byte*                pop_front_vector( byte* vec                                  );
  EXTC void                   destroy_vector( struct vector* vec                         );
  EXTC __forceinline byte*         at_vector( struct vector* vec, size_t idx             );
  EXTC byte*                     find_vector( struct vector* vec, byte* src, size_t size );
  EXTC __forceinline byte*      front_vector( struct vector* vec                         );
  EXTC __forceinline byte*       back_vector( struct vector* vec                         );

#  if !defined( pushb ) && !defined( pushf ) && !defined( popb ) && !defined( popf )
#    define     initv( _v, _s  )                  init_vector( &_v, _s                )
#    define    pushbv( _v, _m  )             push_back_vector( &_v, &_m, sizeof( _m ) )
#    define    pushfv( _v, _m  )            push_front_vector( &_v, &_m, sizeof( _m ) )
#    define     popbv( _v, _t  )   *( (_t*)(  pop_back_vector( &_v                    ) ) )
#    define     popfv( _v, _t  )   *( (_t*)( pop_front_vector( &_v                    ) ) )
#    define  destroyv( _v      )               destroy_vector( &_v                    )
#    define       atv( _v, _i  )                    at_vector( &_v, _i                )
#    define     findv( _v, _m  )                  find_vector( &_v, &_m, sizeof( _m ) )
#    define    frontv( _v, _t  )   *( (_t*)(     front_vector( &_v                    ) ) )
#    define     backv( _v, _t  )   *( (_t*)(      back_vector( &_v                    ) ) )
#  endif
#  define __OSCA_LIBC_VECTOR_H__            TRUE
#endif