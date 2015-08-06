#include "kozos.h"
#include "lib.h"
#include "ipc_menu.h"

int ipc_menu_set_filename(const char *filename)
{
  int len = strlen(filename);
  char *p = kz_kmalloc(1 + len + 1);
  p[0] = MENU_CMD_FILENAME;
  strcpy(&p[1], filename);
  p[1 + len] = '\0';
  kz_send(MSGBOX_ID_MENU, 1 + len + 1, p);
  return 0;
}

int ipc_menu_set_location(int location)
{
  char *p = kz_kmalloc(2);
  p[0] = MENU_CMD_LOCATION;
  p[1] = location;
  kz_send(MSGBOX_ID_MENU, 2, p);
  return 0;
}

int ipc_menu_rotary_from_isr(int left, int right)
{
  char *p = kx_kmalloc(4);
  p[0] = MENU_CMD_ROTARY;
  p[1] = left  ? 1 : 0;
  p[2] = right ? 1 : 0;
  p[3] = 0;
  kx_send(MSGBOX_ID_MENU, 4, p);
  return 0;
}

int ipc_menu_switch_from_isr(int sw1, int sw2, int swr)
{
  char *p = kx_kmalloc(4);
  p[0] = MENU_CMD_SWITCH;
  p[1] = sw1;
  p[2] = sw2;
  p[3] = swr;
  kx_send(MSGBOX_ID_MENU, 4, p);
  return 0;
}

int ipc_menu_remote_from_isr(char *signal, int siz)
{
  char *p = kx_kmalloc(8);
  p[0] = MENU_CMD_REMOTE;
  p[1] = 0;
  p[2] = 0;
  p[3] = 0;
  p[4] = signal[0];
  p[5] = signal[1];
  p[6] = signal[2];
  p[7] = signal[3];
  kx_send(MSGBOX_ID_MENU, 8, p);
  return 0;
}

