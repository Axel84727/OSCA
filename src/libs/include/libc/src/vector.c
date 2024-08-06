#include <libc/stdbool.h> /* Defines bool */
#include <libc/stdint.h> /* Defines byte   */
#include <libc/stddef.h> /* Defines size_t */
#include <libc/stdlib.h> /* Defines malloc, realloc, free */
#include <libc/vector.h> /* Defines vector prototype functions */

static size_t i;

void                 init_vector( struct vector* vec, size_t cap               ) {
  if ( vec == NULL ) {
    return;
  } else if ( cap == 0 ) {
    cap = __POINTER_SIZE__;
  }

  cap = __align( cap ); /* Align to __POINTER_SIZE__ */
  vec->arr      = (struct vector*)( malloc( cap ) );
  vec->capacity = cap;
  vec->size     =   0;
}

void            push_back_vector( struct vector* vec, byte* src, size_t n      ) {
       if ( vec == NULL || src == NULL || n == 0 ) { return; }
  else if ( vec->arr == NULL ) { init_vector( vec, n ); }

  n = __align( n ); /* Align to __POINTER_SIZE__ */
  if ( vec->size == vec->capacity || ( vec->size + n ) >= vec->capacity ) {
    byte* cpy = (struct vector*)( malloc( vec->capacity << 1 ) );
    if ( cpy == NULL ) { return; }
    vec->capacity <<= 1;
    memcpy( cpy, vec->arr, vec->size );
    free( vec->arr );
    vec->arr = cpy;
    memcpy( vec->arr + vec->size, src, n );
    if ( vec->size == 0 ) { vec->frontsize = n; }
    vec->size     += n;
    vec->backsize  = n;
    return;
  }

  memcpy( vec->arr + vec->size, src, n );
  if ( vec->size == 0 ) { vec->frontsize = n; }
  vec->size    += n;
  vec->backsize = n;
}

void           push_front_vector( struct vector* vec, byte* src, size_t n      ) {
  if ( vec == NULL || src == NULL || n == 0 ) {
    return;
  } 
  
  n = __align( n ); /* Align to __POINTER_SIZE__ */
  if ( vec->arr == NULL ) { init_vector( vec, n ); }

  if ( vec->size == vec->capacity || ( vec->size + n ) >= vec->capacity \
  ||   ( vec->size + ( n << 1 ) ) >= vec->capacity ) {
    byte* cpy = (struct vector*)( malloc( vec->capacity << 1 ) );
    if ( cpy == NULL ) { return; }
    vec->capacity <<= 1;
    memcpy( cpy + n, vec->arr, vec->size );
    free( vec->arr );
    vec->arr = cpy;
    memcpy( vec->arr, src, n );
    if ( vec->size == 0 ) { vec->lastsize = n; }
    vec->size    += n;
    vec->frontsize = n;
    return;
  }

  memcpy( vec->arr + n, vec->arr, vec->size );
  memcpy( vec->arr, src, n );
  if ( vec->size == 0 ) { vec->lastsize = n; }
  vec->size    += n;
  vec->frontsize = n;
}

byte*            pop_back_vector( struct vector* vec                           ) {
  if ( vec == NULL || vec->size == 0 || vec->backsize == 0 ) { return NULL; }

  byte* cpy = malloc( vec->capacity - vec->backsize );
  if ( cpy == NULL ) { return NULL; }
  memcpy( cpy, vec->arr, vec->size - vec->backsize );
  byte val[ vec->backsize ];
  memcpy( &val, vec->arr + ( vec->size - vec->backsize ), vec->backsize );
  free( vec->arr );
  vec->arr   = cpy;
  vec->size -= vec->backsize;
  return (byte*)( &val );
}

byte*           pop_front_vector( struct vector* vec                           ) {
  if ( vec == NULL || vec->size == 0 || vec->frontsize == 0 ) { return NULL; }

  byte* cpy = malloc( vec->capacity - vec->frontsize );
  if ( cpy == NULL ) { return NULL; }
  memcpy( cpy, vec->arr + vec->frontsize, vec->size - vec->frontsize );
  byte val[ vec->frontsize ];
  memcpy( &val, vec->arr, vec->frontsize );
  free( vec->arr );
  vec->arr   = cpy;
  vec->size -= vec->frontsize;
  return (byte*)( &val );
}

void              destroy_vector( struct vector* vec                           ) {
  if ( vec == NULL || vec->arr == NULL ) { return; }

  free( vec->arr );
  vec->size      = 0;
  vec->frontsize = 0;
  vec->lastsize  = 0;
  vec->capacity  = 0;
}

