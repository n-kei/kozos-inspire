#include "defines.h"
#include "kozos.h"
#include "interrupt.h"
#include "lib.h"
#include "driver_console.h"
#include "driver_timer.h"
#include "task_audio.h"
#include "task_display.h"
#include "task_menu.h"
#include "task_input.h"
#include "task_command.h"
#include "task_fileio.h"

kz_thread_id_t tskid_audio;
kz_thread_id_t tskid_display;
kz_thread_id_t tskid_fileio;
kz_thread_id_t tskid_menu;
kz_thread_id_t tskid_input;
kz_thread_id_t tskid_command;

/* システム・タスクとユーザ・タスクの起動 */
static int start_threads(int argc, char *argv[])
{
  /*
   * Drivers
   */
  kz_run(driver_console,    "dConsole",  1, 0x200, 0, NULL);
  kz_run(driver_timer,      "dTimer",    2, 0x200, 0, NULL);

  /*
   * Tasks
   */
  tskid_audio   = kz_run(task_audio,    "tAudio",    3, 0x800, 0, NULL);
  tskid_display = kz_run(task_display,  "tDisplay",  4, 0x800, 0, NULL);
  tskid_menu    = kz_run(task_menu,     "tMenu",     5, 0x800, 0, NULL);
  tskid_input   = kz_run(task_input,    "tInput",    6, 0x800, 0, NULL);
  tskid_command = kz_run(task_command,  "tCommand",  7, 0x800, 0, NULL);
  tskid_fileio  = kz_run(task_fileio,   "tFileIO",   8, 0x800, 0, NULL);

  kz_chpri(15); /* 優先順位を下げて，アイドルスレッドに移行する */
  INTR_ENABLE; /* 割込み有効にする */
  while (1) {
    asm volatile ("sleep"); /* 省電力モードに移行 */
  }

  return 0;
}

int main(void)
{
  INTR_DISABLE; /* 割込み無効にする */

  puts("kozos boot succeed!\n");

  /* OSの動作開始 */
  kz_start(start_threads, "idle", 0, 0x100, 0, NULL);
  /* ここには戻ってこない */

  return 0;
}

