
#include "defines.h"
#include "lib.h"
#include "dram.h"
#include "portconf.h"
#include "spreg.h"

typedef struct {
  union {
    volatile uint8  val8[4];
    volatile uint16 val16[2];
    volatile uint32 val32[1];
  } u;
} val_t;

int dram_init()
{
  spreg_dram_init();
  return 0;
}

static int check_val(volatile val_t *p, volatile val_t *wval)
{
  volatile val_t rval;

  p->u.val8[0] = wval->u.val8[0]; p->u.val8[1] = wval->u.val8[1];
  p->u.val8[2] = wval->u.val8[2]; p->u.val8[3] = wval->u.val8[3];
  rval.u.val8[0] = p->u.val8[0]; rval.u.val8[1] = p->u.val8[1];
  rval.u.val8[2] = p->u.val8[2]; rval.u.val8[3] = p->u.val8[3];

  if (rval.u.val32[0] != wval->u.val32[0])
    return -1;

  p->u.val16[0] = wval->u.val16[0]; p->u.val16[1] = wval->u.val16[1];
  rval.u.val16[0] = p->u.val16[0]; rval.u.val16[1] = p->u.val16[1];

  if (rval.u.val32[0] != wval->u.val32[0])
    return -1;

  p->u.val32[0] = wval->u.val32[0];
  rval.u.val32[0] = p->u.val32[0];

  if (rval.u.val32[0] != wval->u.val32[0])
    return -1;

  return 0;
}

int dram_check()
{
  uint32 *p;
  int err;
  val_t val;

  puts("DRAM checking...\n");

  for (p = (uint32 *)DRAM_START; p < (uint32 *)DRAM_END; p++) {
    putxval((unsigned long)p, 8);
    err = 1;

    val.u.val32[0] = (uint32)p;
    if (check_val((val_t *)p, &val) < 0)
      goto err;

    val.u.val32[0] = 0;
    if (check_val((val_t *)p, &val) < 0)
      goto err;

    val.u.val32[0] = 0xffffffffUL;
    if (check_val((val_t *)p, &val) < 0)
      goto err;

    puts("\x08\x08\x08\x08\x08\x08\x08\x08");
  }
  puts("\nall check OK.\n");
  return 0;

err:
  puts("\nERROR: ");
  putxval((unsigned long)*p, 8);
  puts("\n");
  return -1;
}

static uint32 dram_check2_val0(uint32 *addr) {  return  0x55555555UL; }
static uint32 dram_check2_val1(uint32 *addr) {  return  0xaaaaaaaaUL; }
static uint32 dram_check2_val2(uint32 *addr) {  return  0x00000000UL; }
static uint32 dram_check2_val3(uint32 *addr) {  return  0xffffffffUL; }
static uint32 dram_check2_val4(uint32 *addr) {  return  (uint32)addr; }
static uint32 dram_check2_val5(uint32 *addr) {  return ~(uint32)addr; }

int dram_check2()
{
  uint32 *p;
  int ret = 0, i;
  uint32 (*getval[])(uint32 *) = {
    dram_check2_val0,
    dram_check2_val1,
    dram_check2_val2,
    dram_check2_val3,
    dram_check2_val4,
    dram_check2_val5,
    NULL
  };

  for (i = 0; getval[i]; i++) {

    puts("DRAM check pattern: ");
    putxval(i, 0);

    puts("\nDRAM setting...\n");

    for (p = (uint32 *)DRAM_START; p < (uint32 *)DRAM_END; p++) {
      *p = getval[i](p);
      if (!((uint32)p & 0xfff)) {
	putxval((unsigned long)p, 8);
	puts("\x08\x08\x08\x08\x08\x08\x08\x08");
      }
    }

    puts("\nDRAM checking...\n");

    for (p = (uint32 *)DRAM_START; p < (uint32 *)DRAM_END; p++) {
      if (*p != getval[i](p)) {
	puts("\nERROR! :");
	putxval((unsigned long)p, 8);
	puts(" ");
	putxval((unsigned long)*p, 8);
	puts("\n");
	ret = -1;
      }
      if (!((uint32)p & 0xfff)) {
	putxval((unsigned long)p, 8);
	puts("\x08\x08\x08\x08\x08\x08\x08\x08");
      }
    }

    puts("\n");

  }

  if (ret == 0) {
    puts("\nall check OK.\n");
  }

  return ret;
}

int dram_clear()
{
  uint32 *p;

  puts("DRAM clearing...\n");

  for (p = (uint32 *)DRAM_START; p < (uint32 *)DRAM_END; p++)
    *p = 0;

  puts("DRAM cleared.\n");

  return 0;
}
