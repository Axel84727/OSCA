#include <stdint.h>
#include <stddef.h>
#include <float.h>

#define flt float

__forceinline flt __builtin_buildinf(void) {
  static __flt_repr_t _infinity;
#if __NAN_INFINITY_SUPPORTED__
  _infinity.y = 0x7F800000;
#else
  _infinity.y = 0x7C00;
#endif
  return _infinity.x; /* x = float, y = int32_t */
}

__forceinline flt __builtin_buildnan(void) {
  static __flt_repr_t _nan;
#if __NAN_INFINITY_SUPPORTED__
  _nan.y = 0x7FC00000;
#else
  _infinity.y = 0x7E00;
#endif
  return _nan.x; /* x = float, y = int32_t */
}

#undef flt