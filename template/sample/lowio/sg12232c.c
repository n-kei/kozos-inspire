#include "sg12232c.h"
#include "defines.h"

static const uint8 FONT_X = 5;
static const uint8 FONT_Y = 7;
static const uint16 FONT_MIN_CODE = 0x20;
static const uint16 FONT_MAX_CODE = 0x7F;

#define swap(a,b) {int c=a;a=b;b=c;}
#define abs(n) (((int)(n) < 0) ? ((int)(n) * (-1)) : (n))

#define H8_3069F_P4DDR  ((volatile uint8 *)0xFEE003)
#define H8_3069F_P4DR   ((volatile uint8 *)0xFFFFD3)
#define H8_3069F_CSCR   ((volatile uint8 *)0xFEE01F)

#define LCD_ADDR_LEFT   ((volatile uint8 *)0x800000)
#define LCD_ADDR_RIGHT  ((volatile uint8 *)0xA00000)
#define LCD_AOFS_CMD    (0)
#define LCD_AOFS_DAT    (1 << 3)

#define BIT_LCD_RES     (1 << 7)
#define BIT_SDC_CS      (1 << 0)
#define BIT_VSCCS       (1 << 2)
#define BIT_VSDCS       (1 << 3)
#define BIT_VSRST       (1 << 5)

#define LCD1_CMD(VAL) \
  do { \
    *(LCD_ADDR_LEFT + LCD_AOFS_CMD) = (VAL); \
  } while (0)

#define LCD1_DAT_WRITE(VAL) \
  do { \
    *(LCD_ADDR_LEFT + LCD_AOFS_DAT) = (VAL); \
  } while (0)

#define LCD1_DAT_READ() (*(LCD_ADDR_LEFT + LCD_AOFS_DAT))

#define LCD2_CMD(VAL) \
  do { \
    *(LCD_ADDR_RIGHT + LCD_AOFS_CMD) = (VAL); \
  } while (0)

#define LCD2_DAT_WRITE(VAL) \
  do { \
    *(LCD_ADDR_RIGHT + LCD_AOFS_DAT) = (VAL); \
  } while (0)

#define LCD2_DAT_READ() (*(LCD_ADDR_RIGHT + LCD_AOFS_DAT))

