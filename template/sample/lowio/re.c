#include "re.h"
#include "spreg.h"

int re_init(void)
{
  spreg_itu_init();
  return 0;
}

uint16 re_read(void)
{
  uint16 value;
  spreg_itu_counter(&value);
  return value;
}

