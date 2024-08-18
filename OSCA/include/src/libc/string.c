#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

size_t strlen(const char *a0) {
   if (!a0 || !(*a0)) {
     return 0;
   }

   size_t n = 0;
#  if    __POINTER_SIZE__ == 2
     u16* p0 = (u16*)(a0);
     for ( ; (p0[n] & 0xFF) && ((p0[n] >> 8) & 0xFF); n++ ) {
       if ( ( p0[n + 1] & 0xFF) && ((p0[n + 1] >> 8) & 0xFF ) ) { n++; }
     }

     for ( ; a0[n]; n++ ) {
       if ( a0[n + 1] ) { n++; }
     }
#  elif  __POINTER_SIZE__ == 4
     u32* p0 = (u32*)(a0);
     for ( ; (p0[n] & 0xFF) && ((p0[n] >> 8) & 0xFF) \
      &&     ((p0[n] >> 16) & 0xFF) && ((p0[n] >> 24) & 0xFF); n++ ) {
       if ( ( p0[n + 1] & 0xFF ) && (( p0[n + 1] >> 8 ) & 0xFF) \
       && ( ( p0[n + 1] >> 16 ) & 0xFF ) && ( ( p0[n + 1] >> 24 ) & 0xFF ) ) { n++; }
       if ( ( p0[n + 2] & 0xFF ) && (( p0[n + 2] >> 8 ) & 0xFF) \
       && ( ( p0[n + 2] >> 16 ) & 0xFF ) && ( ( p0[n + 2] >> 24 ) & 0xFF ) ) { n++; }
       if ( ( p0[n + 3] & 0xFF ) && (( p0[n + 3] >> 8 ) & 0xFF) \
       && ( ( p0[n + 3] >> 16 ) & 0xFF ) && ( ( p0[n + 3] >> 24 ) & 0xFF ) ) { n++; }
     }

     for ( ; a0[n]; n++ ) {
       if ( a0[n + 1] ) { n++; }
       if ( a0[n + 2] ) { n++; }
       if ( a0[n + 3] ) { n++; }
     }
#  elif  __POINTER_SIZE__ == 8
     u64* p0 = (u64*)(a0);
     for ( ; (p0[n] & 0xFF) && ((p0[n] >> 8) & 0xFF) \
      &&     ((p0[n] >> 16) & 0xFF) && ((p0[n] >> 24) & 0xFF) \
      &&     ((p0[n] >> 32) & 0xFF) && ((p0[n] >> 40) & 0xFF) \
      &&     ((p0[n] >> 48) & 0xFF) && ((p0[n] >> 56) & 0xFF); n++ ) {
       if ( ( p0[n + 1] & 0xFF ) && (( p0[n + 1] >> 8 ) & 0xFF) \
       && ( ( p0[n + 1] >> 16 ) & 0xFF ) && ( ( p0[n + 1] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 1] >> 32 ) & 0xFF ) && ( ( p0[n + 1] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 1] >> 48 ) & 0xFF ) && ( ( p0[n + 1] >> 56 ) & 0xFF ) ) { n++; }

       if ( ( p0[n + 2] & 0xFF ) && (( p0[n + 2] >> 8 ) & 0xFF) \
       && ( ( p0[n + 2] >> 16 ) & 0xFF ) && ( ( p0[n + 2] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 2] >> 32 ) & 0xFF ) && ( ( p0[n + 2] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 2] >> 48 ) & 0xFF ) && ( ( p0[n + 2] >> 56 ) & 0xFF ) ) { n++; }

       if ( ( p0[n + 3] & 0xFF ) && (( p0[n + 3] >> 8 ) & 0xFF) \
       && ( ( p0[n + 3] >> 16 ) & 0xFF ) && ( ( p0[n + 3] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 3] >> 32 ) & 0xFF ) && ( ( p0[n + 3] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 3] >> 48 ) & 0xFF ) && ( ( p0[n + 3] >> 56 ) & 0xFF ) ) { n++; }

       if ( ( p0[n + 4] & 0xFF ) && (( p0[n + 4] >> 8 ) & 0xFF) \
       && ( ( p0[n + 4] >> 16 ) & 0xFF ) && ( ( p0[n + 4] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 4] >> 32 ) & 0xFF ) && ( ( p0[n + 4] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 4] >> 48 ) & 0xFF ) && ( ( p0[n + 4] >> 56 ) & 0xFF ) ) { n++; }

       if ( ( p0[n + 5] & 0xFF ) && (( p0[n + 5] >> 8 ) & 0xFF) \
       && ( ( p0[n + 5] >> 16 ) & 0xFF ) && ( ( p0[n + 5] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 5] >> 32 ) & 0xFF ) && ( ( p0[n + 5] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 5] >> 48 ) & 0xFF ) && ( ( p0[n + 5] >> 56 ) & 0xFF ) ) { n++; }

       if ( ( p0[n + 6] & 0xFF ) && (( p0[n + 6] >> 8 ) & 0xFF) \
       && ( ( p0[n + 6] >> 16 ) & 0xFF ) && ( ( p0[n + 6] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 6] >> 32 ) & 0xFF ) && ( ( p0[n + 6] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 6] >> 48 ) & 0xFF ) && ( ( p0[n + 6] >> 56 ) & 0xFF ) ) { n++; }

       if ( ( p0[n + 7] & 0xFF ) && (( p0[n + 7] >> 8 ) & 0xFF) \
       && ( ( p0[n + 7] >> 16 ) & 0xFF ) && ( ( p0[n + 7] >> 24 ) & 0xFF ) \
       && ( ( p0[n + 7] >> 32 ) & 0xFF ) && ( ( p0[n + 7] >> 40 ) & 0xFF ) \
       && ( ( p0[n + 7] >> 48 ) & 0xFF ) && ( ( p0[n + 7] >> 56 ) & 0xFF ) ) { n++; }
     }

   for ( ; a0[n]; n++ ) {
     if ( a0[n + 1] ) { n++; }
     if ( a0[n + 2] ) { n++; }
     if ( a0[n + 3] ) { n++; }
     if ( a0[n + 4] ) { n++; }
     if ( a0[n + 5] ) { n++; }
     if ( a0[n + 6] ) { n++; }
     if ( a0[n + 7] ) { n++; }
   }
