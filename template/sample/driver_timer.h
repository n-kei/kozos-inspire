#ifndef _TIMERDRV_H_INCLUDED_
#define _TIMERDRV_H_INCLUDED_

#define TIMERDRV_DEVICE_NUM 1

void timerdrv_start(int msec);
void timerdrv_wait();

struct timerreq {
  kz_msgbox_id_t id; /* ��������λ���Υ�å����������� */
  int msec;
};

int driver_timer(int argc, char *argv[]);

#endif
