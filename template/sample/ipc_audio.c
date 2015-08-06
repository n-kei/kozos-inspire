#include "kozos.h"
#include "ipc_audio.h"

int ipc_audio_cancel(void)
{
  char *p = kz_kmalloc(1);
  p[0] = AUDIO_CMD_CANCEL;
  kz_send(MSGBOX_ID_AUDIO, 1, p);
  return 0;
}

int ipc_audio_play(int (*readfunc)(void *buf, int siz))
{
  const int siz = 1024;
  char *p;
  int cnt;

  p = kz_kmalloc(8 + siz);
  cnt = readfunc((void *)&p[8], siz);

  p[0] = AUDIO_CMD_PLAY;
  p[1] = 0;
  p[2] = (siz >> 8) & 0xff;
  p[3] = (siz >> 0) & 0xff;
  p[4] = (cnt >> 8) & 0xff;
  p[5] = (cnt >> 0) & 0xff;
  p[6] = 0;
  p[7] = 0;
  kz_send(MSGBOX_ID_AUDIO, 8 + siz, p);

  return (siz == cnt) ? 1 : 0;
}

int ipc_audio_volume(const int left, const int right)
{
  char *p;
  p = kz_kmalloc(4);
  p[0] = AUDIO_CMD_VOLUME;
  p[1] = 0;
  p[2] = 255 - left;
  p[3] = 255 - right;
  if ((0 <= left) && (left <= 255) && (0 <= right) && (right <= 255)) {
      kz_send(MSGBOX_ID_AUDIO, 4, p);
      return 1;
  }
  return 0;
}

