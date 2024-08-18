#ifndef __OSCA_X86_CORE_TTY_DRIVER_H__
#  include <stddef.h>
#  include <stdint.h>
#  include <sys/cdefs.h>

  typedef struct {
    uint8_t character, attribute;
  } __packed screen_char_t;

  typedef struct {
    uint32_t cursor_x, cursor_y;
    volatile unsigned char* video_memory;
  } __packed terminal_t;

  enum terminal_color;

  extern void terminal_initialize(void);
  extern void terminal_set_cursor(uint32_t x, uint32_t y);
  extern __forceinline void terminal_set_color(enum terminal_color background, enum terminal_color text);
  extern void terminal_putchar(char c);
  extern void terminal_writestring(const char *str);

/* Hardware text mode color constants. */
  typedef enum terminal_color {
	          VGA_COLOR_BLACK,
	           VGA_COLOR_BLUE,
	          VGA_COLOR_GREEN,
         	   VGA_COLOR_CYAN,
	            VGA_COLOR_RED,
	        VGA_COLOR_MAGENTA,
	         VGA_COLOR_YELLOW,
	     VGA_COLOR_LIGHT_GREY,
	      VGA_COLOR_DARK_GREY,
	     VGA_COLOR_LIGHT_BLUE,
	    VGA_COLOR_LIGHT_GREEN,
  	   VGA_COLOR_LIGHT_CYAN,
	      VGA_COLOR_LIGHT_RED,
  	VGA_COLOR_LIGHT_MAGENTA,
	    VGA_COLOR_LIGHT_BROWN,
  	        VGA_COLOR_WHITE
  } __packed terminal_color;
#  define __OSCA_X86_CORE_TTY_DRIVER_H__            1
#endif