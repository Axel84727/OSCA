#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

int  isalnum(int c) \
  { return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }

int  isalpha(int c) \
  { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'Z')); }

int  isascii(int c) \
  { return (c >= 0 && c <= 127); }

int  isblank(int c) \
  { return (c == ' ' || c == '\t'); }

int  iscntrl(int c) \
  { return ((c >= 0 && c <= 31) || c == 127); }

int  isdigit(int c) \
  { return (c >= '0' && c <= '9'); }

int  isgraph(int c) \
  { return (c >  ' ' && c <= '~'); }

int  islower(int c) \
  { return (c >= 'a' && c <= 'z'); }

int  isprint(int c) \
  { return (c >= ' ' && c <= '~'); }

int  ispunct(int c) \
  { return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') \
        ||  (c >= '[' && c <= '`') || (c >= '{' && c <= '~') ); }

int  isspace(int c) \
  { return ((c == ' ') || (c == '\f') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v')); }

int  isupper(int c) \
  { return (c >= 'A' && c <= 'Z'); }

int isxdigit(int c) \
  { return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')); }