#  endif
   for ( ; a0[n]; n++ );

   return n;
}

size_t wcslen(const char *a0) {
   if (!a0 || *a0 == L'\0') {
     return 0;
   }

   size_t n = 0;
#  if    __POINTER_SIZE__ == 2
     u16* p0 = (u16*)(a0);
     for ( ; (p0[n] & 0xFF) && ((p0[n] >> 8) & 0xFF); n++ ) {
       if ( ( (p0[n + 1] & 0xFF) != L'\0') && (((p0[n + 1] >> 8) & 0xFF) != L'\0' ) )   { n++; }
     }

     for ( ; a0[n]; n++ ) {
       if ( a0[n + 1] ) { n++; }
     }
#  elif  __POINTER_SIZE__ == 4
     u32* p0 = (u32*)(a0);
     for ( ; ((p0[n] & 0xFF) != L'\0') && (((p0[n] >> 8) & 0xFF) != L'\0') \
      &&     (((p0[n] >> 16) & 0xFF) != L'\0') && (((p0[n] >> 24) & 0xFF) != L'\0'); n++ ) {
       if ( ( (p0[n + 1] & 0xFF) != L'\0' ) && ((( p0[n + 1] >> 8 ) & 0xFF) != L'\0') \
       && ( ( ( p0[n + 1] >> 16 ) & 0xFF ) != L'\0' ) && ( ( ( p0[n + 1] >> 24 ) & 0xFF ) != L'\0' ) ) { n++; }
       if ( ( (p0[n + 2] & 0xFF) != L'\0' ) && ((( p0[n + 2] >> 8 ) & 0xFF) != L'\0') \
       && ( ( ( p0[n + 2] >> 16 ) & 0xFF ) != L'\0' ) && ( ( ( p0[n + 2] >> 24 ) & 0xFF ) != L'\0' ) ) { n++; }
       if ( ( (p0[n + 3] & 0xFF) != L'\0' ) && ((( p0[n + 3] >> 8 ) & 0xFF) != L'\0') \
       && ( ( ( p0[n + 3] >> 16 ) & 0xFF ) != L'\0' ) && ( ( ( p0[n + 3] >> 24 ) & 0xFF ) != L'\0' ) ) { n++; }
     }

     for ( ; a0[n]; n++ ) {
       if ( a0[n + 1] ) { n++; }
       if ( a0[n + 2] ) { n++; }
       if ( a0[n + 3] ) { n++; }
     }
#  elif  __POINTER_SIZE__ == 8
     u64* p0 = (u64*)(a0);
     for ( ; (p0[n] & 0xFF) && ((p0[n] >> 8) & 0xFF) \
      &&     ((p0[n] >> 16) & 0xFF) && ((p0[n] >> 24) & 0xFF) \
      &&     ((p0[n] >> 32) & 0xFF) && ((p0[n] >> 40) & 0xFF) \
      &&     ((p0[n] >> 48) & 0xFF) && ((p0[n] >> 56) & 0xFF); n++ ) {
      if  ( ( ( p0[n + 1] & 0xFF) != L'\0' ) && ((( p0[n + 1] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 1] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 1] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 1] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 1] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 1] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 1] >> 56 ) & 0xFF) != L'\0' ) )   { n++; }

      if  ( ( ( p0[n + 2] & 0xFF) != L'\0' ) && ((( p0[n + 2] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 2] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 2] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 2] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 2] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 2] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 2] >> 56 ) & 0xFF) != L'\0' ) )   { n++; }

      if  ( ( ( p0[n + 3] & 0xFF) != L'\0' ) && ((( p0[n + 3] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 3] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 3] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 3] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 3] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 3] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 3] >> 56 ) & 0xFF) != L'\0' ) )  { n++; }

      if  ( ( ( p0[n + 4] & 0xFF) != L'\0' ) && ((( p0[n + 4] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 4] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 4] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 4] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 4] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 4] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 4] >> 56 ) & 0xFF) != L'\0' ) ) { n++; }

      if  ( ( ( p0[n + 5] & 0xFF) != L'\0' ) && ((( p0[n + 5] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 5] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 5] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 5] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 5] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 5] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 5] >> 56 ) & 0xFF) != L'\0' ) ) { n++; }

      if  ( ( ( p0[n + 6] & 0xFF) != L'\0' ) && ((( p0[n + 6] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 6] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 6] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 6] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 6] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 6] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 6] >> 56 ) & 0xFF) != L'\0' ) ) { n++; }

      if  ( ( ( p0[n + 7] & 0xFF) != L'\0' ) && ((( p0[n + 7] >> 8 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 7] >> 16 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 7] >> 24 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 7] >> 32 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 7] >> 40 ) & 0xFF) != L'\0' ) \
       && ( ( (p0[n + 7] >> 48 ) & 0xFF) != L'\0' ) && ( ( (p0[n + 7] >> 56 ) & 0xFF) != L'\0' ) ) { n++; }
     }

   for ( ; a0[n] != L'\0'; n++ ) {
     if ( a0[n + 1] != L'\0' ) { n++; }
     if ( a0[n + 2] != L'\0' ) { n++; }
     if ( a0[n + 3] != L'\0' ) { n++; }
     if ( a0[n + 4] != L'\0' ) { n++; }
     if ( a0[n + 5] != L'\0' ) { n++; }
     if ( a0[n + 6] != L'\0' ) { n++; }
     if ( a0[n + 7] != L'\0' ) { n++; }
   }
