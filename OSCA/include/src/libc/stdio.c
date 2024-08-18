#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <x86/driver/tty.h>
#include <sys/cdefs.h>

static void reverse( char *low, char *ptr ) {
  if (!low || !ptr) { return ; }

  register char temp;
  do {
    temp = *low;
    *(low++) = *ptr, *ptr = temp;
  } while (low < ptr);
}

static const char bases_36[37] = "0123456789abcdefghijklmnopqrstuvwxyz";

// Funciones itoa y utoa previamente definidas
static char *itoa(int value, char* str, int base) {
  if      (!value) { *str = '0', *(str + 1) = '\0'; return NULL; }
  else if (!base) { base = 10; }
  char* rc;
  char* ptr;
  char* low;

  // Check for valid base
  if (base < 2 || base > 36) {
    *str = '\0';
    return NULL;
  }

  rc = ptr = str;

  // Set '-' for negative decimals
  if (value < 0 && base == 10) {
    *(ptr++) = '-';
    value = -value;
  }

  // Remember where the numbers start
  low = ptr;

  do {
    // Modulo is negative for negative value. This trick makes abs() unnecessary
    *(ptr++) = bases_36[value % base];
    value /= base;
  } while (value);

  // Terminate string in buffer
  *(ptr--) = '\0';

  reverse(low, ptr);
  return rc;
}

static void utoa(unsigned int value, char* str, int base) {
  if      (!value) { *str = '0', *(str + 1) = '\0'; return; }
  else if (!base) { base = 10; }
  char* rc;
  char* ptr;
  char* low;

  // Check for valid base
  if (base < 2 || base > 36) {
    *str = '\0';
    return ;
  }

  rc = ptr = str;

  // Remember where the numbers start
  low = ptr;

  // The actual conversion
  do {
    // Modulo is negative for negative value. This trick makes abs() unnecessary
    *(ptr++) = bases_36[value % base];
    value /= base;
  } while (value);

  // Terminate string in buffer
  *(ptr--) = '\0';

  reverse(low, ptr);
}

static void fillwz(int num, int precision, int base, char *str) {
  if (!num) { return; } else if ( !str ) { return; }
  else if (!precision) { precision = 11; } if (!base) { base = 10; }

  int num_digs = 0;
  int temp = num;
#if    __POINTER_SIZE__ == 2
  for ( ; temp; num_digs++, temp /= 10 ) {
    if ( temp ) { num_digs++, temp /= 10; }
  }
#elif  __POINTER_SIZE__ == 4
  for ( ; temp; num_digs++, temp /= 10 ) {
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
  }
#elif  __POINTER_SIZE__ == 8
  for ( ; temp; num_digs++, temp /= 10 ) {
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
  }
#endif
  for ( ; temp; num_digs++, temp /= 10 );

  int num_zeros = (precision > num_digs) ? (precision - num_digs) : 0;

  int n = 0;
#if    __POINTER_SIZE__ == 2
  for ( ; (n + __POINTER_SIZE__) < num_zeros; n += __POINTER_SIZE__ ) {
    str[n    ] = '0';
    str[n + 1] = '0';
  }
#elif  __POINTER_SIZE__ == 4
  for ( ; (n + __POINTER_SIZE__) < num_zeros; n += __POINTER_SIZE__ ) {
    str[n    ] = '0';
    str[n + 1] = '0';
    str[n + 2] = '0';
    str[n + 3] = '0';
  }
#elif  __POINTER_SIZE__ == 8
  for ( ; (n + __POINTER_SIZE__) < num_zeros; n += __POINTER_SIZE__ ) {
    str[n    ] = '0';
    str[n + 1] = '0';
    str[n + 2] = '0';
    str[n + 3] = '0';
    str[n + 4] = '0';
    str[n + 5] = '0';
    str[n + 6] = '0';
    str[n + 7] = '0';
  }
#endif
  for ( ; n < num_zeros; str[n++] = '0' );
  itoa(num, str + num_zeros, base);
}

