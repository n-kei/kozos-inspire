#include "led.h"
#include "defines.h"
#include "portconf.h"

int led_init(void)
{
  volatile uint8 mask = PORTCONF_PABIT_LED1 | PORTCONF_PABIT_LED2 | PORTCONF_PABIT_LEDG | PORTCONF_PABIT_LEDR;

  /*
   * ポートディレクションを設定する前にデータレジスタを初期化する。
   * 負論理なので、初期値のゼロだと出力にした時点で点灯状態となる。
   */
  *PORTCONF_PADR |= mask;

  /*
   * ポートAのビット2,3,6,7は出力ポートとして設定する。
   *
   * データディレクションレジスタはWrite Onlyなので、
   * 他のビットの設定が必要になった時点で、
   * ポート入出力設定をまとめて管理するような
   * 何らかの対策が必要となるだろう。
   */
  *PORTCONF_PADDR = 0xCC;

  return 0;
}

int led_write(led_target_t target, led_state_t state)
{
  volatile uint8 mask = 0x00;

  switch (target) {
    case Led1:
      mask = PORTCONF_PABIT_LED1;
      break;
    case Led2:
      mask = PORTCONF_PABIT_LED2;
      break;
    case LedG:
      mask = PORTCONF_PABIT_LEDG;
      break;
    case LedR:
      mask = PORTCONF_PABIT_LEDR;
      break;
    default:
      return -1;
  }

  switch (state) {
    case LedOn:
      *PORTCONF_PADR &= ~mask;
      break;
    case LedOff:
      *PORTCONF_PADR |= mask;
      break;
    default:
      return -1;
  }

  return 0;
}

int led_toggle(led_target_t target)
{
  volatile uint8 mask = 0x00;

  switch (target) {
    case Led1:
      mask = PORTCONF_PABIT_LED1;
      break;
    case Led2:
      mask = PORTCONF_PABIT_LED2;
      break;
    case LedG:
      mask = PORTCONF_PABIT_LEDG;
      break;
    case LedR:
      mask = PORTCONF_PABIT_LEDR;
      break;
    default:
      return -1;
  }

  if (*PORTCONF_PADR & mask) {
    *PORTCONF_PADR &= ~mask;
  } else {
    *PORTCONF_PADR |= mask;
  }

  return 0;
}

