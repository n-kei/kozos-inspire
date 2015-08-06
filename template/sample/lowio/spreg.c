
#include "spreg.h"
#include "defines.h"
#include "portconf.h"

/*
 * DRAM
 */
#define SPREG_DRAM_ABWCR  ((volatile uint8 *)0xfee020)
#define SPREG_DRAM_ASTCR  ((volatile uint8 *)0xfee021)
#define SPREG_DRAM_RTCOR  ((volatile uint8 *)0xfee02a)
#define SPREG_DRAM_RTMCSR ((volatile uint8 *)0xfee028)
#define SPREG_DRAM_DRCRB  ((volatile uint8 *)0xfee027)
#define SPREG_DRAM_DRCRA  ((volatile uint8 *)0xfee026)
#define SPREG_DRAM_WCRH   ((volatile uint8 *)0xfee022)
#define SPREG_DRAM_WCRL   ((volatile uint8 *)0xfee023)

/*
 * ITU
 */
#define SPREG_ITU_TMDR       ((volatile uint8 *)0xFFFF62)
#define SPREG_ITU_TSTR       ((volatile uint8 *)0xFFFF60)
#define SPREG_ITU_16TCNT2H   ((volatile uint8 *)0xFFFF7A)
#define SPREG_ITU_16TCNT2L   ((volatile uint8 *)0xFFFF7B)

#define SPREG_ITU_TSTR_BIT_STR2   (1 << 2)
#define SPREG_ITU_TMDR_BIT_MDF    (1 << 6)

/*
 * Chip Select Control Register
 */
#define SPREG_CSCR       ((volatile uint8 *)0xFEE01F)

void spreg_itu_init(void)
{
  *SPREG_ITU_TMDR = SPREG_ITU_TMDR_BIT_MDF;
  *SPREG_ITU_TSTR = SPREG_ITU_TSTR_BIT_STR2;
}

void spreg_itu_counter(uint16 *value)
{
  *value = ((*SPREG_ITU_16TCNT2H) << 8) | (*SPREG_ITU_16TCNT2L << 0);
}

void spreg_dram_init(void)
{
  int i, j;

  *SPREG_DRAM_ABWCR  = 0xff;
  *SPREG_DRAM_RTCOR  = 0x03; /* リフレッシュ周期を短めに設定 */
  *SPREG_DRAM_RTMCSR = 0x37;
  *SPREG_DRAM_DRCRB  = 0x8f; /* ウエイト挿入 */
  *SPREG_DRAM_DRCRA  = 0x20;

  *PORTCONF_P1DDR  = 0xff;
  *PORTCONF_P2DDR  = 0x07;
  *PORTCONF_P8DDR  = 0xee;
  *PORTCONF_PBDDR  = 0x6c;

  for (i = 0; i < 200; i++) {
    for (j = 0; j < 200; j++) {
      asm volatile ("nop");
    }
  }

  /*
   * 3ステートアクセス
   */
  *SPREG_DRAM_WCRH = 0xff;
  *SPREG_DRAM_WCRL = 0xff;

  /*
   * 3ステートアクセス
   */
  *SPREG_DRAM_ASTCR = 0xff;

  /*
   * チップセレクトコントロールレジスタもここで設定する。
   */
  *SPREG_CSCR = 0x3F;
}

