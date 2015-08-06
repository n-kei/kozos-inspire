#ifndef IPC_AUDIO_H
#define IPC_AUDIO_H

#define AUDIO_CMD_CANCEL    'C'
#define AUDIO_CMD_PLAY      'P'
#define AUDIO_CMD_VOLUME    'V'

int ipc_audio_cancel(void);
int ipc_audio_play(int (*readfunc)(void *buf, int siz));
int ipc_audio_volume(const int left, const int right);

#endif