#  endif
   for ( ; a0[n] != L'\0'; n++ );
}

void *memcpy(void *a0, const void *a1, size_t a2)
{
   if (!a0 || !a1 || !a2) { return NULL; }

   size_t n = 0;
   size_t sz;

#  if    __POINTER_SIZE__ == 2
     sz = (n >> 1);

     switch (sz) {
       default: {
         u16* p0 = (u16*)(a0);
         const u16* p1 = (const u16*)(a1);
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           p0[n    ] = p1[n    ];
           p0[n + 1] = p1[n + 1];
         }

         for ( ; n < sz; n++ ) {
           p0[n] = p1[n];
         }

         break;
       }

       case 0:
       case 1: { break; }
     }
#  elif  __POINTER_SIZE__ == 4
     sz = (n >> 2);

     switch (sz) {
       default: {
         u32* p0 = (u32*)(a0);
         const u32* p1 = (const u32*)(a1);
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           p0[n    ] = p1[n    ];
           p0[n + 1] = p1[n + 1];
           p0[n + 2] = p1[n + 2];
           p0[n + 3] = p1[n + 3];
         }

         for ( ; n < sz; n++ ) {
           p0[n] = p1[n];
         }

         break;
       }

       case (__POINTER_SIZE__ >> 1): {
         u16* p0 = (u16*)(a0);
         const u16* p1 = (const u16*)(a1);
         for ( ; (n + (__POINTER_SIZE__ >> 1)) < sz; n += (__POINTER_SIZE__ >> 1) ) {
           p0[n    ] = p1[n    ];
           p0[n + 1] = p1[n + 1];
         }

         for ( ; n < sz; n++ ) {
           p0[n] = p1[n];
         }

         break;
       }

       case 0:
       case 1: { break; }
     }
