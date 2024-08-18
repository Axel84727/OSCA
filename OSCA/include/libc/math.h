#ifndef __OSCA_LIBC_MATH_H__

#  if !defined(__MATH_H_SYMBOLS__)
#    define        M_E		2.71828182845904523539
#    define    M_LOG2E		1.44269504088896340739
#    define   M_LOG10E	   0.43429448190325182765
#    define      M_LN2		0.69314718055994530942
#    define     M_LN10		2.30258509299404568402
#    define       M_PI		3.14159265358979323846
#    define     M_PI_2		1.57079632679489661923
#    define     M_PI_4		0.78539816339744830962
#    define     M_1_PI		0.31830988618379067154
#    define     M_2_PI		0.63661977236758134308
#    define M_2_SQRTPI	   1.12837916709551257390
#    define    M_SQRT2		1.41421356237309504880
#    define  M_SQRT1_2	   0.70710678118654752440
#    define __MATH_H_SYMBOLS__                  1
#  endif

   extern float fabsf(float);
   extern double fabs(double);
   
   extern float floorf(float);
   extern double floor(double);

   extern float  ceilf(float);
   extern double  ceil(double);

   extern float fmodf(float, float);
   extern double fmod(double, double);

   extern float  powf(float, float);
   extern double  pow(double, double);

   extern float  expf(float);
   extern double  exp(double);
   
   extern float  logf(float);
   extern double  log(double);
#  define __OSCA_LIBC_MATH_H__                  1
#endif