__forceinline byte*    at_vector( struct vector* vec, size_t idx ) {
  if ( vec == NULL || vec->arr == NULL || idx >= vec->size ) { return NULL; }

  return vec->arr[ idx ];
}

byte*                find_vector( struct vector* vec, byte* value, size_t size ) {
  if ( value == NULL ) { return NULL; }

# if __POINTER_SIZE__ == 2
    if ( size == sizeof( i16 ) ) {
      i16 cpy = *( (i16*)value );
      size_t sz = ( vec->size >> 1 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i16*)vec->arr )[ i     ] ) { return &( ( (i16*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 1 ] ) { return &( ( (i16*)vec->arr )[ i + 1 ] ); }
      }
    } else if ( size == sizeof( i32 ) ) {
      i32 cpy = *( (i32*)value );
      size_t sz = ( vec->size >> 2 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i32*)vec->arr )[ i     ] ) { return &( ( (i32*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 1 ] ) { return &( ( (i32*)vec->arr )[ i + 1 ] ); }
      }
    } else if ( size == sizeof( i64 ) ) {
      i64 cpy = *( (i64*)value );
      size_t sz = ( vec->size >> 3 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i64*)vec->arr )[ i     ] ) { return &( ( (i64*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 1 ] ) { return &( ( (i64*)vec->arr )[ i + 1 ] ); }
      }
    } else {
      i8  cpy = *( (i8*)value );
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < vec->size ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == vec->arr[ i     ] ) { return &( vec->arr[ i     ] ); }
        else if ( cpy == vec->arr[ i + 1 ] ) { return &( vec->arr[ i + 1 ] ); }
      }
    }
