
#include "kozos.h"
#include "re.h"
#include "sw.h"
#include "intr.h"
#include "ipc_menu.h"

#define H8_3069F_ISCR       ((volatile uint8 *)0xFEE014)
#define H8_3069F_IER        ((volatile uint8 *)0xFEE015)
#define H8_3069F_ISR        ((volatile uint8 *)0xFEE016)

#define H8_3069F_TSTR       ((volatile uint8 *)0xFFFF60)
#define H8_3069F_TISRC      ((volatile uint8 *)0xFFFF66)

#define H8_3069F_16TCR0     ((volatile uint8 *)0xFFFF68)
#define H8_3069F_TIOR0      ((volatile uint8 *)0xFFFF69)
#define H8_3069F_16TCNT0H   ((volatile uint8 *)0xFFFF6A)
#define H8_3069F_16TCNT0L   ((volatile uint8 *)0xFFFF6B)

#define H8_3069F_16TCR1     ((volatile uint8 *)0xFFFF70)
#define H8_3069F_TIOR1      ((volatile uint8 *)0xFFFF71)
#define H8_3069F_16TCNT1H   ((volatile uint8 *)0xFFFF72)
#define H8_3069F_16TCNT1L   ((volatile uint8 *)0xFFFF73)

#define MAX_BIT_COUNT (64)

#define IRQ4_ENABLE() \
  do { \
    (*H8_3069F_ISCR |= (1 << 4)); \
    (*H8_3069F_IER  |= (1 << 4)); \
  } while (0)

#define TCNT0_START()   (*H8_3069F_TSTR |=  (1 << 0))
#define TCNT0_STOP()    (*H8_3069F_TSTR &= ~(1 << 0))
#define TCNT0_VALUE()   (((*H8_3069F_16TCNT0H) << 8) | ((*H8_3069F_16TCNT0L) << 0))
#define TCNT0_RESET()  \
  do { \
    *H8_3069F_16TCNT0H = 0; \
    *H8_3069F_16TCNT0L = 0; \
  } while (0)

#define TCNT1_START()   (*H8_3069F_TSTR |=  (1 << 1))
#define TCNT1_STOP()    (*H8_3069F_TSTR &= ~(1 << 1))
#define TCNT1_VALUE()   (((*H8_3069F_16TCNT1H) << 8) | ((*H8_3069F_16TCNT1L) << 0))
#define TCNT1_RESET()  \
  do { \
    *H8_3069F_16TCNT1H = 0; \
    *H8_3069F_16TCNT1L = 0; \
  } while (0)

#define TCR0_SETUP()        (*H8_3069F_16TCR0 = 0x03)
#define TCR0_INTR_ENABLE()  (*H8_3069F_TISRC |=  (1 << 4))
#define TCR0_FLAG_CLEAR()   (*H8_3069F_TISRC &= ~(1 << 0))

#define TCR1_SETUP()        (*H8_3069F_16TCR1 = 0x03)
#define TCR1_INTR_ENABLE()  (*H8_3069F_TISRC |=  (1 << 5))
#define TCR1_FLAG_CLEAR()   (*H8_3069F_TISRC &= ~(1 << 1))

#define VS1011E_CHK_DREQ()  (((*PORTCONF_P4DR) & PORTCONF_P4BIT_VSDREQ) ? 0 : 1)

typedef enum {
  WaitLeader,
  FoundLeader,
  Receiving,
} ir_state_t;

static ir_state_t irs = WaitLeader;
static uint8 data[MAX_BIT_COUNT / 8];
static uint16 bitcnt = 0;
static uint16 prev = 0, curr = 0;

static void remocon_intr_edge(void)
{
  switch (irs) {
    case WaitLeader:
      TCNT0_START();
      bitcnt = 0;
      irs = FoundLeader;
      break;
    case FoundLeader:
      irs = Receiving;
      break;
    case Receiving:
      if (bitcnt < MAX_BIT_COUNT) {
        if ((bitcnt % 8) == 0) {
          data[bitcnt / 8] = 0;
        }
        uint16 tmrval = TCNT0_VALUE();
        if (tmrval > 0x1077) {
          data[bitcnt / 8] |= (1 << (bitcnt % 8));
        }
        bitcnt++;
      }
      if (32 <= bitcnt) {
        ipc_menu_remote_from_isr(&data[0], 4);
        irs = WaitLeader;
        TCNT0_STOP();
      }
      break;
    default:
      break;
  }
  TCNT0_RESET();
}

static void remocon_intr_tovf(void)
{
  TCR0_FLAG_CLEAR();
  irs = WaitLeader;
  TCNT0_STOP();
}

static void encoder_intr_tovf(void)
{
  TCR1_FLAG_CLEAR();

  /*
   * ロータリーエンコーダ入力処理
   */
  curr = re_read();
  if (curr != prev) {
      int dir = (int)(curr & 0xff) - (int)(prev & 0xff);
      if (dir < 0) {
          if (-32 < dir) {
              ipc_menu_rotary_from_isr(1, 0);
          }
      } else {
          if (dir < 32) {
              ipc_menu_rotary_from_isr(0, 1);
          }
      }
      prev = curr;
  }

  /*
   * スイッチ入力処理
   */
  static int sw1_prev = 0, sw1_curr = 0;
  static int sw2_prev = 0, sw2_curr = 0;
  static int swr_prev = 0, swr_curr = 0;
  sw1_curr = sw_read(Sw1);
  sw2_curr = sw_read(Sw2);
  swr_curr = sw_read(SwRe);
  int s1 = 0, s2 = 0, sr = 0;
  if ((sw1_prev != sw1_curr) && (sw1_curr)) {
      s1 = 1;
  }
  if ((sw2_prev != sw2_curr) && (sw2_curr)) {
      s2 = 1;
  }
  if ((swr_prev != swr_curr) && (swr_curr)) {
      sr = 1;
  }
  if (s1 || s2 || sr) {
      ipc_menu_switch_from_isr(s1, s2, sr);
  }
  sw1_prev = sw1_curr;
  sw2_prev = sw2_curr;
  swr_prev = swr_curr;
}

int task_input(int argc, char *argv[])
{
  /*
   * Setup.
   */
  kz_setintr(SOFTVEC_TYPE_IR_EDGE, remocon_intr_edge);
  kz_setintr(SOFTVEC_TYPE_IR_TOVF, remocon_intr_tovf);
  kz_setintr(SOFTVEC_TYPE_RE_TOVF, encoder_intr_tovf);

  TCR0_SETUP();
  TCR0_INTR_ENABLE();

  TCR1_SETUP();
  TCR1_INTR_ENABLE();
  TCNT1_START();

  IRQ4_ENABLE();

  while (1) {
    kz_sleep();
  }

  return 0;
}