#  elif  __POINTER_SIZE__ == 8
     sz = (n >> 3);
     switch (sz) {
       default: {
         u64* p0 = (u64*)(a0);
         const u64* p1 = (const u64*)(a1);
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           p0[n    ] = p1[n    ];
           p0[n + 1] = p1[n + 1];
           p0[n + 2] = p1[n + 2];
           p0[n + 3] = p1[n + 3];
           p0[n + 4] = p1[n + 4];
           p0[n + 5] = p1[n + 5];
           p0[n + 6] = p1[n + 6];
           p0[n + 7] = p1[n + 7];
         }

         for ( ; n < sz; n++ ) {
           p0[n] = p1[n];
         }

         break;
       }

       case (__POINTER_SIZE__ >> 1): {
         u32* p0 = (u32*)(a0);
         const u32* p1 = (const u32*)(a1);
         for ( ; (n + (__POINTER_SIZE__ >> 1)) < sz; n += (__POINTER_SIZE__ >> 1) ) {
           p0[n    ] = p1[n    ];
           p0[n + 1] = p1[n + 1];
           p0[n + 2] = p1[n + 2];
           p0[n + 3] = p1[n + 3];
         }

         for ( ; n < sz; n++ ) {
           p0[n] = p1[n];
         }

         break;
       }

       case (__POINTER_SIZE__ >> 2): {
         u16* p0 = (u16*)(a0);
         const u16* p1 = (const u16*)(a1);
         for ( ; (n + (__POINTER_SIZE__ >> 2)) < sz; n += (__POINTER_SIZE__ >> 2) ) {
           p0[n    ] = p1[n    ];
           p0[n + 1] = p1[n + 1];
         }

         for ( ; n < sz; n++ ) {
           p0[n] = p1[n];
         }

         break;
       }

       case 0:
       case 1: { break; }
     }
#  endif

   u8* p2 = (u8*)(a0);
   const u8* p3 = (const u8*)(a1);
#  if    __POINTER_SIZE__ == 2
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       p2[n    ] = p3[n    ];
       p2[n + 1] = p3[n + 1];
     }
#  elif  __POINTER_SIZE__ == 4
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       p2[n    ] = p3[n    ];
       p2[n + 1] = p3[n + 1];
       p2[n + 2] = p3[n + 2];
       p2[n + 3] = p3[n + 3];
     }
#  elif  __POINTER_SIZE__ == 8
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       p2[n    ] = p3[n    ];
       p2[n + 1] = p3[n + 1];
       p2[n + 2] = p3[n + 2];
       p2[n + 3] = p3[n + 3];
       p2[n + 4] = p3[n + 4];
       p2[n + 5] = p3[n + 5];
       p2[n + 6] = p3[n + 6];
       p2[n + 7] = p3[n + 7];
     }
