#ifndef __OSCA_LIBC_VECTOR_H__
#  include <stddef.h>

  struct vector {
    size_t bsize;
    size_t fsize;
    size_t  capy;
    size_t  size;
    char*    arr;
  } __packed;

  extern void       init_vector( struct vector* vec, size_t cap           );
  extern void  push_back_vector( struct vector* vec, void*  val, size_t n );
  extern void push_front_vector( struct vector* vec, void*  val, size_t n );
  extern void*  pop_back_vector( struct vector* vec                       );
  extern void* pop_front_vector( struct vector* vec                       );
  extern void*      find_vector( struct vector* vec, void  *val, size_t s );
  extern void    destroy_vector( struct vector* vec                       );

#  if !defined(initv) && !defined(pushbv) && !defined(pushfv) \
   && !defined(popbv) && !defined(popfv) \
   && !defined(atv) && !defined(findv) && !defined(destroyv)
#    define    initv(a0, a1) init_vector(&a0, a1)
#    define   pushbv(a0, a1) push_back_vector(&a0, (void*)&a1, sizeof(a1))
#    define   pushfv(a0, a1) push_front_vector(&a0, (void*)&a1, sizeof(a1))
#    define    popbv(a0, a1) *(a1*)(pop_back_vector(&a0))
#    define    popfv(a0, a1) *(a1*)(pop_front_vector(&a0))
#    define  atv(a0, a1, a2)  ((a1*)(a0.arr))[a2]
#    define findv(a0, a1, a2) *(a1*)(find_vector(&a0, (void *)(&a2), sizeof(a1)))
#    define destroyv(a0)     destroy_vector(&a0)
#  endif

#  define __OSCA_LIBC_VECTOR_H__                1
#endif