# elif __POINTER_SIZE__ == 4
    if ( size == sizeof( i16 ) ) {
      i16 cpy = *( (i16*)value );
      size_t sz = ( vec->size >> 1 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i16*)vec->arr )[ i     ] ) { return &( ( (i16*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 1 ] ) { return &( ( (i16*)vec->arr )[ i + 1 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 2 ] ) { return &( ( (i16*)vec->arr )[ i + 2 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 3 ] ) { return &( ( (i16*)vec->arr )[ i + 3 ] ); }
      }
    } else if ( size == sizeof( i32 ) ) {
      i32 cpy = *( (i32*)value );
      size_t sz = ( vec->size >> 2 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i32*)vec->arr )[ i     ] ) { return &( ( (i32*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 1 ] ) { return &( ( (i32*)vec->arr )[ i + 1 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 2 ] ) { return &( ( (i32*)vec->arr )[ i + 2 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 3 ] ) { return &( ( (i32*)vec->arr )[ i + 3 ] ); }
      }
    } else if ( size == sizeof( i64 ) ) {
      i64 cpy = *( (i64*)value );
      size_t sz = ( vec->size >> 3 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i64*)vec->arr )[ i     ] ) { return &( ( (i64*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 1 ] ) { return &( ( (i64*)vec->arr )[ i + 1 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 2 ] ) { return &( ( (i64*)vec->arr )[ i + 2 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 3 ] ) { return &( ( (i64*)vec->arr )[ i + 3 ] ); }
      }
    } else {
      i8  cpy = *( (i8*)value );
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < vec->size ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == vec->arr[ i     ] ) { return &( vec->arr[ i     ] ); }
        else if ( cpy == vec->arr[ i + 1 ] ) { return &( vec->arr[ i + 1 ] ); }
        else if ( cpy == vec->arr[ i + 2 ] ) { return &( vec->arr[ i + 2 ] ); }
        else if ( cpy == vec->arr[ i + 3 ] ) { return &( vec->arr[ i + 3 ] ); }
      }
    }
# elif __POINTER_SIZE__ == 8
    if ( size == sizeof( i16 ) ) {
      i16 cpy = *( (i16*)value );
      size_t sz = ( vec->size >> 1 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i16*)vec->arr )[ i     ] ) { return &( ( (i16*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 1 ] ) { return &( ( (i16*)vec->arr )[ i + 1 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 2 ] ) { return &( ( (i16*)vec->arr )[ i + 2 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 3 ] ) { return &( ( (i16*)vec->arr )[ i + 3 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 4 ] ) { return &( ( (i16*)vec->arr )[ i + 4 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 5 ] ) { return &( ( (i16*)vec->arr )[ i + 5 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 6 ] ) { return &( ( (i16*)vec->arr )[ i + 6 ] ); }
        else if ( cpy == ( (i16*)vec->arr )[ i + 7 ] ) { return &( ( (i16*)vec->arr )[ i + 7 ] ); }
      }
    } else if ( size == sizeof( i32 ) ) {
      i32 cpy = *( (i32*)value );
      size_t sz = ( vec->size >> 2 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i32*)vec->arr )[ i     ] ) { return &( ( (i32*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 1 ] ) { return &( ( (i32*)vec->arr )[ i + 1 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 2 ] ) { return &( ( (i32*)vec->arr )[ i + 2 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 3 ] ) { return &( ( (i32*)vec->arr )[ i + 3 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 4 ] ) { return &( ( (i32*)vec->arr )[ i + 4 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 5 ] ) { return &( ( (i32*)vec->arr )[ i + 5 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 6 ] ) { return &( ( (i32*)vec->arr )[ i + 6 ] ); }
        else if ( cpy == ( (i32*)vec->arr )[ i + 7 ] ) { return &( ( (i32*)vec->arr )[ i + 7 ] ); }
      }
    } else if ( size == sizeof( i64 ) ) {
      i64 cpy = *( (i64*)value );
      size_t sz = ( vec->size >> 3 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i64*)vec->arr )[ i     ] ) { return &( ( (i64*)vec->arr )[ i     ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 1 ] ) { return &( ( (i64*)vec->arr )[ i + 1 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 2 ] ) { return &( ( (i64*)vec->arr )[ i + 2 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 3 ] ) { return &( ( (i64*)vec->arr )[ i + 3 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 4 ] ) { return &( ( (i64*)vec->arr )[ i + 4 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 5 ] ) { return &( ( (i64*)vec->arr )[ i + 5 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 6 ] ) { return &( ( (i64*)vec->arr )[ i + 6 ] ); }
        else if ( cpy == ( (i64*)vec->arr )[ i + 7 ] ) { return &( ( (i64*)vec->arr )[ i + 7 ] ); }
      }
    } else {
      i8  cpy = *( (i8*)value );
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < vec->size ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == vec->arr[ i     ] ) { return &( vec->arr[ i     ] ); }
        else if ( cpy == vec->arr[ i + 1 ] ) { return &( vec->arr[ i + 1 ] ); }
        else if ( cpy == vec->arr[ i + 2 ] ) { return &( vec->arr[ i + 2 ] ); }
        else if ( cpy == vec->arr[ i + 3 ] ) { return &( vec->arr[ i + 3 ] ); }
        else if ( cpy == vec->arr[ i + 4 ] ) { return &( vec->arr[ i + 4 ] ); }
        else if ( cpy == vec->arr[ i + 5 ] ) { return &( vec->arr[ i + 5 ] ); }
        else if ( cpy == vec->arr[ i + 6 ] ) { return &( vec->arr[ i + 6 ] ); }
        else if ( cpy == vec->arr[ i + 7 ] ) { return &( vec->arr[ i + 7 ] ); }
      }
    }
# else
    if ( size == sizeof( i16 ) ) {
      i16 cpy = *( (i16*)value );
      size_t sz = ( vec->size >> 1 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i16*)vec->arr )[ i     ] ) { return &( ( (i16*)vec->arr )[ i     ] ); }
      }
    } else if ( size == sizeof( i32 ) ) {
      i32 cpy = *( (i32*)value );
      size_t sz = ( vec->size >> 2 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i32*)vec->arr )[ i     ] ) { return &( ( (i32*)vec->arr )[ i     ] ); }
      }
    } else if ( size == sizeof( i64 ) ) {
      i64 cpy = *( (i64*)value );
      size_t sz = ( vec->size >> 3 );
      sz = ( sz == 0 ) ? vec->size : sz;
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < sz ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == ( (i64*)vec->arr )[ i     ] ) { return &( ( (i64*)vec->arr )[ i     ] ); }
      }
    } else {
      i8  cpy = *( (i8*)value );
      for ( ; ( ( i + ( __UNROLL_STEPS__ ) ) < vec->size ); i += __UNROLL_STEPS__ ) {
        if      ( cpy == vec->arr[ i     ] ) { return &( vec->arr[ i     ] ); }
      }
    }
# endif

  i8 cpy2 = *( (i8*)value );
  for ( ; i < vec->size; i++ ) {
    if ( cpy2 == vec->arr[ i ] ) { return &( vec->arr[ i ] ); }
  }

  return NULL;
}

__forceinline byte* front_vector( struct vector* vec                           ) {
  if ( vec == NULL || vec->arr == NULL ) {
    return NULL;
  }

  return vec->arr[ 0 ];
}

__forceinline byte*  back_vector( struct vector* vec                           ) {
  if ( vec == NULL || vec->arr == NULL ) {
    return NULL;
  }

  return vec->arr[ vec->size - vec->lastsize ];
}