#  endif
   for ( ; n < a2; n++ ) {
     p2[n] = p3[n];
   }

   return a0;
}

void *memset(void *a0, int a1, size_t a2) {
   if (!a0 || !a2) { return NULL; }

   size_t n  = 0;
   size_t sz;

#  if    __POINTER_SIZE__ == 2
     sz = (a2 >> 1);
     switch ( sz ) {
       default: {
         u16* p0 = (u16*)(a0);
         u16 value = a1 | (a1 << 8);

         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           p0[n    ] = value;
           p0[n + 1] = value;
         }

         for ( ; n < sz; n++ ) {
           p0[n] = value;
         }
       }

       case 1: { break; }
     }
#  elif  __POINTER_SIZE__ == 4
     sz = (a2 >> 2);
     switch ( sz ) {
       default: {
         u32* p0 = (u32*)(a0);
         u32 value = a1 | (a1 << 8) | (a1 << 16) | (a1 << 24);
       
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           p0[n    ] = value;
           p0[n + 1] = value;
           p0[n + 2] = value;
           p0[n + 3] = value;
         }

         for ( ; n < sz; n++ ) {
           p0[n] = value;
         }

         break;
       } 
     
       case (__POINTER_SIZE__ >> 1): {
         u16* p0 = (u16*)(a0);
         u16 value = a1 | (a1 << 8);
 
         for ( ; (n + (__POINTER_SIZE__ >> 1)) < sz; n += (__POINTER_SIZE__ >> 1) ) {
           p0[n    ] = value;
           p0[n + 1] = value;
         }

          for ( ; n < sz; n++ ) {
            p0[n] = value;
          }
          break;
        }
       
        case 1: { break; }
      }
#  elif  __POINTER_SIZE__ == 8
     sz = (a2 >> 3);
     switch ( sz ) {
       default: {
         u64* p0 = (u64*)(a0);
         u64 value = a1 | (a1 << 8) | (a1 << 16) | (a1 << 24) | \
               (a1 << 32) | (a1 << 40) | (a1 << 48) | (a1 << 56);

         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           p0[n    ] = value;
           p0[n + 1] = value;
           p0[n + 2] = value;
           p0[n + 3] = value;
           p0[n + 4] = value;
           p0[n + 5] = value;
           p0[n + 6] = value;
           p0[n + 7] = value;
         }

         for ( ; n < sz; n++ ) {
           p0[n] = value;
         }

         break;
       }

       case (__POINTER_SIZE__ >> 1): {
         u32* p0 = (u32*)(a0);
         u32 value = a1 | (a1 << 8) | (a1 << 16) | (a1 << 24);
       
         for ( ; (n + (__POINTER_SIZE__ >> 1)) < sz; n += (__POINTER_SIZE__ >> 1) ) {
           p0[n    ] = value;
           p0[n + 1] = value;
           p0[n + 2] = value;
           p0[n + 3] = value;
         }

         for ( ; n < sz; n++ ) {
           p0[n] = value;
         }

         break;
       } 
     
       case (__POINTER_SIZE__ >> 2): {
         u16* p0 = (u16*)(a0);
         u16 value = a1 | (a1 << 8);
 
         for ( ; (n + (__POINTER_SIZE__ >> 2)) < sz; n += (__POINTER_SIZE__ >> 2) ) {
           p0[n    ] = value;
           p0[n + 1] = value;
         }

          for ( ; n < sz; n++ ) {
            p0[n] = value;
          }
          break;
        }
       
        case 1: { break; }
      }
#  endif

   u8* p1 = (u8*)(a0);
#  if    __POINTER_SIZE__ == 2
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       p1[n    ] = (u8)(a1);
       p1[n + 1] = (u8)(a1);
     }
#  elif  __POINTER_SIZE__ == 4
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       p1[n    ] = (u8)(a1);
       p1[n + 1] = (u8)(a1);
       p1[n + 2] = (u8)(a1);
       p1[n + 3] = (u8)(a1);
     }
