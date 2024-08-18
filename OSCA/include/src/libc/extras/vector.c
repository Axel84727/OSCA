#include <extras/vector.h>
#include <stdlib.h>
#include <string.h>

void init_vector(struct vector *vec, size_t cap) {
  if (!cap || !vec) { return; }

  vec->arr = (char *)(malloc(cap));
  if (!vec->arr) { return; }
  vec->capy = cap;
}

void push_back_vector(struct vector *vec, void *val, size_t n) {
  if ( !vec || !vec->arr || !vec->capy || !val || !n ) { return; }

  if ( vec->size == vec->capy || (vec->size + n) >= vec->capy ) {
    void* arr = (void*)(realloc(vec->arr, vec->capy << 1));
    if (!arr) { return; }
    vec->capy <<= 1;
    memcpy(arr, vec->arr, vec->size);
    free(vec->arr);
    vec->arr = (char *)(arr);
    memcpy(vec->arr + vec->size, val, n);
    vec->size += n;
    vec->bsize = n;
    return;
  }

  memcpy(vec->arr + vec->size, val, n);
  if ( !vec->size ) { vec->fsize = n; }
  vec->size += n;
  vec->bsize = n;
}

void push_front_vector(struct vector *vec, void *val, size_t n) {
  if (!vec || !vec->arr || !vec->capy || !val || !n) { return; }

  if ( vec->size == vec->capy || (vec->size + n) >= vec->capy ) {
    void *arr = (void*)(realloc(vec->arr, vec->capy << 1));
    if (!arr) { return; }
    vec->capy <<= 1;
    memcpy(arr, val, n), memcpy(arr + n, vec->arr, vec->size);
    free(vec->arr);
    vec->arr = (char *)(arr);
    vec->size += n;
    vec->fsize = n;
    return;
  }

  void *arr = (void*)(malloc(vec->capy));
  if (!arr) { return; }
  memcpy(arr, val, n), memcpy(arr + n, vec->arr, vec->size != 0 ? vec->size : vec->capy);
  free(vec->arr);
  vec->arr = (char *)(arr);
  if (!vec->size) { vec->bsize = n; }
  vec->size += n;
  vec->fsize = n;
}

void *pop_back_vector(struct vector *vec) {
  if (!vec || !vec->arr || !vec->capy || !vec->size || !vec->bsize) { return NULL; }

  void *output = malloc(vec->bsize), *arr = malloc(vec->capy);
  if (!output || !arr) { output != NULL ? free(output) : (arr != NULL ? free(arr) : (void)0); return NULL; }
  memcpy(output, vec->arr + (vec->size - vec->bsize), vec->bsize);
  memcpy(arr, vec->arr, vec->size -= vec->bsize);
  free(vec->arr);
  vec->arr   = arr;
  vec->bsize =   0;

  return output;
}

void *pop_front_vector(struct vector *vec) {
  if (!vec || !vec->arr || !vec->capy || !vec->size || !vec->fsize) { return NULL; }

  void *output = malloc(vec->fsize), *arr = malloc(vec->capy);
  if (!output || !arr) { output != NULL ? free(output) : (arr != NULL ? free(arr) : (void)0); return NULL; }
  memcpy(output, vec->arr, vec->fsize );
  memcpy(arr, vec->arr + vec->fsize, vec->size -= vec->fsize);
  free(vec->arr);
  vec->arr = (char *)(arr);
  vec->fsize = 0;

  return output;
}

void      *find_vector(struct vector *vec, void* val, size_t s ) {
  if (!vec || !vec->arr || !vec->size || !vec->capy || !val || !s) {
    return NULL;
  }

   size_t n = 0;
#  if    __POINTER_SIZE__ == 2
     for ( ; (n + __POINTER_SIZE__) < vec->size; n += __POINTER_SIZE__ ) {
       if      ( !memcmp( (void *)&vec->arr[n    ], val, s ) ) { return ((char*)&vec->arr[n    ]); }
       else if ( !memcmp( (void *)&vec->arr[n + 1], val, s ) ) { return ((char*)&vec->arr[n + 1]); }
     }
#  elif  __POINTER_SIZE__ == 4
     for ( ; (n + __POINTER_SIZE__) < vec->size; n += __POINTER_SIZE__ ) {
       if      ( !memcmp( (void *)&vec->arr[n    ], val, s ) ) { return ((char*)&vec->arr[n    ]); }
       else if ( !memcmp( (void *)&vec->arr[n + 1], val, s ) ) { return ((char*)&vec->arr[n + 1]); }
       else if ( !memcmp( (void *)&vec->arr[n + 2], val, s ) ) { return ((char*)&vec->arr[n + 2]); }
       else if ( !memcmp( (void *)&vec->arr[n + 3], val, s ) ) { return ((char*)&vec->arr[n + 3]); }
     }
#  elif  __POINTER_SIZE__ == 8
     for ( ; (n + __POINTER_SIZE__) < vec->size; n += __POINTER_SIZE__ ) {
       if      ( !memcmp( (void *)&vec->arr[n    ], val, s ) ) { return ((char*)&vec->arr[n    ]); }
       else if ( !memcmp( (void *)&vec->arr[n + 1], val, s ) ) { return ((char*)&vec->arr[n + 1]); }
       else if ( !memcmp( (void *)&vec->arr[n + 2], val, s ) ) { return ((char*)&vec->arr[n + 2]); }
       else if ( !memcmp( (void *)&vec->arr[n + 3], val, s ) ) { return ((char*)&vec->arr[n + 3]); }
       else if ( !memcmp( (void *)&vec->arr[n + 4], val, s ) ) { return ((char*)&vec->arr[n + 4]); }
       else if ( !memcmp( (void *)&vec->arr[n + 5], val, s ) ) { return ((char*)&vec->arr[n + 5]); }
       else if ( !memcmp( (void *)&vec->arr[n + 6], val, s ) ) { return ((char*)&vec->arr[n + 6]); }
       else if ( !memcmp( (void *)&vec->arr[n + 7], val, s ) ) { return ((char*)&vec->arr[n + 7]); }
     }
#  endif
   for ( ; n < vec->size; n++ ) {
     if ( !memcmp( (void *)&vec->arr[n], val, s ) ) { return ((char*)&vec->arr[n]); }
   }

   return (void *)(NULL);
}

void    destroy_vector(struct vector *vec) {
  if (!vec && !vec->arr && !vec->size && !vec->capy) { return; }

  free(vec->arr);
  vec->arr = NULL;
  vec->bsize =  0;
  vec->fsize =  0;
  vec->capy  =  0;
  vec->size  =  0;
}