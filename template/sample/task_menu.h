
#ifndef _TASK_MENU_H_
#define _TASK_MENU_H_

#define AUDIO_CONTROL_NONE  0x00
#define AUDIO_CONTROL_REW   0x01
#define AUDIO_CONTROL_FWD   0x02

int menu_get_audio_control(int *control);
int menu_get_audio_info(int *volume);

int task_menu(int argc, char *argv[]);

#endif

