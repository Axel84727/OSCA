#include <x86/driver/tty.h>
#include <x86/driver/io.h>

#define VIDEO_MEMORY 0xb8000
#define SCREEN_WIDTH      80
#define SCREEN_HEIGHT     25
#define TAB_STOP           8

#define PIT_CHANNEL0    0x40
#define PIT_COMMAND     0x43
#define PIT_FREQ     1193180

static terminal_t _terminal;

static uint8_t _terminal_color;
static const int16_t sz = SCREEN_WIDTH * SCREEN_HEIGHT;
static const int16_t su = (SCREEN_WIDTH * (SCREEN_HEIGHT - 1));
static size_t n = 0;

void terminal_initialize(void) {
  _terminal.video_memory = (screen_char_t*)VIDEO_MEMORY;
  _terminal.cursor_x = 0, _terminal.cursor_y = 0;
  if (!_terminal_color) { terminal_set_color(VGA_COLOR_BLACK, VGA_COLOR_YELLOW); }
  for ( n = 0; n < sz; n++ ) {
    _terminal.video_memory[n * 2    ] = ' ';
    _terminal.video_memory[n * 2 + 1] = _terminal_color;
  }
}

__forceinline void terminal_set_color(enum terminal_color bp, enum terminal_color fp) {
  _terminal_color = fp | (bp << 4);
}

void terminal_set_cursor(uint32_t x, uint32_t y) {
  uint32_t pos = y * SCREEN_WIDTH + x;
  outb(0x3D4, 0x0F);
  outb(0x3D5, pos & 0xFF);
  outb(0x3D4, 0x0E);
  outb(0x3D5, (pos >> 8) & 0xFF);
  _terminal.cursor_x = x, _terminal.cursor_y = y;
}

static __forceinline void beep(uint32_t frequency) {
  uint32_t divisor = PIT_FREQ / frequency;
  
  outb(PIT_COMMAND, 0x36);

  outb(PIT_CHANNEL0, divisor & 0xFF);
  outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);
}

void terminal_putchar(char c) {
  switch (c) {
    case '\n': {
      _terminal.cursor_x = 0;
      if (++_terminal.cursor_y >= SCREEN_HEIGHT) {
        for ( n = 0; n < su; n++ ) {
          _terminal.video_memory[n * 2] = _terminal.video_memory[(n + SCREEN_WIDTH) * 2];
        }

        for ( n = su; n < sz; n++ ) {
          _terminal.video_memory[n * 2    ] = ' ';
          _terminal.video_memory[n * 2 + 1] = _terminal_color;
        }

        _terminal.cursor_y = SCREEN_HEIGHT - 1;
      }

      break;
    }

    case '\t': {
      _terminal.cursor_x = (_terminal.cursor_x + TAB_STOP) & ~(TAB_STOP - 1);
      if (_terminal.cursor_x >= SCREEN_WIDTH) {
        _terminal.cursor_x = 0;
        if (++_terminal.cursor_y >= SCREEN_HEIGHT) {
          for ( n = 0; n < su; n++ ) {
            _terminal.video_memory[n * 2    ] = _terminal.video_memory[(n + SCREEN_WIDTH) * 2    ];
            _terminal.video_memory[n * 2 + 1] = _terminal.video_memory[(n + SCREEN_WIDTH) * 2 + 1];
          }

          for ( n = su; n < sz; n++ ) {
            _terminal.video_memory[n * 2    ] = ' ';
            _terminal.video_memory[n * 2 + 1] = _terminal_color;
          }

          _terminal.cursor_y = SCREEN_HEIGHT - 1;
        }
      }

      break;
    }

    case '\r': {
      _terminal.cursor_x = 0;
      break;
    }

    case '\b': {
      if (_terminal.cursor_x > 0) {
        _terminal.cursor_x--;
        _terminal.video_memory[(_terminal.cursor_y * SCREEN_WIDTH + _terminal.cursor_x) * 2    ] = ' ';
        _terminal.video_memory[(_terminal.cursor_y * SCREEN_WIDTH + _terminal.cursor_x) * 2 + 1] = _terminal_color;
      }

      break;
    }

    case '\f': {
      for ( n = 0; n < su; n++ ) {
        _terminal.video_memory[n * 2    ] = ' ';
        _terminal.video_memory[n * 2 + 1] = _terminal_color;
      }
      _terminal.cursor_x = 0;
      _terminal.cursor_y = 0;

      break;
    }

    case '\a': {
      beep(1000);
      break; /* Nothing for now */
    }

    default: {
      n = (_terminal.cursor_y * SCREEN_WIDTH + _terminal.cursor_x) * 2;
      _terminal.video_memory[n    ] = c;
      _terminal.video_memory[n + 1] = _terminal_color;
      if (++_terminal.cursor_x >= SCREEN_WIDTH) {
        _terminal.cursor_x = 0;
        if (++_terminal.cursor_y >= SCREEN_HEIGHT) {
          for ( n = 0; n < su; n++ ) {
            _terminal.video_memory[n * 2] = _terminal.video_memory[(n + SCREEN_WIDTH) * 2];
          }

          for ( n = su; n < sz; n++ ) {
            _terminal.video_memory[n * 2    ] = ' ';
            _terminal.video_memory[n * 2 + 1] = _terminal_color;
          }
          _terminal.cursor_y = SCREEN_HEIGHT - 1;
        }
      }
    }
  }

  terminal_set_cursor(_terminal.cursor_x, _terminal.cursor_y);
}

void terminal_writestring(const char *str) {
  while (*str) {
    terminal_putchar(*str++);
  }
}