static void fillwzu(unsigned int num, int precision, int base, char *str) {
  if (!num) { return; } else if ( !str ) { return; }
  else if (!precision) { precision = 11; } if (!base) { base = 10; }

  int num_digs = 0;
  unsigned int temp = num;
#if    __POINTER_SIZE__ == 2
  for ( ; temp; num_digs++, temp /= 10 ) {
    if ( temp ) { num_digs++, temp /= 10; }
  }
#elif  __POINTER_SIZE__ == 4
  for ( ; temp; num_digs++, temp /= 10 ) {
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
  }
#elif  __POINTER_SIZE__ == 8
  for ( ; temp; num_digs++, temp /= 10 ) {
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
    if ( temp ) { num_digs++, temp /= 10; }
  }
#endif
  for ( ; temp; num_digs++, temp /= 10 );

  int num_zeros = (precision > num_digs) ? (precision - num_digs) : 0;

  int n = 0;
#if    __POINTER_SIZE__ == 2
  for ( ; (n + __POINTER_SIZE__) < num_zeros; n += __POINTER_SIZE__ ) {
    str[n    ] = '0';
    str[n + 1] = '0';
  }
#elif  __POINTER_SIZE__ == 4
  for ( ; (n + __POINTER_SIZE__) < num_zeros; n += __POINTER_SIZE__ ) {
    str[n    ] = '0';
    str[n + 1] = '0';
    str[n + 2] = '0';
    str[n + 3] = '0';
  }
#elif  __POINTER_SIZE__ == 8
  for ( ; (n + __POINTER_SIZE__) < num_zeros; n += __POINTER_SIZE__ ) {
    str[n    ] = '0';
    str[n + 1] = '0';
    str[n + 2] = '0';
    str[n + 3] = '0';
    str[n + 4] = '0';
    str[n + 5] = '0';
    str[n + 6] = '0';
    str[n + 7] = '0';
  }
#endif
  for ( ; n < num_zeros; str[n++] = '0' );
  utoa(num, str + num_zeros, base);
}

#  define   ltoa  itoa
#  define  ultoa  itoa
#  define  lltoa  itoa
#  define ulltoa  utoa
#if  __STDC_VERSION__ > 199409L
static void lftoa(long double num, char *str, int precision) {
  if      ( !num || !str || !(*str) ) { *str = '0', *(str+1) = '\0'; }
  else if (!precision) { precision = 6; }
  i64    ipart =    (i64)num;
  long double fpart = num - (long double)ipart;
  *(str + (precision - 1)) = '\0'; /* Converts the '.' to '\0' temporally for int part */
  lltoa((i64)num, str, 10);
  *(str + (precision - 1)) =  '.'; /* Restores the '.' for the fractional part */

  register int digit;
  for ( ; precision; fpart *= 10, digit = (int)fpart, *(str++) = digit + '0', fpart -= digit );

  *str = '\0';
}
#else
#  define lftoa ftoa
#endif

static void ftoa(double num, char *str, int precision) {
    if (precision < 0) precision = 6; // Default precision

    if (num == 0.0) {
        size_t len = strlen("0.");
        strncpy(str, "0.", len);
        memset(str + (len - 1), '0', precision);
        return;
    }

  int32_t ipart = (int32_t)num;
  float   fpart = num - ipart;

  if (num < 0) {
    *(str++) = '-';
    ipart = -ipart;
    fpart = -fpart;
  }

  char  buffer[32];
  char *p = buffer, *b = buffer;

  do {
    *(p++) = bases_36[ipart % 10];
    ipart /= 10;
  } while (ipart);

  reverse(b, p);
  strcpy(str, buffer);

  *(str++) = '.';

  register int digit;
  for ( ; precision--; fpart *= 10, digit = (int)fpart, *(str++) = bases_36[digit % 10], fpart -= digit );

  *str = '\0';
}