#  elif  __POINTER_SIZE__ == 8
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       p1[n    ] = (u8)(a1);
       p1[n + 1] = (u8)(a1);
       p1[n + 2] = (u8)(a1);
       p1[n + 3] = (u8)(a1);
       p1[n + 4] = (u8)(a1);
       p1[n + 5] = (u8)(a1);
       p1[n + 6] = (u8)(a1);
       p1[n + 7] = (u8)(a1);
     }
#  endif
   for ( ; n < a2; n++ ) {
     p1[n] = (u8)(a1);
   }

   return a0;
}

int   memcmp(const void *a0, const void *a1, size_t a2) {
   if (!a0 && !a1) { return 0; }

   if (!a0) { return -1; } else if ( !a1 ) { return 1; }

   size_t  n = 0;
   size_t sz;
#  if    __POINTER_SIZE__ == 2
     sz = (n >> 1);
     switch (sz) {
       default: {
         const u16* p0 = (const u16*)(a0);
         const u16* p1 = (const u16*)(a1);
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           if ( p0[n    ] != p1[n    ] ) { return (char)((p0[n    ] - p1[n    ]) & 0xFF); }
           if ( p0[n + 1] != p1[n + 1] ) { return (char)((p0[n + 1] - p1[n + 1]) & 0xFF); }
         }

         for ( ; n < sz; n++ ) {
           if ( p0[n] != p1[n] ) { return (p0[n] - p1[n]) & 0xFF; }
         }

         break;
       }

       case 0:
       case 1: { break; }
     }
#  elif  __POINTER_SIZE__ == 4
     sz = (n >> 2);
     switch (sz) {
       default: {
         const u32* p0 = (const u32*)(a0);
         const u32* p1 = (const u32*)(a1);
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           if ( p0[n    ] != p1[n    ] ) { return (char)(((p0[n    ] - p1[n    ])) & 0xFF); }
           if ( p0[n + 1] != p1[n + 1] ) { return (char)(((p0[n + 1] - p1[n + 1])) & 0xFF); }
           if ( p0[n + 2] != p1[n + 2] ) { return (char)(((p0[n + 2] - p1[n + 2])) & 0xFF); }
           if ( p0[n + 3] != p1[n + 3] ) { return (char)(((p0[n + 3] - p1[n + 3])) & 0xFF); }
         }

         for ( ; n < sz; n++ ) {
           if ( p0[n] != p1[n] ) { return (char)(((p0[n] - p1[n])) & 0xFF); }
         }

         break;
       }

       case (__POINTER_SIZE__ >> 1): {
         const u16* p0 = (const u16*)(a0);
         const u16* p1 = (const u16*)(a1);
         for ( ; (n + (__POINTER_SIZE__ >> 1)) < sz; n += (__POINTER_SIZE__ >> 1) ) {
           if ( p0[n    ] != p1[n    ] ) { return (char)((p0[n    ] - p1[n    ]) & 0xFF); }
           if ( p0[n + 1] != p1[n + 1] ) { return (char)((p0[n + 1] - p1[n + 1]) & 0xFF); }
         }

         for ( ; n < sz; n++ ) {
           if ( p0[n] != p1[n] ) { return (char)((p0[n] - p1[n]) & 0xFF); }
         }

         break;
       }

       case 0:
       case 1: { break; }
     }
