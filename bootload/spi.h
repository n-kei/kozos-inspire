
#ifndef SPI_H
#define SPI_H

#include "defines.h"

typedef enum {
    SpiTarget_VS1011E_CTRL,
    SpiTarget_VS1011E_DATA,
    SpiTarget_SDCARD
} SpiTarget;

void spi_init(void);
void spi_tx(uint8 d);
uint8 spi_rx(void);
void spi_select(SpiTarget st);
void spi_deselect(void);

#endif

