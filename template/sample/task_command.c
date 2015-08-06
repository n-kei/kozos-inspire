
#include "defines.h"
#include "kozos.h"
#include "lib.h"
#include "driver_console.h"
#include "ntshell.h"

int func_read(char *buf, int cnt)
{
  int i;
  for (i = 0; i < cnt; i++) {
    char *p;
    int size;
    /* コンソールからの受信文字列を受け取る */
    kz_recv(MSGBOX_ID_CONSINPUT, &size, &p);
    buf[i] = p[0];
    kz_kmfree(p);
  }
  return 0;
}

int func_write(const char *buf, int cnt)
{
  int i;
  for (i = 0; i < cnt; i++) {
    putc(buf[i]);
  }
  return 0;
}

int func_callback(const char *text, void *extobj)
{
  if (strlen(text) > 0) {
    puts((unsigned char *)text);
    puts("\n");
  }
  return 0;
}

int task_command(int argc, char *argv[])
{
  ntshell_t ntshell;

  console_use(SERIAL_DEFAULT_DEVICE);

  while (1) {
    ntshell_execute(&ntshell, func_read, func_write, func_callback, NULL);
  }

  return 0;
}