#  elif  __POINTER_SIZE__ == 8
     sz = (n >> 3);
     switch (sz) {
       default: {
         const u64* p0 = (const u64*)(a0);
         const u64* p1 = (const u64*)(a1);
         for ( ; (n + __POINTER_SIZE__) < sz; n += __POINTER_SIZE__ ) {
           if ( p0[n    ] != p1[n    ] ) { return (char)((((p0[n    ] - p1[n    ]))) & 0xFF); }
           if ( p0[n + 1] != p1[n + 1] ) { return (char)((((p0[n + 1] - p1[n + 1]))) & 0xFF); }
           if ( p0[n + 2] != p1[n + 2] ) { return (char)((((p0[n + 2] - p1[n + 2]))) & 0xFF); }
           if ( p0[n + 3] != p1[n + 3] ) { return (char)((((p0[n + 3] - p1[n + 3]))) & 0xFF); }
           if ( p0[n + 4] != p1[n + 4] ) { return (char)((((p0[n + 4] - p1[n + 4]))) & 0xFF); }
           if ( p0[n + 5] != p1[n + 5] ) { return (char)((((p0[n + 5] - p1[n + 5]))) & 0xFF); }
           if ( p0[n + 6] != p1[n + 6] ) { return (char)((((p0[n + 6] - p1[n + 6]))) & 0xFF); }
           if ( p0[n + 7] != p1[n + 7] ) { return (char)((((p0[n + 7] - p1[n + 7]))) & 0xFF); }
         }

         for ( ; n < sz; n++ ) {
           if ( p0[n] != p1[n] ) { return (char)((p0[n] - p1[n]) & 0xFF); }
         }

         break;
       }

       case (__POINTER_SIZE__ >> 1): {
         const u32* p0 = (const u32*)(a0);
         const u32* p1 = (const u32*)(a1);
         for ( ; (n + (__POINTER_SIZE__ >> 1)) < sz; n += (__POINTER_SIZE__ >> 1) ) {
           if ( p0[n    ] != p1[n    ] ) { return (char)(((p0[n    ] - p1[n    ])) & 0xFF); }
           if ( p0[n + 1] != p1[n + 1] ) { return (char)(((p0[n + 1] - p1[n + 1])) & 0xFF); }
           if ( p0[n + 2] != p1[n + 2] ) { return (char)(((p0[n + 2] - p1[n + 2])) & 0xFF); }
           if ( p0[n + 3] != p1[n + 3] ) { return (char)(((p0[n + 3] - p1[n + 3])) & 0xFF); }
         }

         for ( ; n < sz; n++ ) {
           if ( p0[n] != p1[n] ) { return (char)(((p0[n] - p1[n])) & 0xFF); }
         }

         break;
       }
       
       case (__POINTER_SIZE__ >> 2): {
         const u16* p0 = (const u16*)(a0);
         const u16* p1 = (const u16*)(a1);
         for ( ; (n + (__POINTER_SIZE__ >> 2)) < sz; n += (__POINTER_SIZE__ >> 2) ) {
           if ( p0[n    ] != p1[n    ] ) { return (char)((p0[n    ] - p1[n    ]) & 0xFF); }
           if ( p0[n + 1] != p1[n + 1] ) { return (char)((p0[n + 1] - p1[n + 1]) & 0xFF); }
         }

         for ( ; n < sz; n++ ) {
           if ( p0[n] != p1[n] ) { return (char)((p0[n] - p1[n]) & 0xFF); }
         }

         break;
       }

       case 0:
       case 1: { break; }
     }
#  endif

   const char* p2 = (const char*)(a0);
   const char* p3 = (const char*)(a1);
#  if    __POINTER_SIZE__ == 2
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       if ( p2[n    ] != p3[n    ] ) { return (char)(p2[n    ] - p3[n    ]); }
       if ( p2[n + 1] != p3[n + 1] ) { return (char)(p2[n + 1] - p3[n + 1]); }
     }
#  elif  __POINTER_SIZE__ == 4
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       if ( p2[n    ] != p3[n    ] ) { return (char)(p2[n    ] - p3[n    ]); }
       if ( p2[n + 1] != p3[n + 1] ) { return (char)(p2[n + 1] - p3[n + 1]); }
       if ( p2[n + 2] != p3[n + 2] ) { return (char)(p2[n + 2] - p3[n + 2]); }
       if ( p2[n + 3] != p3[n + 3] ) { return (char)(p2[n + 3] - p3[n + 3]); }
     }
