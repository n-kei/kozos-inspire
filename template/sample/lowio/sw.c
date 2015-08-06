
#include "sw.h"
#include "portconf.h"

int sw_init(void)
{
  return 0;
}

uint8 sw_read(sw_target_t target)
{
  uint8 c = 0;
  switch (target) {
    case Sw1:
      c = (*PORTCONF_P7DR & PORTCONF_P7BIT_SW1) ? 0 : 1;
      break;
    case Sw2:
      c = (*PORTCONF_P7DR & PORTCONF_P7BIT_SW2) ? 0 : 1;
      break;
    case SwRe:
      c = (*PORTCONF_PADR & PORTCONF_PABIT_SWRE) ? 0 : 1;
      break;
  }
  return c;
}

