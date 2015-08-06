
#include "pff.h"
#include "lib.h"
#include "task_fileio.h"
#include "task_menu.h"
#include "ipc_menu.h"
#include "ipc_audio.h"
#include "ntl.h"
#include "ntlusr.h"

static FATFS fatfs;
static DIR dir;
static FILINFO filinfo;

static int readfunc(void *buf, int siz)
{
    WORD cnt;
    NTLEVT_START(NTLUSR_TRACK_FILEIO, NTLUSR_EVENT_FILEIO_READING);
    pf_read(buf, siz, &cnt);
    NTLEVT_END(NTLUSR_TRACK_FILEIO, NTLUSR_EVENT_FILEIO_READING);
    return cnt;
}

static int play(const char *filename)
{
    FRESULT r = pf_open(filename);
    if (r != FR_OK) {
        return 1;
    }
    static int vol_prev = 0, vol_curr = 0;
    int divcnt = 0;
    int control = 0;

    ipc_menu_set_filename(filinfo.fname);
    ipc_menu_set_location(fatfs.fptr * 100 / fatfs.fsize);

    while (ipc_audio_play(readfunc)) {
        NTLEVT_START(NTLUSR_TRACK_FILEIO, NTLUSR_EVENT_FILEIO_OTHERS);
        switch ((divcnt++) % 4) {
            case 0:
                /*
                 * 早送りや巻き戻し
                 */
                menu_get_audio_control(&control);
                if (control != 0) {
                    switch (control) {
                        case AUDIO_CONTROL_FWD:
                            if (fatfs.fptr + 8192 < fatfs.fsize) {
                                pf_lseek(fatfs.fptr + 8192);
                            }
                            ipc_audio_cancel();
                            break;
                        case AUDIO_CONTROL_REW:
                            if (16384 < fatfs.fptr) {
                                pf_lseek(fatfs.fptr - 16384);
                            }
                            ipc_audio_cancel();
                            break;
                    }
                }
                break;
            case 1:
                /*
                 * オーディオ情報の取得
                 */
                menu_get_audio_info(&vol_curr);
                if (vol_curr != vol_prev) {
                    ipc_audio_volume(vol_curr, vol_curr);
                }
                vol_prev = vol_curr;
                break;
            case 2:
                /*
                 * 位置の設定
                 */
                ipc_menu_set_location(fatfs.fptr * 100 / fatfs.fsize);
                break;
        }
        NTLEVT_END(NTLUSR_TRACK_FILEIO, NTLUSR_EVENT_FILEIO_OTHERS);
    }
    return 0;
}

static int is_music_file(const char *filename)
{
    int len = strlen(filename);
    if (len < 4) {
        return 0;
    }
    if (strcmp(filename + len - 4, ".MP3") == 0) {
        return 1;
    }
    if (strcmp(filename + len - 4, ".WAV") == 0) {
        return 1;
    }
    return 0;
}

int task_fileio(int argc, char *argv[])
{
  while (1) {
      ipc_menu_set_filename("Mounting...");
      if (pf_mount(&fatfs)) {
          continue;
      }
      while (1) {
          ipc_menu_set_filename("Directory");
          if (pf_opendir(&dir, "")) {
              break;
          }
          while (!pf_readdir(&dir, &filinfo) && filinfo.fname[0]) {
              ipc_menu_set_filename(filinfo.fname);
              if (!(filinfo.fattrib & (AM_DIR | AM_HID))) {
                  if (is_music_file(filinfo.fname)) {
                      if (play(filinfo.fname)) {
                          break;
                      }
                  }
              }
          }
      }
  }

  return 0;
}

