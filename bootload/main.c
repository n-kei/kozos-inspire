#include "init.h"
#include "test.h"
#include "boot.h"
#include "interrupt.h"
#include "portconf.h"
#include "lib.h"
#include "sw.h"

int main(void)
{
  INTR_DISABLE; /* 割込み無効にする */

  init_system();
  init_components();
  test_execute();

  if (PORTCONF_SDC_DETECT() && !sw_read(Sw1)) {
      puts("Boot : SDC detected.\n");
      puts("Boot : Booting from SDC.\n");
      boot_from_sdc("kozos");
      puts("Boot : Boot from SDC failed.\n");
      puts("Boot : Going to serial boot mode.\n");
      boot_from_ser();
  } else {
      puts("Boot : SDC not found.\n");
      puts("Boot : Going to serial boot mode.\n");
      boot_from_ser();
  }

  for (;;) { }

  return 0;
}