// Función vsnprintf
int vsnprintf(char* buffer, size_t size, const char* format, va_list args) {
    char* buf_ptr = buffer;
    const char* fmt_ptr = format;
    size_t len = 0, precision = 6;

    while (*fmt_ptr != '\0') {
        if (*fmt_ptr == '%' && *(fmt_ptr + 1) != '\0') {
            fmt_ptr++;
            if (*fmt_ptr == 'i' || *fmt_ptr == 'I' || *fmt_ptr == 'd' || *fmt_ptr == 'D') {
                int val = va_arg(args, int);
                char temp[12]; // Espacio suficiente para un entero de 32 bits
                itoa(val, temp, 10);
                char* t_ptr;
                for ( t_ptr = temp; *t_ptr != '\0' && len < size - 1; t_ptr++) {
                    *buf_ptr++ = *t_ptr;
                    len++;
                }
            } else if (*fmt_ptr == 'u' || *fmt_ptr == 'U') {
                unsigned int val = va_arg(args, unsigned int);
                char temp[12]; // Espacio suficiente para un entero sin signo de 32 bits
                utoa(val, temp, 10);
                char* t_ptr;
                for ( t_ptr = temp; *t_ptr != '\0' && len < size - 1; t_ptr++) {
                    *buf_ptr++ = *t_ptr;
                    len++;
                }
            } else if (*fmt_ptr == 'x' || *fmt_ptr == 'X') {
                unsigned int val = va_arg(args, unsigned int);
                char temp[9];
                utoa(val, temp, 16);
                char* t_ptr;
                for ( t_ptr = temp; *t_ptr && len < size - 1; t_ptr++ ) {
                    *(buf_ptr++) = *t_ptr;
                    len++;
                }
            } else if (*fmt_ptr == 's' || *fmt_ptr == 'S') {
                const char *s_ptr = va_arg(args, const char *);
                for ( ; *s_ptr && len < size - 1; s_ptr++ ) {
                    *(buf_ptr++) = *s_ptr;
                    len++;
                }
            } else if (*fmt_ptr == 'f' || *fmt_ptr == 'F') {
                float val = va_arg(args, float);
                int num_digs = 0;
                i32 ipart = (int)(val);
                for ( ; ipart /= 10; num_digs++ );
                char temp[num_digs + precision]; /* 2 for '.' and '\0', 6 for number */
                ftoa(val, temp, precision);
                char *t_ptr;
                for ( t_ptr = temp; *t_ptr && len < size - 1; t_ptr++ ) {
                    *(buf_ptr++) = *t_ptr;
                    len++;
                }
            } else if (*fmt_ptr == '.' || *fmt_ptr == '*') {
                if (*(fmt_ptr++) == '*') {
                  precision = va_arg(args, int);
                } else {
                  precision = atoi(fmt_ptr + 1);
                }

                fmt_ptr++;
                if (*fmt_ptr == 'i' || *fmt_ptr == 'I' || *fmt_ptr == 'd' || *fmt_ptr == 'D') {
                    int val = va_arg(args, int);
                    char temp[precision + 1]; // Espacio suficiente para un entero de 32 bits
                    fillwz(val, precision, 10, temp);
                    char* t_ptr;
                    for ( t_ptr = temp; *t_ptr != '\0' && len < size - 1; t_ptr++) {
                        *buf_ptr++ = *t_ptr;
                        len++;
                    }
                } else if (*fmt_ptr == 'u' || *fmt_ptr == 'U') {
                    unsigned int val = va_arg(args, unsigned int);
                    char temp[precision + 1]; // Espacio suficiente para un entero de 32 bits
                    fillwzu(val, precision, 10, temp);
                    char* t_ptr;
                    for ( t_ptr = temp; *t_ptr != '\0' && len < size - 1; t_ptr++) {
                        *buf_ptr++ = *t_ptr;
                        len++;
                    }
                } else if (*fmt_ptr == 'x' || *fmt_ptr == 'X') {
                    unsigned int val = va_arg(args, unsigned int);
                    char temp[precision + 1]; // Espacio suficiente para un entero de 32 bits
                    fillwzu(val, precision, 16, temp);
                    char* t_ptr;
                    for ( t_ptr = temp; *t_ptr != '\0' && len < size - 1; t_ptr++) {
                        *buf_ptr++ = *t_ptr;
                        len++;
                    }
                } else if (*fmt_ptr == 's' || *fmt_ptr == 'S') {
                    const char *s_ptr = va_arg(args, const char *);
                    int n = 0;
                    for ( ; n < precision && *s_ptr && len < size - 1; s_ptr++ ) {
                        *(buf_ptr++) = *s_ptr;
                        len++;
                    }
                } else if (*fmt_ptr == 'f' || *fmt_ptr == 'F') {
                  float val = va_arg(args, float);
                  int num_digs = 0;
                  i32 ipart = (int)(val);
                  for ( ; ipart /= 10; num_digs++ );
                  char temp[num_digs + precision]; /* 2 for '.' and '\0', 6 for number */
                  ftoa(val, temp, precision);
                  char *t_ptr;
                  for ( t_ptr = temp; *t_ptr && len < size - 1; t_ptr++ ) {
                      *(buf_ptr++) = *t_ptr;
                      len++;
                  }
                } else if (*fmt_ptr == 'l' || *fmt_ptr == 'L') {
                    if (*fmt_ptr == 'L') {
                      
                    } else {

                    }
                }
            }
        } else {
            if (len < size - 1) {
                *buf_ptr++ = *fmt_ptr;
                len++;
            }
        }
        fmt_ptr++;
    }

    // Null-terminate el buffer
    if (size > 0) {
        *buf_ptr = '\0';
    }

    return len;
}

#define SIZE_MAX ((size_t)-1)

int vprintf(char *str, const char *fmt, va_list args) {
  return vsnprintf(str, SIZE_MAX, fmt, args);
}

int sprintf(char *str, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(str, SIZE_MAX, fmt, args);
  va_end(args);
  return len;
}

int snprintf(char *str, size_t n, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(str, n, fmt, args);
  va_end(args);
  return len;
}

#define BUF_MAX 100

int printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  static char buf[BUF_MAX];
  int len = vsnprintf(buf, BUF_MAX, fmt, args);
  va_end(args);

  terminal_writestring(buf);
  return len;
}