static const uint8 font5x7_data[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, // (white space)
  0x00, 0x00, 0x5F, 0x00, 0x00, // !
  0x00, 0x07, 0x00, 0x07, 0x00, // "
  0x14, 0x7F, 0x14, 0x7F, 0x14, // #
  0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
  0x23, 0x13, 0x08, 0x64, 0x62, // %
  0x36, 0x49, 0x55, 0x22, 0x50, // &
  0x00, 0x05, 0x03, 0x00, 0x00, // '
  0x00, 0x1C, 0x22, 0x41, 0x00, // (
  0x00, 0x41, 0x22, 0x1C, 0x00, // )
  0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
  0x08, 0x08, 0x3E, 0x08, 0x08, // +
  0x00, 0x50, 0x30, 0x00, 0x00, // ,
  0x08, 0x08, 0x08, 0x08, 0x08, // -
  0x00, 0x60, 0x60, 0x00, 0x00, // .
  0x20, 0x10, 0x08, 0x04, 0x02, // /
  0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
  0x00, 0x42, 0x7F, 0x40, 0x00, // 1
  0x42, 0x61, 0x51, 0x49, 0x46, // 2
  0x21, 0x41, 0x45, 0x4B, 0x31, // 3
  0x18, 0x14, 0x12, 0x7F, 0x10, // 4
  0x27, 0x45, 0x45, 0x45, 0x39, // 5
  0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
  0x01, 0x71, 0x09, 0x05, 0x03, // 7
  0x36, 0x49, 0x49, 0x49, 0x36, // 8
  0x06, 0x49, 0x49, 0x29, 0x1E, // 9
  0x00, 0x36, 0x36, 0x00, 0x00, // :
  0x00, 0x56, 0x36, 0x00, 0x00, // ;
  0x00, 0x08, 0x14, 0x22, 0x41, // <
  0x14, 0x14, 0x14, 0x14, 0x14, // =
  0x41, 0x22, 0x14, 0x08, 0x00, // >
  0x02, 0x01, 0x51, 0x09, 0x06, // ?
  0x32, 0x49, 0x79, 0x41, 0x3E, // @
  0x7E, 0x11, 0x11, 0x11, 0x7E, // A
  0x7F, 0x49, 0x49, 0x49, 0x36, // B
  0x3E, 0x41, 0x41, 0x41, 0x22, // C
  0x7F, 0x41, 0x41, 0x22, 0x1C, // D
  0x7F, 0x49, 0x49, 0x49, 0x41, // E
  0x7F, 0x09, 0x09, 0x01, 0x01, // F
  0x3E, 0x41, 0x41, 0x51, 0x32, // G
  0x7F, 0x08, 0x08, 0x08, 0x7F, // H
  0x00, 0x41, 0x7F, 0x41, 0x00, // I
  0x20, 0x40, 0x41, 0x3F, 0x01, // J
  0x7F, 0x08, 0x14, 0x22, 0x41, // K
  0x7F, 0x40, 0x40, 0x40, 0x40, // L
  0x7F, 0x02, 0x04, 0x02, 0x7F, // M
  0x7F, 0x04, 0x08, 0x10, 0x7F, // N
  0x3E, 0x41, 0x41, 0x41, 0x3E, // O
  0x7F, 0x09, 0x09, 0x09, 0x06, // P
  0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
  0x7F, 0x09, 0x19, 0x29, 0x46, // R
  0x46, 0x49, 0x49, 0x49, 0x31, // S
  0x01, 0x01, 0x7F, 0x01, 0x01, // T
  0x3F, 0x40, 0x40, 0x40, 0x3F, // U
  0x1F, 0x20, 0x40, 0x20, 0x1F, // V
  0x7F, 0x20, 0x18, 0x20, 0x7F, // W
  0x63, 0x14, 0x08, 0x14, 0x63, // X
  0x03, 0x04, 0x78, 0x04, 0x03, // Y
  0x61, 0x51, 0x49, 0x45, 0x43, // Z
  0x00, 0x00, 0x7F, 0x41, 0x41, // [
  0x02, 0x04, 0x08, 0x10, 0x20, // /
  0x41, 0x41, 0x7F, 0x00, 0x00, // ]
  0x04, 0x02, 0x01, 0x02, 0x04, // ^
  0x40, 0x40, 0x40, 0x40, 0x40, // _
  0x00, 0x01, 0x02, 0x04, 0x00, // `
  0x20, 0x54, 0x54, 0x54, 0x78, // a
  0x7F, 0x48, 0x44, 0x44, 0x38, // b
  0x38, 0x44, 0x44, 0x44, 0x20, // c
  0x38, 0x44, 0x44, 0x48, 0x7F, // d
  0x38, 0x54, 0x54, 0x54, 0x18, // e
  0x08, 0x7E, 0x09, 0x01, 0x02, // f
  0x08, 0x14, 0x54, 0x54, 0x3C, // g
  0x7F, 0x08, 0x04, 0x04, 0x78, // h
  0x00, 0x44, 0x7D, 0x40, 0x00, // i
  0x20, 0x40, 0x44, 0x3D, 0x00, // j
  0x00, 0x7F, 0x10, 0x28, 0x44, // k
  0x00, 0x41, 0x7F, 0x40, 0x00, // l
  0x7C, 0x04, 0x18, 0x04, 0x78, // m
  0x7C, 0x08, 0x04, 0x04, 0x78, // n
  0x38, 0x44, 0x44, 0x44, 0x38, // o
  0x7C, 0x14, 0x14, 0x14, 0x08, // p
  0x08, 0x14, 0x14, 0x18, 0x7C, // q
  0x7C, 0x08, 0x04, 0x04, 0x08, // r
  0x48, 0x54, 0x54, 0x54, 0x20, // s
  0x04, 0x3F, 0x44, 0x40, 0x20, // t
  0x3C, 0x40, 0x40, 0x20, 0x7C, // u
  0x1C, 0x20, 0x40, 0x20, 0x1C, // v
  0x3C, 0x40, 0x30, 0x40, 0x3C, // w
  0x44, 0x28, 0x10, 0x28, 0x44, // x
  0x0C, 0x50, 0x50, 0x50, 0x3C, // y
  0x44, 0x64, 0x54, 0x4C, 0x44, // z
  0x00, 0x08, 0x36, 0x41, 0x00, // {
  0x00, 0x00, 0x7F, 0x00, 0x00, // |
  0x00, 0x41, 0x36, 0x08, 0x00, // }
  0x08, 0x08, 0x2A, 0x1C, 0x08, // ->
  0x08, 0x1C, 0x2A, 0x08, 0x08  // <-
};

