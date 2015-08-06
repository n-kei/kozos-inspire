#include "led.h"
#include "defines.h"
#include "portconf.h"

int led_init(void)
{
  volatile uint8 mask = PORTCONF_PABIT_LED1 | PORTCONF_PABIT_LED2 | PORTCONF_PABIT_LEDG | PORTCONF_PABIT_LEDR;

  /*
   * �ݡ��ȥǥ��쥯���������ꤹ�����˥ǡ����쥸�������������롣
   * �������ʤΤǡ�����ͤΥ�����Ƚ��Ϥˤ����������������֤Ȥʤ롣
   */
  *PORTCONF_PADR |= mask;

  /*
   * �ݡ���A�Υӥå�2,3,6,7�Ͻ��ϥݡ��ȤȤ������ꤹ�롣
   *
   * �ǡ����ǥ��쥯�����쥸������Write Only�ʤΤǡ�
   * ¾�ΥӥåȤ����꤬ɬ�פˤʤä������ǡ�
   * �ݡ��������������ޤȤ�ƴ�������褦��
   * ���餫���к���ɬ�פȤʤ������
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

