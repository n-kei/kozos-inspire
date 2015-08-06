
#ifndef IPC_DISPLAY_H
#define IPC_DISPLAY_H

#define DISPLAY_CMD_LCD_CLEAR       'c' /* LCD$B$N>C5n(B */
#define DISPLAY_CMD_LCD_DRAW_BOX    'b' /* BOX$BIA2h%3%^%s%I(B */
#define DISPLAY_CMD_LCD_DRAW_LOGO   'l' /* LOGO$BIA2h%3%^%s%I(B */
#define DISPLAY_CMD_LCD_DRAW_TEXT   't' /* TEXT$BIA2h%3%^%s%I(B */
#define DISPLAY_CMD_LCD_DRAW_PBAR   'p' /* PBAR$BIA2h%3%^%s%I(B */
#define DISPLAY_CMD_LED_ON          '1' /* LED$B$NE@Et(B */
#define DISPLAY_CMD_LED_OFF         '0' /* LED$B$N>CEt(B */
#define DISPLAY_CMD_LED_TOGGLE      'a' /* LED$B$N%H%0%k(B */

void ipc_display_led_write(int target, int state);
void ipc_display_led_toggle(int target);
void ipc_display_clear(void);
void ipc_display_draw_box(int x1, int y1, int x2, int y2, int on);
void ipc_display_draw_logo(int x, int y, int size);
void ipc_display_draw_text(int x, int y, char *str);
void ipc_display_draw_progressbar(
        int x1, int y1, int x2, int y2,
        int min, int max, int value);

#endif

