#include "defines.h"

extern void start(void);        /* スタート・アップ */
extern void intr_softerr(void); /* ソフトウエア・エラー */
extern void intr_syscall(void); /* システム・コール */
extern void intr_serintr(void); /* シリアル割込み */
extern void intr_timintr(void); /* タイマ割込み */
extern void intr_ir_edge(void); /* リモコンエッジ割込み */
extern void intr_ir_tovf(void); /* リモコンタイマーオーバーフロー割込み */
extern void intr_re_tovf(void); /* エンコーダタイマーオーバーフロー割込み */

/*
 * 割込みベクタの設定．
 * リンカ・スクリプトの定義により，先頭番地に配置される．
 */
void (*vectors[])(void) = {
  start,        /*  0: リセット */
  NULL,         /*  1: システム予約 */
  NULL,         /*  2: システム予約 */
  NULL,         /*  3: システム予約 */
  NULL,         /*  4: システム予約 */
  NULL,         /*  5: システム予約 */
  NULL,         /*  6: システム予約 */
  NULL,         /*  7: 外部割り込みNMI */
  intr_syscall, /*  8: トラップ命令 */
  intr_softerr, /*  9: トラップ命令 */
  intr_softerr, /* 10: トラップ命令 */
  intr_softerr, /* 11: トラップ命令 */
  NULL,         /* 12: 外部割り込みIRQ0 */
  NULL,         /* 13: 外部割り込みIRQ1 */
  NULL,         /* 14: 外部割り込みIRQ2 */
  NULL,         /* 15: 外部割り込みIRQ3 */
  intr_ir_edge, /* 16: 外部割り込みIRQ4 */
  NULL,         /* 17: 外部割り込みIRQ5 */
  NULL,         /* 18: システム予約 */
  NULL,         /* 19: システム予約 */
  NULL,         /* 20: ウォッチドッグタイマ */
  NULL,         /* 21: DRAMインターフェース CMI */
  NULL,         /* 22: システム予約 */
  NULL,         /* 23: A/D ADI */
  NULL,         /* 24: ITUチャネル0 IMIA0 */
  NULL,         /* 25: ITUチャネル0 IMIB0 */
  intr_ir_tovf, /* 26: ITUチャネル0 OVI0  */
  NULL,         /* 27: システム予約 */
  NULL,         /* 28: ITUチャネル1 IMIA1 */
  NULL,         /* 29: ITUチャネル1 IMIB1 */
  intr_re_tovf, /* 30: ITUチャネル1 OVI1  */
  NULL,         /* 31: システム予約 */
  NULL,         /* 32: ITUチャネル2 IMIA2 */
  NULL,         /* 33: ITUチャネル2 IMIB2 */
  NULL,         /* 34: ITUチャネル2 OVI2  */
  NULL,         /* 35: システム予約 */
  intr_timintr, /* 36: ITUチャネル3 CMIA0 */
  intr_timintr, /* 37: ITUチャネル3 CMIB0 */
  intr_timintr, /* 38: ITUチャネル3 CMIA1/CMIB1 */
  intr_timintr, /* 39: ITUチャネル3 TOVIO0/TOVI1 */
  intr_timintr, /* 40: ITUチャネル4 CMIA2 */
  intr_timintr, /* 41: ITUチャネル4 CMIB2 */
  intr_timintr, /* 42: ITUチャネル4 CMIA3/CMIB3 */
  intr_timintr, /* 43: ITUチャネル4 TOVI2/TOVI3 */
  NULL,         /* 44: DMAC */
  NULL,         /* 45: DMAC */
  NULL,         /* 46: DMAC */
  NULL,         /* 47: DMAC */
  NULL,         /* 48: システム予約 */
  NULL,         /* 49: システム予約 */
  NULL,         /* 50: システム予約 */
  NULL,         /* 51: システム予約 */
  intr_serintr, /* 52: SCIチャネル0 ERI0 */
  intr_serintr, /* 53: SCIチャネル0 RXI0 */
  intr_serintr, /* 54: SCIチャネル0 TXI0 */
  intr_serintr, /* 55: SCIチャネル0 TEI0 */
  intr_serintr, /* 56: SCIチャネル1 ERI1 */
  intr_serintr, /* 57: SCIチャネル1 RXI1 */
  intr_serintr, /* 58: SCIチャネル1 TXI1 */
  intr_serintr, /* 59: SCIチャネル1 TEI1 */
  intr_serintr, /* 60: SCIチャネル2 ERI2 */
  intr_serintr, /* 61: SCIチャネル2 RXI2 */
  intr_serintr, /* 62: SCIチャネル2 TXI2 */
  intr_serintr, /* 63: SCIチャネル2 TEI2 */
};

