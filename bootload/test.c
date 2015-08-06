
#include "test.h"
#include "led.h"
#include "vs1011e.h"
#include "lib.h"

void test_execute(void)
{
  volatile int i;

  /*
   * L : Max.
   * R : Min.
   */
  {
    puts("Test : Phone (L)...");
    led_write(Led1, LedOn);
    led_write(Led2, LedOff);
    led_write(LedG, LedOn);
    led_write(LedR, LedOff);
    vs1011e_volume_write(0x40, 0xF0);

    vs1011e_sinetest_init();
    for (i = 0; i < 20000; i++) { }
    vs1011e_sinetest_fini();
    for (i = 0; i < 20000; i++) { }

    vs1011e_sinetest_init();
    for (i = 0; i < 20000; i++) { }
    vs1011e_sinetest_fini();
    for (i = 0; i < 20000; i++) { }

    vs1011e_sinetest_init();
    for (i = 0; i < 20000; i++) { }
    vs1011e_sinetest_fini();
    for (i = 0; i < 20000; i++) { }
    puts("Done.\n");
  }

  /*
   * L : Min.
   * R : Max.
   */
  {
    puts("Test : Phone (R)...");
    led_write(Led1, LedOff);
    led_write(Led2, LedOn);
    led_write(LedG, LedOff);
    led_write(LedR, LedOn);
    vs1011e_volume_write(0xF0, 0x40);

    vs1011e_sinetest_init();
    for (i = 0; i < 20000; i++) { }
    vs1011e_sinetest_fini();
    for (i = 0; i < 20000; i++) { }

    vs1011e_sinetest_init();
    for (i = 0; i < 20000; i++) { }
    vs1011e_sinetest_fini();
    for (i = 0; i < 20000; i++) { }

    vs1011e_sinetest_init();
    for (i = 0; i < 20000; i++) { }
    vs1011e_sinetest_fini();
    for (i = 0; i < 20000; i++) { }
    puts("Done.\n");
  }

  led_write(Led1, LedOff);
  led_write(Led2, LedOff);
  led_write(LedG, LedOff);
  led_write(LedR, LedOff);
  vs1011e_volume_write(0x40, 0x40);

  uint8 vol_left, vol_right;
  vs1011e_volume_read(&vol_left, &vol_right);
  puts("Test : Volume (L:");
  putxval(vol_left, 2);
  puts(",R:");
  putxval(vol_right, 2);
  puts(")\n");
}