void sg12232c_init(void)
{
  *H8_3069F_P4DDR = BIT_LCD_RES | BIT_SDC_CS | BIT_VSCCS | BIT_VSDCS | BIT_VSRST;

  /*
   * L->H : 68K mode.
   */
  *H8_3069F_P4DR &= ~BIT_LCD_RES;
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");
  *H8_3069F_P4DR |= BIT_LCD_RES;

  *H8_3069F_CSCR = 0x3F;

  LCD1_CMD(0xE2);   // Reset
  LCD1_CMD(0xA4);   // Static Drive Off
  LCD1_CMD(0xC0);   // Display Start Line
  LCD1_CMD(0xAF);   // Display On
  LCD1_CMD(0xB8);   // Page Address Setup
  LCD1_CMD(0x00);   // Column Address

  LCD2_CMD(0xE2);   // Reset
  LCD2_CMD(0xA4);   // Static Drive Off
  LCD2_CMD(0xC0);   // Display Start Line
  LCD2_CMD(0xAF);   // Display On
  LCD2_CMD(0xB8);   // Page Address Setup
  LCD2_CMD(0x00);   // Column Address
}

void sg12232c_clear(void)
{
  int p, c;

  for (p = 0; p <= 3; p++) {
    LCD1_CMD(0xB8 | (p & 0x03));  // Page Address Setup
    LCD1_CMD(0x00 | (0 & 0x7F));  // Column Address
    for (c = 0; c < 62; c++) {
      LCD1_DAT_WRITE(0);
    }

    LCD2_CMD(0xB8 | (p & 0x03));  // Page Address Setup
    LCD2_CMD(0x00 | (0 & 0x7F));  // Column Address
    for (c = 0; c < 62; c++) {
      LCD2_DAT_WRITE(0);
    }
  }
}

void sg12232c_set_pixel(int x, int y, int reverse)
{
  volatile uint8 dat;
  int p, c;

  if (x <= 60) {
    p = y / 8;
    c = x;
    LCD1_CMD(0xB8 | (p & 0x03));  // Page Address Setup
    LCD1_CMD(0x00 | (c & 0x7F));  // Column Address
    LCD1_CMD(0xE0);
    dat = LCD1_DAT_READ();    // Dummy Read
    dat = LCD1_DAT_READ();    // Real Read
    if (reverse) {
      dat |= (1 << (y % 8));
    } else {
      dat &= ~(1 << (y % 8));
    }
    LCD1_DAT_WRITE(dat);
    LCD1_CMD(0xEE);
  } else {
    p = y / 8;
    c = x - 61;
    LCD2_CMD(0xB8 | (p & 0x03));  // Page Address Setup
    LCD2_CMD(0x00 | (c & 0x7F));  // Column Address
    LCD2_CMD(0xE0);
    dat = LCD2_DAT_READ();    // Dummy Read
    dat = LCD2_DAT_READ();    // Real Read
    if (reverse) {
      dat |= (1 << (y % 8));
    } else {
      dat &= ~(1 << (y % 8));
    }
    LCD2_DAT_WRITE(dat);
    LCD2_CMD(0xEE);
  }
}

void sg12232c_draw_line(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 reverse)
{
  int x;
  /*
   * Bresenham's line algorithm
   */
  uint8 steep = abs(y2 - y1) > abs(x2 - x1);
  if (steep) {
    swap(x1, y1);
    swap(x2, y2);
  }
  if (x1 > x2) {
    swap(x1, x2);
    swap(y1, y2);
  }
  int deltax = x2 - x1;
  int deltay = abs(y2 - y1);
  int error = deltax / 2;
  int ystep;
  int y = y1;
  if (y1 < y2) {
    ystep = 1;
  } else {
    ystep = -1;
  }
  for (x = x1; x <= x2; x++) {
    if (steep) {
      if (reverse) {
        sg12232c_set_pixel(y, x, 0);
      } else {
        sg12232c_set_pixel(y, x, 1);
      }
    } else {
      if (reverse) {
        sg12232c_set_pixel(x, y, 0);
      } else {
        sg12232c_set_pixel(x, y, 1);
      }
    }
    error = error - deltay;
    if (error < 0) {
      y = y + ystep;
      error = error + deltax;
    }
  }
}

