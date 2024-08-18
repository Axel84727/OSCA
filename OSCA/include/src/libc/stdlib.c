#include <stdlib.h>
#include <ctype.h>
#include "_malloc.h"

int atoi(const char *str) {
  if (!str || !(*str)) { return 0; }

  int result =     0;
  bool  sign = false;

  for ( ; isspace(*str); str++ );

  if (*str == '-' || *str == '+') { if (*str == '-') { sign = true; } str++; }

  for ( ; isdigit(*str); result = result * 10 + (*str - '0'), str++ );

  return (sign ? -result : result);
}

long atol(const char *str) {
  if (!str || !(*str)) { return 0; }

  long result =   0;
  bool sign = false;

  for ( ; isspace(*str); str++ );

  if (*str == '-' || *str == '+') { if (*str == '-') { sign = true; } str++; }

  for ( ; isdigit(*str); result = result * 10 + (*str - '0'), str++ );

  return (sign ? -result : result);
}

double atof(const char *str) {
  double result = 0.0, factor = 1.0, fracPlace = 1.0;
  bool sign = false, frac = false, notation = false;

  for ( ; isspace(*str); str++ );

  if (*str == '-' || *str == '+') { if (*str == '-') { sign = true; } str++; }

  result = (double)(atol(str));
  if (*str == '.') {
    str++;
    frac = true;
  } else if (*str == 'e') {
    if ( *(str + 1) == '-' ) {
      
    } else {

    }
  }

  for ( ; isdigit(*str); str++ ) {
    result = result * 10.0 + (*str - '0');
    fracPlace *= 10.0;
    str++;
  }

  if (frac) { result /= fracPlace; }

  return (sign ? -result : result);
}

long strtol(const char *str, char **endptr, int base) {
  if (!str || !endptr || !(*endptr)) { return 0; }
  long result =   0;
  bool sign = false;

  for ( ; isspace(*str); str++ );

  if (*str == '-' || *str == '+') { if (*str == '-') { sign = true; } str++; }

  if ((base == 0 || base == 16) && (*(str + 1) == 'x' || *(str + 1) == 'X' )) {
    base = 16;
    str +=  2;
  } else if (base == 0 && *str == '0') {
    base =  8;
    str++;
  } else if (base == 0) {
    base = 10;
  }

  register int digit;
  for ( ; isalnum(*str); str++ ) {
    if      (*str >= '0' && *str <= '9') { digit = *str - '0';      }
    else if (*str >= 'a' && *str <= 'z') { digit = *str - 'a' + 10; }
    else { digit = *str - 'A' + 10; }

    if (digit >= base) break;
    result = result * base + digit;
  }

  if (endptr) { *endptr = (char *)str; }

  return (sign ? -result : result);
}

unsigned long strtoul(const char *str, char **endptr, int base) {
  if (!str || !endptr || !(*endptr)) { return 0; }

  unsigned long result = 0;

  for ( ; isspace(*str); str++ );

  if ((base == 0 || base == 16) && (*(str + 1) == 'x' || *(str + 1) == 'X' )) {
    base = 16;
    str +=  2;
  } else if (base == 0 && *str == '0') {
    base =  8;
    str++;
  } else if (base == 0) {
    base = 10;
  }

  register int digit;
  for ( ; isalnum(*str); str++ ) {
    if      (*str >= '0' && *str <= '9') { digit = *str - '0';      }
    else if (*str >= 'a' && *str <= 'z') { digit = *str - 'a' + 10; }
    else { digit = *str - 'A' + 10; }

    if (digit >= base) break;
    result = result * base + digit;
  }

  if (endptr) { *endptr = (char *)str; }

  return result;
}

#if    __STDC_VERSION__ > 199409L

long long atoll(const char *str) {
  if (!str || !(*str)) { return 0; }

  long long result =   0;
  bool sign = false;

  for ( ; isspace(*str); str++ );

  if (*str == '-' || *str == '+') { if (*str == '-') { sign = true; } str++; }

  for ( ; isdigit(*str); result = result * 10 + (*str - '0'), str++ );

  return (sign ? -result : result);
}

long long strtoll(const char *str, char **endptr, int base) {
  if (!str || !endptr || !(*endptr)) { return 0; }
  long long result =   0;
  bool sign = false;

  for ( ; isspace(*str); str++ );

  if (*str == '-' || *str == '+') { if (*str == '-') { sign = true; } str++; }

  if ((base == 0 || base == 16) && (*(str + 1) == 'x' || *(str + 1) == 'X' )) {
    base = 16;
    str +=  2;
  } else if (base == 0 && *str == '0') {
    base =  8;
    str++;
  } else if (base == 0) {
    base = 10;
  }

  register int digit;
  for ( ; isalnum(*str); str++ ) {
    if      (*str >= '0' && *str <= '9') { digit = *str - '0';      }
    else if (*str >= 'a' && *str <= 'z') { digit = *str - 'a' + 10; }
    else { digit = *str - 'A' + 10; }

    if (digit >= base) break;
    result = result * base + digit;
  }

  if (endptr) { *endptr = (char *)str; }

  return (sign ? -result : result);
}

unsigned long long strtoull(const char *str, char **endptr, int base) {
  if (!str || !endptr || !(*endptr)) { return 0; }

  unsigned long long result = 0;

  for ( ; isspace(*str); str++ );

  if ((base == 0 || base == 16) && (*(str + 1) == 'x' || *(str + 1) == 'X' )) {
    base = 16;
    str +=  2;
  } else if (base == 0 && *str == '0') {
    base =  8;
    str++;
  } else if (base == 0) {
    base = 10;
  }

  register int digit;
  for ( ; isalnum(*str); str++ ) {
    if      (*str >= '0' && *str <= '9') { digit = *str - '0';      }
    else if (*str >= 'a' && *str <= 'z') { digit = *str - 'a' + 10; }
    else { digit = *str - 'A' + 10; }

    if (digit >= base) break;
    result = result * base + digit;
  }

  if (endptr) { *endptr = (char *)str; }

  return result;
}

#endif