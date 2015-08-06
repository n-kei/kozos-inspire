#ifndef _CONSDRV_H_INCLUDED_
#define _CONSDRV_H_INCLUDED_

#define CONSDRV_DEVICE_NUM 1

void console_use(int index);
void console_write(char *str);

int driver_console(int argc, char *argv[]);

#endif
