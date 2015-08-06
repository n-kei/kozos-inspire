
#include "boot.h"
#include "defines.h"
#include "pff.h"
#include "sg12232c.h"
#include "led.h"
#include "lib.h"
#include "xmodem.h"
#include "elf.h"

void boot_from_sdc(const char *filename)
{
  static unsigned char *loadbuf = NULL;
  char *entry_point;
  void (*f)(void);
  extern int buffer_start; /* リンカ・スクリプトで定義されているバッファ */

  FATFS fatfs;
  WORD br, i;
  BYTE buff[64];
  int rc;

  /*
   * SDカードをマウント。
   */
  rc = pf_mount(&fatfs);
  if (rc) {
    return;
  }

  /*
   * ファイルを開く。
   */
  rc = pf_open(filename);
  if (rc) {
    return;
  }

  sg12232c_draw_string(2, 10, "Booting from SDC.", 0);

  /*
   * SDカード上のOSイメージをメモリ上に読み込み。
   */
  loadbuf = (char *)(&buffer_start);
  for (;;) {
    rc = pf_read(buff, sizeof(buff), &br);
    if (rc || !br) {
      break;
    }
    for (i = 0; i < br; i++) {
      *loadbuf = buff[i];
      loadbuf++;
    }
    sg12232c_draw_progressbar(5, 20, 121 - 5, 25, 0, 100, fatfs.fptr * 100 / fatfs.fsize, 0);
    led_toggle(Led1);
    led_toggle(Led2);
  }
  if (rc) {
    sg12232c_draw_string(2, 10, "File read error.", 0);
    return;
  }

  /*
   * メモリ上に展開(ロード)
   */
  loadbuf = (char *)(&buffer_start);
  entry_point = elf_load(loadbuf);

  /*
   * 実行。
   */
  if (!entry_point) {
    sg12232c_draw_string(2, 10, "Run error.", 0);
  } else {
    sg12232c_clear();
    led_write(Led1, LedOff);
    led_write(Led2, LedOff);
    led_write(LedG, LedOff);
    led_write(LedR, LedOff);
    f = (void (*)(void))entry_point;
    f();
  }
}

static void wait()
{
  volatile long i;
  for (i = 0; i < 300000; i++)
    ;
}

/* メモリの16進ダンプ出力 */
static int dump(char *buf, long size)
{
  long i;

  if (size < 0) {
    puts("no data.\n");
    return -1;
  }
  for (i = 0; i < size; i++) {
    putxval(buf[i], 2);
    if ((i & 0xf) == 15) {
      puts("\n");
    } else {
      if ((i & 0xf) == 7) puts(" ");
      puts(" ");
    }
  }
  puts("\n");

  return 0;
}

void boot_from_ser(void)
{
  static char buf[16];
  static long size = -1;
  static unsigned char *loadbuf = NULL;
  char *entry_point;
  void (*f)(void);
  extern int buffer_start; /* リンカ・スクリプトで定義されているバッファ */

  sg12232c_draw_string(2, 10, "Waiting a boot image.", 0);

  while (1) {
    puts("kzload> "); /* プロンプト表示 */
    gets(buf); /* シリアルからのコマンド受信 */

    if (!strcmp(buf, "load")) { /* XMODEMでのファイルのダウンロード */
      sg12232c_draw_string(2, 10, "Receiving a boot image.", 0);
      loadbuf = (char *)(&buffer_start);
      size = xmodem_recv(loadbuf);
      wait(); /* 転送アプリが終了し端末アプリに制御が戻るまで待ち合わせる */
      if (size < 0) {
        puts("\nXMODEM receive error!\n");
        sg12232c_draw_string(2, 10, "Receive error occurred.", 0);
      } else {
        puts("\nXMODEM receive succeeded.\n");
        sg12232c_draw_string(2, 10, "Receive succeeded.     ", 0);
      }
    } else if (!strcmp(buf, "dump")) { /* メモリの16進ダンプ出力 */
      puts("size: ");
      putxval(size, 0);
      puts("\n");
      dump(loadbuf, size);
    } else if (!strcmp(buf, "run")) { /* ELF形式ファイルの実行 */
      entry_point = elf_load(loadbuf); /* メモリ上に展開(ロード) */
      if (!entry_point) {
        puts("run error!\n");
      } else {
        puts("starting from entry point: ");
        putxval((unsigned long)entry_point, 0);
        puts("\n");
        f = (void (*)(void))entry_point;
        f(); /* ここで，ロードしたプログラムに処理を渡す */
        /* ここには返ってこない */
      }
    }
  }
}