#  elif  __POINTER_SIZE__ == 8
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       if ( p2[n    ] != p3[n    ] ) { return (char)(p2[n    ] - p3[n    ]); }
       if ( p2[n + 1] != p3[n + 1] ) { return (char)(p2[n + 1] - p3[n + 1]); }
       if ( p2[n + 2] != p3[n + 2] ) { return (char)(p2[n + 2] - p3[n + 2]); }
       if ( p2[n + 3] != p3[n + 3] ) { return (char)(p2[n + 3] - p3[n + 3]); }
       if ( p2[n + 4] != p3[n + 4] ) { return (char)(p2[n + 4] - p3[n + 4]); }
       if ( p2[n + 5] != p3[n + 5] ) { return (char)(p2[n + 5] - p3[n + 5]); }
       if ( p2[n + 6] != p3[n + 6] ) { return (char)(p2[n + 6] - p3[n + 6]); }
       if ( p2[n + 7] != p3[n + 7] ) { return (char)(p2[n + 7] - p3[n + 7]); }
     }
#  endif
   for ( ; n < a2; n++ ) {
     if ( p2[n] != p3[n] ) { return (char)(p2[n] - p3[n]); }
   }

   return 0;
}

int   strcmp(const char *a0, const char *a1) {
  if      ( !a0 && !a1 ) { return 0; }
  
  if ( !a0 ) { return -1; } else if ( !a1 ) { return 1; }
  size_t l0 = strlen(a0);
  size_t l1 = strlen(a1);

  if ( l0 > l1 ) {
    return a0[l1+1];
  } else if ( l0 < l1 ) {
    return -a1[l0+1];
  }

  return memcmp( a0, a1, l0 );
}

char *strchr(const char *a0, int a1) {
   if (!a0 || !(*a0)) { return NULL; } else if ( !a1 ) { return ((char*)&a0[strlen(a0)]); }

   size_t n = 0, a2 = strlen(a0);
#  if    __POINTER_SIZE__ == 2
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       if      ( a0[n    ] == a1) { return ((char*)&a0[n    ]); }
       else if ( a0[n + 1] == a1) { return ((char*)&a0[n + 1]); }
     }
#  elif  __POINTER_SIZE__ == 4
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       if      ( a0[n    ] == a1) { return ((char*)&a0[n    ]); }
       else if ( a0[n + 1] == a1) { return ((char*)&a0[n + 1]); }
       else if ( a0[n + 2] == a1) { return ((char*)&a0[n + 2]); }
       else if ( a0[n + 3] == a1) { return ((char*)&a0[n + 3]); }
     }
#  elif  __POINTER_SIZE__ == 8
     for ( ; (n + __POINTER_SIZE__) < a2; n += __POINTER_SIZE__ ) {
       if      ( a0[n    ] == a1) { return ((char*)&a0[n    ]); }
       else if ( a0[n + 1] == a1) { return ((char*)&a0[n + 1]); }
       else if ( a0[n + 2] == a1) { return ((char*)&a0[n + 2]); }
       else if ( a0[n + 3] == a1) { return ((char*)&a0[n + 3]); }
       else if ( a0[n + 4] == a1) { return ((char*)&a0[n + 4]); }
       else if ( a0[n + 5] == a1) { return ((char*)&a0[n + 5]); }
       else if ( a0[n + 6] == a1) { return ((char*)&a0[n + 6]); }
       else if ( a0[n + 7] == a1) { return ((char*)&a0[n + 7]); }
     }
#  endif
   for ( ; n < a2; n++ ) {
     if ( a0[n] == a1 ) { return ((char*)&a0[n]); }
   }

   return (char*)(NULL);
}


char *strtok(char *a0, const char *a1) {
   static char *a2 = NULL;

   if (  a0 ) { a2 = a0;     }
   if ( !a2 ) { return NULL; }

   char *p1 = a2;
   for ( ; *p1 &&  strchr(a1, *p1); p1++ );

   if ( !(*p1) ) { a2 = NULL; return NULL; }

   char *p2 = p1;
   for ( ; *p2 && !strchr(a1, *p2); p2++ );

   if ( !(*p2) ) { a2 = NULL; } 
   else { *p2 = '\0'; a2 = p2 + 1; }

   return p1;
}
