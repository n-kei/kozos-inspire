
#include "lib.h"
#include "kozos.h"
#include "task_menu.h"
#include "ipc_menu.h"
#include "ipc_display.h"
#include "ntl.h"
#include "ntlusr.h"

#define IR_DEBUG_ENABLED    (0)

#define VOL_MAX 250
#define VOL_DEF 220
#define VOL_MIN 200

#define LED_LEFT() \
    do { \
      ipc_display_led_write(1, 0); \
      ipc_display_led_toggle(0); \
    } while (0)

#define LED_RIGHT() \
    do { \
      ipc_display_led_write(0, 0); \
      ipc_display_led_toggle(1); \
    } while (0)

#define LED_GREEN() \
    do { \
      ipc_display_led_toggle(2); \
    } while (0)

#define LED_RED() \
    do { \
      ipc_display_led_toggle(3); \
    } while (0)

#define DISP_VOLUME(N) \
    ipc_display_draw_progressbar(107, 3, 118, 7, VOL_MIN, VOL_MAX, N)

#define DISP_LOCATION(N) \
    ipc_display_draw_progressbar(24, 13, 83, 17, 0, 100, N)

static int _volume = VOL_DEF;
static int _control = 0;

int menu_get_audio_control(int *control)
{
    *control = _control;
    _control = 0;
    return 0;
}

int menu_get_audio_info(int *volume)
{
    *volume = _volume;
    return 0;
}

static int menu_cmdproc(char *p)
{
  int cmd = p[0];
  switch (cmd) {
  case MENU_CMD_FILENAME:
    NTLEVT_START(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_FILENAME);
    ipc_display_draw_text(24, 3, &p[1]);
    NTLEVT_END(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_FILENAME);
    break;
  case MENU_CMD_LOCATION:
    NTLEVT_START(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_LOCATION);
    DISP_LOCATION(p[1]);
    NTLEVT_END(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_LOCATION);
    break;
  case MENU_CMD_ROTARY:
    NTLEVT_START(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_ROTARY);
    if (p[1]) {
        if (VOL_MIN < _volume) {
            _volume--;
            LED_LEFT();
            DISP_VOLUME(_volume);
        }
    }
    if (p[2]) {
        if (_volume < VOL_MAX) {
            _volume++;
            LED_RIGHT();
            DISP_VOLUME(_volume);
        }
    }
    NTLEVT_END(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_ROTARY);
    break;
  case MENU_CMD_SWITCH:
    NTLEVT_START(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_SWITCH);
    if (p[1]) {
        LED_LEFT();
        _control = AUDIO_CONTROL_REW;
    }
    if (p[2]) {
        LED_RIGHT();
        _control = AUDIO_CONTROL_FWD;
    }
    if (p[3]) {
        LED_GREEN();
    }
    NTLEVT_END(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_SWITCH);
    break;
  case MENU_CMD_REMOTE:
    {
        NTLEVT_START(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_REMOTE);
        uint32 n =
            ((uint32)p[4] << 24) |
            ((uint32)p[5] << 16) |
            ((uint32)p[6] <<  8) |
            ((uint32)p[7] <<  0);
        /*
         * リモコンのコードは、メーカによって異なる。
         */
        switch (n) {
            case 0xaa550af5:
                if (_volume < VOL_MAX) {
                    _volume++;
                    LED_RIGHT();
                    DISP_VOLUME(_volume);
                }
                break;
            case 0xaa550bf4:
                if (VOL_MIN < _volume) {
                    _volume--;
                    LED_LEFT();
                    DISP_VOLUME(_volume);
                }
                break;
            case 0xaa5511ee:
                LED_LEFT();
                _control = AUDIO_CONTROL_REW;
                break;
            case 0xaa5510ef:
                LED_RIGHT();
                _control = AUDIO_CONTROL_FWD;
                break;
            default:
#if IR_DEBUG_ENABLED
                puts("Unknown: ");
                putxval(p[4], 2);
                putxval(p[5], 2);
                putxval(p[6], 2);
                putxval(p[7], 2);
                puts("\n");
#endif
                break;
        }
        NTLEVT_END(NTLUSR_TRACK_MENU, NTLUSR_EVENT_MENU_REMOTE);
    }
    break;
  default:
    break;
  }
  kz_kmfree(p);

  return 0;
}

int task_menu(int argc, char *argv[])
{
  ipc_display_clear();
  ipc_display_draw_box(0, 0, 121, 31, 1);
  ipc_display_draw_logo(2, 2, 0);
  DISP_VOLUME(_volume);

  while (1) {
      int size;
      char *p;
      kz_recv(MSGBOX_ID_MENU, &size, &p);
      menu_cmdproc(p);
  }

  return 0;
}

