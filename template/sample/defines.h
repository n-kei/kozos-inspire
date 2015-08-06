#ifndef _DEFINES_H_INCLUDED_
#define _DEFINES_H_INCLUDED_

#define NULL ((void *)0)
#define SERIAL_DEFAULT_DEVICE 1
#define TIMER_DEFAULT_DEVICE  1

typedef char  int8;
typedef short int16;
typedef long  int32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

typedef uint32 kz_thread_id_t;
typedef int (*kz_func_t)(int argc, char *argv[]);
typedef void (*kz_handler_t)(void);

typedef enum {
  MSGBOX_ID_CONSINPUT = 0,
  MSGBOX_ID_CONSOUTPUT,
  MSGBOX_ID_TIMDRIVE,
  MSGBOX_ID_TIMEXPIRE,
  MSGBOX_ID_AUDIO,
  MSGBOX_ID_DISPLAY,
  MSGBOX_ID_MENU,
  MSGBOX_ID_NUM
} kz_msgbox_id_t;

#endif
