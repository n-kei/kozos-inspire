
#ifndef PORTCONF_H
#define PORTCONF_H

#include "defines.h"

/*
 * Data Direction Register
 */

#define PORTCONF_P1DDR  ((volatile uint8 *)0xfee000)
#define PORTCONF_P2DDR  ((volatile uint8 *)0xfee001)
#define PORTCONF_P4DDR  ((volatile uint8 *)0xFEE003)
#define PORTCONF_P8DDR  ((volatile uint8 *)0xfee007)
#define PORTCONF_PADDR  ((volatile uint8 *)0xFEE009)
#define PORTCONF_PBDDR  ((volatile uint8 *)0xfee00a)

/*
 * Port Data Register
 */

#define PORTCONF_P4DR   ((volatile uint8 *)0xFFFFD3)
#define PORTCONF_P7DR   ((volatile uint8 *)0xFFFFD6)
#define PORTCONF_PADR   ((volatile uint8 *)0xFFFFD9)
#define PORTCONF_PBDR   ((volatile uint8 *)0xFFFFDA)

/*
 * Bit
 */

#define PORTCONF_PABIT_LEDG     (1 << 2)
#define PORTCONF_PABIT_LEDR     (1 << 3)
#define PORTCONF_PABIT_SWRE     (1 << 4)
#define PORTCONF_PABIT_LED1     (1 << 6)
#define PORTCONF_PABIT_LED2     (1 << 7)

#define PORTCONF_PBBIT_SCLK     (1 << 5)
#define PORTCONF_PBBIT_MOSI     (1 << 6)
#define PORTCONF_PBBIT_MISO     (1 << 7)

#define PORTCONF_P4BIT_SDCCS    (1 << 0)
#define PORTCONF_P4BIT_SDCDET   (1 << 1)
#define PORTCONF_P4BIT_VSCCS    (1 << 2)
#define PORTCONF_P4BIT_VSDCS    (1 << 3)
#define PORTCONF_P4BIT_VSDREQ   (1 << 4)
#define PORTCONF_P4BIT_VSRST    (1 << 5)
#define PORTCONF_P4BIT_LCD_RES  (1 << 7)

#define PORTCONF_P7BIT_SW1      (1 << 0)
#define PORTCONF_P7BIT_SW2      (1 << 1)

/*
 * Utilities
 */
#define PORTCONF_SDC_DETECT()   (!(*PORTCONF_P4DR & PORTCONF_P4BIT_SDCDET))

#endif

