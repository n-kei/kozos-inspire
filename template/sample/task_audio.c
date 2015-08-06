
#include "task_audio.h"
#include "vs1011e.h"
#include "kozos.h"
#include "ipc_audio.h"
#include "ntl.h"
#include "ntlusr.h"

static int waitfunc(void)
{
    kz_wait();
    return 1;
}

static int audio_cmdproc(char *p)
{
  int cmd = p[0];
  switch (cmd) {
  case AUDIO_CMD_CANCEL:
    NTLEVT_START(NTLUSR_TRACK_AUDIO, NTLUSR_EVENT_AUDIO_CANCEL);
      vs1011e_cancel_data();
    NTLEVT_END(NTLUSR_TRACK_AUDIO, NTLUSR_EVENT_AUDIO_CANCEL);
      break;
  case AUDIO_CMD_PLAY:
    NTLEVT_START(NTLUSR_TRACK_AUDIO, NTLUSR_EVENT_AUDIO_PLAY);
    vs1011e_play_with_data(
        &p[8],
        ((unsigned char)p[4] << 8) | ((unsigned char)p[5] << 0),
        waitfunc);
    NTLEVT_END(NTLUSR_TRACK_AUDIO, NTLUSR_EVENT_AUDIO_PLAY);
    break;
  case AUDIO_CMD_VOLUME:
    NTLEVT_START(NTLUSR_TRACK_AUDIO, NTLUSR_EVENT_AUDIO_VOLUME);
    vs1011e_volume_write(p[2], p[3]);
    NTLEVT_END(NTLUSR_TRACK_AUDIO, NTLUSR_EVENT_AUDIO_VOLUME);
    break;
  default:
    break;
  }
  kz_kmfree(p);

  return 0;
}

int task_audio(int argc, char *argv[])
{
  int size;
  char *p;

  while (1) {
    kz_recv(MSGBOX_ID_AUDIO, &size, &p);
    audio_cmdproc(p);
  }

  return 0;
}

