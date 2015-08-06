
#include "kozos.h"
#include "ipc_display.h"
#include "lib.h"

void ipc_display_led_write(int target, int state)
{
  char *p;
  p = kz_kmalloc(2);
  p[0] = state ? DISPLAY_CMD_LED_ON : DISPLAY_CMD_LED_OFF;
  p[1] = '0' + target;
  kz_send(MSGBOX_ID_DISPLAY, 2, p);
}

void ipc_display_led_toggle(int target)
{
  char *p;
  p = kz_kmalloc(2);
  p[0] = DISPLAY_CMD_LED_TOGGLE;
  p[1] = '0' + target;
  kz_send(MSGBOX_ID_DISPLAY, 2, p);
}

void ipc_display_clear(void)
{
  char *p;
  p = kz_kmalloc(1);
  p[0] = DISPLAY_CMD_LCD_CLEAR;
  kz_send(MSGBOX_ID_DISPLAY, 1, p);
}

void ipc_display_draw_box(int x1, int y1, int x2, int y2, int on)
{
  char *p;
  p = kz_kmalloc(6);
  p[0] = DISPLAY_CMD_LCD_DRAW_BOX;
  p[1] = x1;
  p[2] = y1;
  p[3] = x2;
  p[4] = y2;
  p[5] = !on;
  kz_send(MSGBOX_ID_DISPLAY, 6, p);
}

void ipc_display_draw_logo(int x, int y, int size)
{
  char *p;
  p = kz_kmalloc(4);
  p[0] = DISPLAY_CMD_LCD_DRAW_LOGO;
  p[1] = x;
  p[2] = y;
  p[3] = size;
  kz_send(MSGBOX_ID_DISPLAY, 4, p);
}

void ipc_display_draw_text(int x, int y, char *str)
{
  char *p;
  int len;
  len = strlen(str);
  p = kz_kmalloc(3 + len + 1);
  p[0] = DISPLAY_CMD_LCD_DRAW_TEXT;
  p[1] = x;
  p[2] = y;
  memcpy(&p[3], str, len);
  p[3 + len] = '\0';
  kz_send(MSGBOX_ID_DISPLAY, 3 + len + 1, p);
}

void ipc_display_draw_progressbar(
        int x1, int y1, int x2, int y2,
        int min, int max, int value)
{
  char *p;
  p = kz_kmalloc(8);
  p[0] = DISPLAY_CMD_LCD_DRAW_PBAR;
  p[1] = x1;
  p[2] = y1;
  p[3] = x2;
  p[4] = y2;
  p[5] = min;
  p[6] = max;
  p[7] = value;
  kz_send(MSGBOX_ID_DISPLAY, 8, p);
}

