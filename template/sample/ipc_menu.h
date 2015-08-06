
#ifndef IPC_MENU_H
#define IPC_MENU_H

#define MENU_CMD_FILENAME   'F'
#define MENU_CMD_LOCATION   'L'
#define MENU_CMD_ROTARY     'R'
#define MENU_CMD_SWITCH     'S'
#define MENU_CMD_REMOTE     'I'

int ipc_menu_set_filename(const char *filename);
int ipc_menu_set_location(int location);
int ipc_menu_rotary_from_isr(int left, int right);
int ipc_menu_switch_from_isr(int sw1, int sw2, int swr);
int ipc_menu_remote_from_isr(char *signal, int siz);

#endif