void sg12232c_draw_box(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 reverse)
{
  int x, y;
  for (x = x1; x <= x2; x++) {
    if (reverse) {
      sg12232c_set_pixel(x, y1, 0);
      sg12232c_set_pixel(x, y2, 0);
    } else {
      sg12232c_set_pixel(x, y1, 1);
      sg12232c_set_pixel(x, y2, 1);
    }
  }
  for (y = y1; y <= y2; y++) {
    if (reverse) {
      sg12232c_set_pixel(x1, y, 0);
      sg12232c_set_pixel(x2, y, 0);
    } else {
      sg12232c_set_pixel(x1, y, 1);
      sg12232c_set_pixel(x2, y, 1);
    }
  }
}

void sg12232c_fill_box(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 reverse)
{
  int x, y;
  for (x = x1; x <= x2; x++) {
    for (y = y1; y <= y2; y++) {
      if (reverse) {
        sg12232c_set_pixel(x, y, 0);
      } else {
        sg12232c_set_pixel(x, y, 1);
      }
    }
  }
}

void sg12232c_draw_string(uint8 x, uint8 y, char *str, uint8 reverse)
{
  char *p = str;
  int cnt = 0;
  while (*p) {
    sg12232c_draw_char(x + (FONT_X * cnt), y, *p, reverse);
    p++;
    cnt++;
  }
}

void sg12232c_draw_char(uint8 x, uint8 y, char c, uint8 reverse)
{
  int i, j;
  if ((FONT_MIN_CODE <= c) &&(c <= FONT_MAX_CODE)) {
    int aofs = (c - FONT_MIN_CODE) * FONT_X;
    for (i = 0; i < FONT_X; i++) {
      uint8 pat = font5x7_data[aofs + i];
      for (j = 0; j < FONT_Y; j++) {
        if (pat & (1 << j)) {
          if (reverse) {
            sg12232c_set_pixel(x + i, y + j, 0);
          } else {
            sg12232c_set_pixel(x + i, y + j, 1);
          }
        } else {
          if (reverse) {
            sg12232c_set_pixel(x + i, y + j, 1);
          } else {
            sg12232c_set_pixel(x + i, y + j, 0);
          }
        }
      }
    }
  } else {
    for (i = 0; i < FONT_X; i++) {
      uint8 pat = (i % 2) ? 0x55 : 0xAA;
      for (j = 0; j < FONT_Y; j++) {
        if (pat & (1 << j)) {
          if (reverse) {
            sg12232c_set_pixel(x + i, y + j, 0);
          } else {
            sg12232c_set_pixel(x + i, y + j, 1);
          }
        } else {
          if (reverse) {
            sg12232c_set_pixel(x + i, y + j, 1);
          } else {
            sg12232c_set_pixel(x + i, y + j, 0);
          }
        }
      }
    }
  }
}

void sg12232c_draw_checkbox(
    uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 state, uint8 reverse)
{
  sg12232c_draw_box(x1, y1, x2, y2, reverse);
  if (state) {
    sg12232c_draw_line(x1, y1, x2, y2, reverse);
    sg12232c_draw_line(x1, y2, x2, y1, reverse);
  }
}

void sg12232c_draw_progressbar(
    uint16 x1, uint16 y1, uint16 x2, uint16 y2,
    int min, int max, int value, uint8 reverse)
{
  sg12232c_draw_box(x1, y1, x2, y2, reverse);
  if ((value < min) || (max < value)) {
    return;
  }
  int tmp_max = max - min;
  int tmp_val = value - min;
  int pix = ((x2 - x1) * tmp_val) / tmp_max;
  sg12232c_fill_box(x1 + 1, y1 + 1, x1 + pix - 1, y2 - 1, reverse);
  if (pix > 0) {
      sg12232c_fill_box(x1 + pix, y1 + 1, x2 - 1, y2 - 1, !reverse);
  }
}

