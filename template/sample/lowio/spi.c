
#include "spi.h"
#include "portconf.h"

#define SPI_SCI2_SMR     ((volatile uint8 *)0xFFFFC0)
#define SPI_SCI2_BRR     ((volatile uint8 *)0xFFFFC1)
#define SPI_SCI2_SCR     ((volatile uint8 *)0xFFFFC2)
#define SPI_SCI2_TDR     ((volatile uint8 *)0xFFFFC3)
#define SPI_SCI2_SSR     ((volatile uint8 *)0xFFFFC4)
#define SPI_SCI2_RDR     ((volatile uint8 *)0xFFFFC5)
#define SPI_SCI2_SCMR    ((volatile uint8 *)0xFFFFC6)

#define SSR_BIT_TDRE    (1 << 7)
#define SSR_BIT_RDRF    (1 << 6)
#define SSR_BIT_ORER    (1 << 5)
#define SSR_BIT_FER     (1 << 4)
#define SSR_BIT_PER     (1 << 3)

#define CK_H()  do { *PORTCONF_PBDR |=  PORTCONF_PBBIT_SCLK; } while (0)    /* Set MMC SCLK "high" */
#define CK_L()  do { *PORTCONF_PBDR &= ~PORTCONF_PBBIT_SCLK; } while (0)    /* Set MMC SCLK "low" */
#define DI_H()  do { *PORTCONF_PBDR |=  PORTCONF_PBBIT_MOSI; } while (0)    /* Set MMC DI "high" */
#define DI_L()  do { *PORTCONF_PBDR &= ~PORTCONF_PBBIT_MOSI; } while (0)    /* Set MMC DI "low" */
#define DO      ((*PORTCONF_PBDR & PORTCONF_PBBIT_MISO) ? 1 : 0)            /* Get MMC DO value (high:true, low:false) */

#define VS1011E_CTRL_H()    do { *PORTCONF_P4DR |=  PORTCONF_P4BIT_VSCCS; } while (0)
#define VS1011E_CTRL_L()    do { *PORTCONF_P4DR &= ~PORTCONF_P4BIT_VSCCS; } while (0)
#define VS1011E_DATA_H()    do { *PORTCONF_P4DR |=  PORTCONF_P4BIT_VSDCS; } while (0)
#define VS1011E_DATA_L()    do { *PORTCONF_P4DR &= ~PORTCONF_P4BIT_VSDCS; } while (0)
#define SDCARD_H()          do { *PORTCONF_P4DR |=  PORTCONF_P4BIT_SDCCS; } while (0)   /* Set MMC CS "high" */
#define SDCARD_L()          do { *PORTCONF_P4DR &= ~PORTCONF_P4BIT_SDCCS; } while (0)   /* Set MMC CS "low" */

void spi_init(void)
{
    int i;
    *SPI_SCI2_SCR = 0x00;
    *SPI_SCI2_SMR = 0x80;
    *SPI_SCI2_BRR = 0x01;
    for (i = 0; i < 20; i++) { asm("nop;"); }
    *SPI_SCI2_SCR = 0x30;
    *SPI_SCI2_SCMR = 0xFA;
}

void spi_tx(uint8 d)
{
    *SPI_SCI2_TDR = d;
    *SPI_SCI2_SSR &= ~(SSR_BIT_TDRE | SSR_BIT_ORER | SSR_BIT_FER | SSR_BIT_PER);
    while (!(*SPI_SCI2_SSR & SSR_BIT_RDRF)) {
    }
    *SPI_SCI2_SSR &= ~(SSR_BIT_RDRF);
}

uint8 spi_rx(void)
{
    uint8 r;
    *SPI_SCI2_TDR = 0xff;
    *SPI_SCI2_SSR &= ~(SSR_BIT_TDRE | SSR_BIT_ORER | SSR_BIT_FER | SSR_BIT_PER);
    while (!(*SPI_SCI2_SSR & SSR_BIT_RDRF)) {
    }
    r = *SPI_SCI2_RDR;
    *SPI_SCI2_SSR &= ~(SSR_BIT_RDRF);
    return r;
}

void spi_select(SpiTarget st)
{
    spi_deselect();
    switch (st) {
        case SpiTarget_VS1011E_CTRL:
            VS1011E_CTRL_L();
            break;
        case SpiTarget_VS1011E_DATA:
            VS1011E_DATA_L();
            break;
        case SpiTarget_SDCARD:
            SDCARD_L();
            break;
    }
}

void spi_deselect(void)
{
    VS1011E_CTRL_H();
    VS1011E_DATA_H();
    SDCARD_H();
}

