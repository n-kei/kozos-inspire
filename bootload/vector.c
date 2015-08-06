#include "defines.h"

extern void start(void);        /* �������ȡ����å� */
extern void intr_softerr(void); /* ���եȥ����������顼 */
extern void intr_syscall(void); /* �����ƥࡦ������ */
extern void intr_serintr(void); /* ���ꥢ������ */
extern void intr_timintr(void); /* �����޳���� */
extern void intr_ir_edge(void); /* ��⥳�󥨥å������ */
extern void intr_ir_tovf(void); /* ��⥳�󥿥��ޡ������С��ե������ */
extern void intr_re_tovf(void); /* ���󥳡��������ޡ������С��ե������ */

/*
 * ����ߥ٥��������ꡥ
 * ��󥫡�������ץȤ�����ˤ�ꡤ��Ƭ���Ϥ����֤���롥
 */
void (*vectors[])(void) = {
  start,        /*  0: �ꥻ�å� */
  NULL,         /*  1: �����ƥ�ͽ�� */
  NULL,         /*  2: �����ƥ�ͽ�� */
  NULL,         /*  3: �����ƥ�ͽ�� */
  NULL,         /*  4: �����ƥ�ͽ�� */
  NULL,         /*  5: �����ƥ�ͽ�� */
  NULL,         /*  6: �����ƥ�ͽ�� */
  NULL,         /*  7: ����������NMI */
  intr_syscall, /*  8: �ȥ�å�̿�� */
  intr_softerr, /*  9: �ȥ�å�̿�� */
  intr_softerr, /* 10: �ȥ�å�̿�� */
  intr_softerr, /* 11: �ȥ�å�̿�� */
  NULL,         /* 12: ����������IRQ0 */
  NULL,         /* 13: ����������IRQ1 */
  NULL,         /* 14: ����������IRQ2 */
  NULL,         /* 15: ����������IRQ3 */
  intr_ir_edge, /* 16: ����������IRQ4 */
  NULL,         /* 17: ����������IRQ5 */
  NULL,         /* 18: �����ƥ�ͽ�� */
  NULL,         /* 19: �����ƥ�ͽ�� */
  NULL,         /* 20: �����å��ɥå������� */
  NULL,         /* 21: DRAM���󥿡��ե����� CMI */
  NULL,         /* 22: �����ƥ�ͽ�� */
  NULL,         /* 23: A/D ADI */
  NULL,         /* 24: ITU����ͥ�0 IMIA0 */
  NULL,         /* 25: ITU����ͥ�0 IMIB0 */
  intr_ir_tovf, /* 26: ITU����ͥ�0 OVI0  */
  NULL,         /* 27: �����ƥ�ͽ�� */
  NULL,         /* 28: ITU����ͥ�1 IMIA1 */
  NULL,         /* 29: ITU����ͥ�1 IMIB1 */
  intr_re_tovf, /* 30: ITU����ͥ�1 OVI1  */
  NULL,         /* 31: �����ƥ�ͽ�� */
  NULL,         /* 32: ITU����ͥ�2 IMIA2 */
  NULL,         /* 33: ITU����ͥ�2 IMIB2 */
  NULL,         /* 34: ITU����ͥ�2 OVI2  */
  NULL,         /* 35: �����ƥ�ͽ�� */
  intr_timintr, /* 36: ITU����ͥ�3 CMIA0 */
  intr_timintr, /* 37: ITU����ͥ�3 CMIB0 */
  intr_timintr, /* 38: ITU����ͥ�3 CMIA1/CMIB1 */
  intr_timintr, /* 39: ITU����ͥ�3 TOVIO0/TOVI1 */
  intr_timintr, /* 40: ITU����ͥ�4 CMIA2 */
  intr_timintr, /* 41: ITU����ͥ�4 CMIB2 */
  intr_timintr, /* 42: ITU����ͥ�4 CMIA3/CMIB3 */
  intr_timintr, /* 43: ITU����ͥ�4 TOVI2/TOVI3 */
  NULL,         /* 44: DMAC */
  NULL,         /* 45: DMAC */
  NULL,         /* 46: DMAC */
  NULL,         /* 47: DMAC */
  NULL,         /* 48: �����ƥ�ͽ�� */
  NULL,         /* 49: �����ƥ�ͽ�� */
  NULL,         /* 50: �����ƥ�ͽ�� */
  NULL,         /* 51: �����ƥ�ͽ�� */
  intr_serintr, /* 52: SCI����ͥ�0 ERI0 */
  intr_serintr, /* 53: SCI����ͥ�0 RXI0 */
  intr_serintr, /* 54: SCI����ͥ�0 TXI0 */
  intr_serintr, /* 55: SCI����ͥ�0 TEI0 */
  intr_serintr, /* 56: SCI����ͥ�1 ERI1 */
  intr_serintr, /* 57: SCI����ͥ�1 RXI1 */
  intr_serintr, /* 58: SCI����ͥ�1 TXI1 */
  intr_serintr, /* 59: SCI����ͥ�1 TEI1 */
  intr_serintr, /* 60: SCI����ͥ�2 ERI2 */
  intr_serintr, /* 61: SCI����ͥ�2 RXI2 */
  intr_serintr, /* 62: SCI����ͥ�2 TXI2 */
  intr_serintr, /* 63: SCI����ͥ�2 TEI2 */
};

