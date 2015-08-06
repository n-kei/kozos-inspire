
#include "task_display.h"
#include "ipc_display.h"
#include "sg12232c.h"
#include "kozos.h"
#include "lib.h"
#include "led.h"
#include "ntl.h"
#include "ntlusr.h"

static void draw_logo(const int ofsx, const int ofsy, const int size)
{
  static const uint8 logo_40x32[] = {
      0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,
      0x00,0x1f,0xfc,0x00,0x00,
      0x00,0x1f,0xff,0xc0,0x00,
      0x00,0x1f,0xff,0xf0,0x00,
      0x00,0x0f,0x7f,0xfc,0x00,
      0x00,0x0f,0x7f,0xff,0x00,
      0x00,0x0f,0x7f,0xff,0xc0,
      0x00,0x0f,0x7f,0xff,0xe0,
      0x00,0x07,0x3f,0xff,0xf0,
      0x00,0x07,0x9f,0xff,0xfc,
      0x00,0x07,0xc1,0xff,0xfe,
      0x3f,0xff,0xff,0xff,0xff,
      0x3f,0xff,0xff,0xff,0xff,
      0x1f,0xff,0xff,0xff,0xff,
      0x1f,0xff,0xff,0xff,0xff,
      0x1f,0xff,0xfc,0xff,0xff,
      0x1f,0xff,0xf0,0x3f,0xff,
      0x1f,0xff,0xf0,0x07,0xff,
      0x1f,0xff,0xe0,0x41,0xff,
      0x0f,0xff,0xe0,0x21,0xff,
      0x0f,0xff,0xe2,0x13,0xff,
      0x07,0xff,0xf1,0x07,0xff,
      0x07,0xff,0xf8,0x8f,0xff,
      0x03,0xff,0xf8,0x1f,0xff,
      0x03,0xff,0xfc,0x3f,0xff,
      0x01,0xff,0xfc,0x7f,0xff,
      0x00,0xff,0xfe,0xff,0xff,
      0x00,0xff,0xff,0xff,0xff,
      0x00,0x7f,0xff,0xff,0xff,
      0x00,0x3f,0xff,0xff,0xff,
      0x00,0x1f,0xff,0xff,0xff,
  };
  static const uint8 logo_30x24[] = {
      0x00,0x00,0x00,0x00,
      0x00,0xfe,0x00,0x00,
      0x00,0xff,0xe0,0x00,
      0x00,0x7f,0xf8,0x00,
      0x00,0x77,0xff,0x00,
      0x00,0x77,0xff,0x80,
      0x00,0x77,0xff,0xe0,
      0x00,0x73,0xff,0xf0,
      0x00,0x38,0x7f,0xf8,
      0x3f,0xff,0xff,0xfc,
      0x3f,0xff,0xff,0xfc,
      0x3f,0xff,0xff,0xfc,
      0x3f,0xff,0x1f,0xfc,
      0x3f,0xfe,0x07,0xfc,
      0x1f,0xfe,0x23,0xfc,
      0x1f,0xfc,0x11,0xfc,
      0x1f,0xfe,0x8b,0xfc,
      0x0f,0xfe,0x47,0xfc,
      0x0f,0xff,0x2f,0xfc,
      0x07,0xff,0x1f,0xfc,
      0x03,0xff,0xbf,0xfc,
      0x03,0xff,0xff,0xfc,
      0x01,0xff,0xff,0xfc,
      0x00,0xff,0xff,0xfc,
  };
  static const uint8 logo_20x16[] = {
      0x00,0x00,0x00,
      0x03,0xf0,0x00,
      0x03,0xfe,0x00,
      0x03,0x7f,0x00,
      0x03,0x7f,0xc0,
      0x03,0x8f,0xe0,
      0x7f,0xff,0xf0,
      0x7f,0xff,0xf0,
      0x7f,0xc7,0xf0,
      0x3f,0x89,0xf0,
      0x3f,0xa5,0xf0,
      0x3f,0x93,0xf0,
      0x1f,0xc7,0xf0,
      0x0f,0xef,0xf0,
      0x0f,0xff,0xf0,
      0x07,0xff,0xf0,
  };
  int x, y;
  uint8 c = 0;
  switch (size) {
    case 0:
      for (y = 0; y < 16; y++) {
        for (x = 0; x < 20; x++) {
          if ((x % 8) == 0) {
            c = logo_20x16[(y * 3) + (x / 8)];
          }
          int pix = (c & (1 << (7 - (x % 8)))) ? 1 : 0;
          sg12232c_set_pixel(ofsx + x, ofsy + y, pix);
        }
      }
      break;
    case 1:
      for (y = 0; y < 24; y++) {
        for (x = 0; x < 30; x++) {
          if ((x % 8) == 0) {
            c = logo_30x24[(y * 4) + (x / 8)];
          }
          int pix = (c & (1 << (7 - (x % 8)))) ? 1 : 0;
          sg12232c_set_pixel(ofsx + x, ofsy + y, pix);
        }
      }
      break;
    case 2:
      for (y = 0; y < 32; y++) {
        for (x = 0; x < 40; x++) {
          if ((x % 8) == 0) {
            c = logo_40x32[(y * 5) + (x / 8)];
          }
          int pix = (c & (1 << (7 - (x % 8)))) ? 1 : 0;
          sg12232c_set_pixel(ofsx + x, ofsy + y, pix);
        }
      }
      break;
  }
}

/* $B%9%l%C%I$+$i$NMW5a$r=hM}$9$k(B */
static int display_cmdproc(char *p)
{
  int cmd = p[0];
  switch (cmd) {
  case DISPLAY_CMD_LCD_CLEAR:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_CLEAR);
    sg12232c_clear();
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_CLEAR);
    break;
  case DISPLAY_CMD_LCD_DRAW_BOX:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWBOX);
    sg12232c_draw_box(p[1], p[2], p[3], p[4], p[5]);
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWBOX);
    break;
  case DISPLAY_CMD_LCD_DRAW_LOGO:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWLOGO);
    draw_logo(p[1], p[2], p[3]);
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWLOGO);
    break;
  case DISPLAY_CMD_LCD_DRAW_TEXT:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWTEXT);
    sg12232c_draw_string(p[1], p[2], &p[3], 0);
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWTEXT);
    break;
  case DISPLAY_CMD_LCD_DRAW_PBAR:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWPROG);
    sg12232c_draw_progressbar(
            p[1], p[2], p[3], p[4], p[5], p[6], p[7], 0);
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_DRAWPROG);
    break;
  case DISPLAY_CMD_LED_ON:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_LEDON);
    led_write(p[1] - '0', LedOn);
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_LEDON);
    break;
  case DISPLAY_CMD_LED_OFF:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_LEDOFF);
    led_write(p[1] - '0', LedOff);
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_LEDOFF);
    break;
  case DISPLAY_CMD_LED_TOGGLE:
    NTLEVT_START(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_LEDTOGGLE);
    led_toggle(p[1] - '0');
    NTLEVT_END(NTLUSR_TRACK_DISPLAY, NTLUSR_EVENT_DISPLAY_LEDTOGGLE);
    break;
  default:
    break;
  }
  kz_kmfree(p);

  return 0;
}

int task_display(int argc, char *argv[])
{
  int size;
  char *p;

  while (1) {
    kz_recv(MSGBOX_ID_DISPLAY, &size, &p);
    display_cmdproc(p);
  }

  return 0;
}

