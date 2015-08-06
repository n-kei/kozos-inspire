#ifndef _LCD_H_INCLUDED_
#define _LCD_H_INCLUDED_

#include "defines.h"

void sg12232c_init(void);
void sg12232c_clear(void);
void sg12232c_set_pixel(int x, int y, int reverse);
void sg12232c_draw_line(uint16 x1, uint16 y1, uint16 x2, uint16 y2,
    uint8 reverse);
void sg12232c_draw_box(uint16 x1, uint16 y1, uint16 x2, uint16 y2,
    uint8 reverse);
void sg12232c_fill_box(uint16 x1, uint16 y1, uint16 x2, uint16 y2,
    uint8 reverse);
void sg12232c_draw_string(uint8 x, uint8 y, char *str, uint8 reverse);
void sg12232c_draw_char(uint8 x, uint8 y, char c, uint8 reverse);
void sg12232c_draw_checkbox(uint16 x1, uint16 y1, uint16 x2, uint16 y2,
    uint8 state, uint8 reverse);
void sg12232c_draw_progressbar(uint16 x1, uint16 y1, uint16 x2, uint16 y2,
    int min, int max, int value, uint8 reverse);

#endif

