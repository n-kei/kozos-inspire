
#include "init.h"
#include "lib.h"
#include "interrupt.h"
#include "defines.h"
#include "banner.h"
#include "serial.h"
#include "dram.h"
#include "led.h"
#include "re.h"
#include "sw.h"
#include "sg12232c.h"
#include "spi.h"
#include "vs1011e.h"

int init_system(void)
{
  /* 以下はリンカ・スクリプトで定義してあるシンボル */
  extern int erodata, data_start, edata, bss_start, ebss;

  /*
   * データ領域とBSS領域を初期化する．この処理以降でないと，
   * グローバル変数が初期化されていないので注意．
   */
  memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
  memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

  /* ソフトウエア・割り込みベクタを初期化する */
  softvec_init();

  /* シリアルの初期化 */
  serial_init(SERIAL_DEFAULT_DEVICE);

  banner();

  return 0;
}

int init_components(void)
{
  /* DRAMの初期化 */
  puts("Init : DRAM...");
  dram_init();
  puts("Done.\n");

  /* LEDの初期化 */
  puts("Init : LED...");
  led_init();
  puts("Done.\n");

  /* ロータリーエンコーダーの初期化 */
  puts("Init : Rotary Encoder...");
  re_init();
  puts("Done.\n");

  /* スイッチの初期化 */
  puts("Init : Switch...");
  sw_init();
  puts("Done.\n");

  /* LCDの初期化 */
  puts("Init : LCD...");
  sg12232c_init();
  sg12232c_clear();
  sg12232c_draw_box(0, 0, 121, 31, 0);
  sg12232c_draw_string(2, 2, "KOZOS EXPBRD #00", 0);
  puts("Done.\n");

  /* SPI Bus initializing. */
  puts("Init : SPI Bus...");
  spi_init();
  puts("Done.\n");

  /* VS1011e */
  puts("Init : VS1011E...");
  vs1011e_init();
  vs1011e_volume_write(0x40, 0x40);
  puts("Done.\n");

  puts("Init : All Done.\n");

  return 0;
}

