#include <math.h>
#include <float.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/cdefs.h>

float fabsf(float x)   { return ( x >= 0.0f ? x : -x ); }
double fabs(double x)  { return ( x >= 0.0  ? x : -x ); }
float floorf(float x)  { int32_t ipart = (int32_t)x; return (x < ipart ? (ipart - 1) : ipart); }
double floor(double x) { int64_t ipart = (int64_t)x; return (x < ipart ? (ipart - 1) : ipart); }
float  ceilf(float x)  { int32_t ipart = (int32_t)x; return (x > ipart ? (ipart + 1) : ipart); }
double  ceil(double x) { int64_t ipart = (int64_t)x; return (x > ipart ? (ipart + 1) : ipart); }
float  fmodf(float x, float y) { 
  if ( y == 0.0f ) { return (float)(0.0f / 0.0f); /* 0 / 0 = NaN in every compiler */ }
  float remainder = x - (float)( (int32_t)(x / y) * y );

  if ( (remainder * y) < 0 ) { remainder += y; }

  return remainder;
}

double  fmod(double x, double y) {
  if ( y == 0.0f ) { return (float)(0.0f / 0.0f); }
  float remainder = x - (float)( (int32_t)(x / y) * y );

  if ( (remainder * y) < 0 ) { remainder += y; }

  return remainder;
}

float powf(float x, float y) {
  if (x == 0.0f || y == 1.0f) { return x; }
  else if (y == 0.0f) { return 1.0f; }
  
  bool negative;
  if ((y - (int32_t)y ) == 0.0f) {
    negative = (y < 0.0f);
    if (negative) { y = -y; }

    float result = 1.0f;
    for ( ; y > 0.0f; (fmodf(y, 2.0f) == 1.0f) ? result *= x : (void)0, x *= x, y = floorf(y / 2.0f) );

    return negative ? (1.0f / result) : result;
  }
  negative = (x < 0.0f);
  if (negative) { x = -x; }

  return expf(y * logf(x));
}

double pow(double x, double y) {
  if (x == 0.0 || y == 1.0) { return x; }
  else if (y == 0.0) { return 1.0; }

  bool negative;
  if (y - (uint64_t)y == 0.0) {
    negative = (y < 0.0);
    if (negative) { y = -y; }

    double result = 1.0;
    for ( ; y > 0.0; (fmod(y, 2.0) == 1.0) ? result *= x : (void)0, x *= x, y = floor(y / 2.0) );

    return negative ? (1.0 / result) : result;
  }
  negative = (x < 0.0);
  if (negative) { x = -x; }

  return exp(y * log(x));
}

float expf(float x) {
  if (x == 1.0f) { return (float)M_E; }
  else if (x == 0.0f) { return  1.0f; }

  bool negative = (x < 0.0f);
  if (negative) { x = -x; }

  float result = 1.0f, term = 1.0f;
  size_t n = 1;
  for ( ; fabsf(term) > FLT_EPSILON; n++, term *= x / n, result += term );

  return negative ? (1.0f / result) : result;
}

double exp(double x) {
  if (x == 1.0) { return (double)M_E; }
  else if (x == 0.0) { return 1.0; }

  bool negative = (x < 0.0);
  if (negative) { x = -x; }

  double result = 1.0, term = 1.0;
  size_t n = 1;
  for ( ; fabs(term) > DBL_EPSILON; n++, term *= x / n, result += term );

  return negative ? (1.0 / result) : result;
}

float logf(float x) {
#if defined(NAN)
  if (x <= 0.0f) { return x < 0.0f ? -NAN : NAN; }
#elif defined(INFINITY)
  if (x <= 0.0f) { return x < 0.0f ? -INFINITY : INFINITY; }
#else
  if (x <= 0.0f) { return x < 0.0f ? (-0.0f / 0.0f) : 0.0f / 0.0f; /* 0.0 / 0.0 = NAN on each compiler */ }
#endif
  else if (x == 1.0f) { return 0.0f; }
  else if (x == (float)M_E) { return 1.0f; }

  float term = (x - 1.0f) / (x + 1.0f), sum = 0.0f, term_pow = term, term_sq = term * term;

  size_t n = 1;
  for ( ; fabsf(term_pow) > FLT_EPSILON; sum += term_pow / n, term_pow *= term_sq, n += 2 );

  return 2.0f * sum;
}

double log(double x) {
#if defined(NAN)
  if (x <= 0.0) { return x < 0.0 ? -NAN : NAN; }
#elif defined(INFINITY)
  if (x <= 0.0) { return x < 0.0 ? -INFINITY : INFINITY; }
#else
  if (x <= 0.0) { return x < 0.0 ? (-0.0 / 0.0) : 0.0 / 0.0; /* 0.0 / 0.0 = NAN on each compiler */ }
#endif
  else if (x == 1.0) { return 0.0; }
  else if (x == (double)M_E) { return 1.0; }

  float term = (x - 1.0) / (x + 1.0), sum = 0.0, term_pow = term, term_sq = term * term;

  size_t n = 1;
  for ( ; fabsf(term_pow) > DBL_EPSILON; sum += term_pow / n, term_pow *= term_sq, n += 2 );

  return 2.0 * sum;
}