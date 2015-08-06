
#include "vs1011e.h"
#include "portconf.h"
#include "spi.h"

#define VS1011E_OPCODE_READ	0x03
#define VS1011E_OPCODE_WRITE	0x02

#define REGADDR_MODE		0x00
#define REGADDR_STATUS		0x01
#define REGADDR_BASS		0x02
#define REGADDR_CLOCKF		0x03
#define REGADDR_DECODE_TIME	0x04
#define REGADDR_AUDATA		0x05
#define REGADDR_WRAM		0x06
#define REGADDR_WRAMADDR	0x07
#define REGADDR_HDAT0		0x08
#define REGADDR_HDAT1		0x09
#define REGADDR_AIADDR		0x0A
#define REGADDR_VOL		0x0B
#define REGADDR_AICTRL0		0x0C
#define REGADDR_AICTRL1		0x0D
#define REGADDR_AICTRL2		0x0E
#define REGADDR_AICTRL3		0x0F

#define SM_DIFF		(1 <<  0)
#define SM_LAYER12	(1 <<  1)
#define SM_RESET	(1 <<  2)
#define SM_OUTOFWAV	(1 <<  3)
#define SM_SETTOZERO1	(1 <<  4)
#define SM_TESTS	(1 <<  5)
#define SM_STREAM	(1 <<  6)
#define SM_SETTOZERO2	(1 <<  7)
#define SM_DACT		(1 <<  8)
#define SM_SDIORD	(1 <<  9)
#define SM_SDISHARE	(1 << 10)
#define SM_SDINEW	(1 << 11)
#define SM_SETTOZERO3	(1 << 12)
#define SM_SETTOZERO4	(1 << 13)

#define SCI_BASS_BITBASS_ST_AMP		12
#define SCI_BASS_BITBASS_ST_FREQ	8
#define SCI_BASS_BITBASS_SB_AMP		4
#define SCI_BASS_BITBASS_SB_FREQ	0

#define VS1011E_RESET1()    do { *PORTCONF_P4DR |=  PORTCONF_P4BIT_VSRST; } while (0)
#define VS1011E_RESET0()    do { *PORTCONF_P4DR &= ~PORTCONF_P4BIT_VSRST; } while (0)

#define VS1011E_CHK_DREQ()  (((*PORTCONF_P4DR) & PORTCONF_P4BIT_VSDREQ) ? 0 : 1)

static void _delay_ms(int ms)
{
    int i;
    for (i = 0; i < ms * 10000; i++) {
    }
}

static void _delay_us(int us)
{
    int i;
    for (i = 0; i < us * 10; i++) {
    }
}

static void vs1011e_read(uint8 addr, uint16 * stat);
static void vs1011e_write(uint8 addr, uint16 stat);

void vs1011e_init()
{
    vs1011e_reset_by_hardware();
    vs1011e_reset_by_software();
}

void vs1011e_reset_by_hardware()
{
    // Assert vs1011 reset
    VS1011E_RESET0();
    // Delay 30ms
    _delay_ms(30);
    // Deassert CS
    spi_deselect();
    // Release vs1011 reset
    VS1011E_RESET1();
    // Delay 10ms (2.5ms accordig to datasheet)
    _delay_ms(10);
    // Set volume to minimum
    vs1011e_write(REGADDR_VOL, 0xFFFF);
    // Set CLOCKF
    vs1011e_write(REGADDR_CLOCKF, 0x9800);
    // Delay 1ms
    _delay_ms(1);
    // Set slow sample rate for slow analog part startup
    vs1011e_write(REGADDR_AUDATA, 10);
    // Delay 100ms
    _delay_ms(100);
    // Switch on the analog parts
    vs1011e_write(REGADDR_VOL, 0xFEFE);
    vs1011e_write(REGADDR_AUDATA, 44101);
    vs1011e_write(REGADDR_VOL, 0x0202);
}

void vs1011e_reset_by_software()
{
    uint16 i;

    // Delay 200ms
    _delay_ms(200);
    // Set SW reset bit, set VS1011 native mode on SPI
    vs1011e_write(REGADDR_MODE,
            SM_LAYER12 | SM_RESET | SM_SDINEW | SM_TESTS);
    // Delay 2us
    _delay_us(2);
    // Rewrite SCI_CLOCKF after soft reset
    vs1011e_write(REGADDR_CLOCKF, 0x9800);
    // Assert DCS
    spi_select(SpiTarget_VS1011E_DATA);
    // Check the DREQ.
    while (VS1011E_CHK_DREQ()) {
    }
    // Send 0x53 to SPI
    spi_tx(0x53);
    // Send 1024 nulls
    for (i = 0; i < 1024; i++) {
        // Check the DREQ.
        while (VS1011E_CHK_DREQ()) {
        }
        spi_tx(0x00);
    }
    // Deassert DCS
    spi_deselect();
}

void vs1011e_cancel_data()
{
    uint16 i;
    while (VS1011E_CHK_DREQ()) {
    }

    spi_select(SpiTarget_VS1011E_DATA);
    for (i = 0; i < 2048; i++) {
        while (VS1011E_CHK_DREQ()) {
        }
        spi_tx(0x00);
    }
    spi_deselect();
}

void vs1011e_set_enhancer(uint8 st_amp, uint8 st_freq, uint8 sb_amp,
        uint8 sb_freq)
{
    uint16 val =
        (st_amp << SCI_BASS_BITBASS_ST_AMP) |
        (st_freq << SCI_BASS_BITBASS_ST_FREQ) |
        (sb_amp << SCI_BASS_BITBASS_SB_AMP) |
        (sb_freq << SCI_BASS_BITBASS_SB_FREQ);
    vs1011e_write(REGADDR_BASS, val);
}

void vs1011e_get_enhancer(uint8 * st_amp, uint8 * st_freq,
        uint8 * sb_amp, uint8 * sb_freq)
{
    uint16 val;
    vs1011e_read(REGADDR_BASS, &val);
    *st_amp = (val >> SCI_BASS_BITBASS_ST_AMP) & 0x0F;
    *st_freq = (val >> SCI_BASS_BITBASS_ST_FREQ) & 0x0F;
    *sb_amp = (val >> SCI_BASS_BITBASS_SB_AMP) & 0x0F;
    *sb_freq = (val >> SCI_BASS_BITBASS_SB_FREQ) & 0x0F;
}

void vs1011e_volume_read(uint8 * left, uint8 * right)
{
    uint16 val;
    vs1011e_read(REGADDR_VOL, &val);
    *left = val >> 8;
    *right = val >> 0;
}

void vs1011e_volume_write(const uint8 left, const uint8 right)
{
    uint16 val =
        (((uint16) left << 8) & 0xFF00) | (((uint16) right << 0) &
            0x00FF);
    vs1011e_write(REGADDR_VOL, val);
}

void vs1011e_play(
        void *buf, int siz,
        int (*readfunc)(void * buf, const int len))
{
    int i;
    while (1) {
        /*
         * Read the song data.
         */
        int n = readfunc(buf, siz);
        if (n <= 0) {
            return;
        }
        /*
         * Send the data.
         */
        spi_select(SpiTarget_VS1011E_DATA);
        for (i = 0; i < n; i++) {
            while (VS1011E_CHK_DREQ()) { }
            spi_tx(*((char *)buf + i));
        }
        spi_deselect();
    }
}

void vs1011e_decodetime_read(uint16 * sec)
{
    vs1011e_read(REGADDR_DECODE_TIME, sec);
}

void vs1011e_decodetime_write(const uint16 sec)
{
    vs1011e_write(REGADDR_DECODE_TIME, sec);
}

void vs1011e_sinetest_init()
{
    while (VS1011E_CHK_DREQ()) {
    }

    spi_select(SpiTarget_VS1011E_DATA);
    spi_tx(0x53);
    spi_tx(0xEF);
    spi_tx(0x6E);
    spi_tx(0xF0);
    spi_tx(0x00);
    spi_tx(0x00);
    spi_tx(0x00);
    spi_tx(0x00);
    spi_deselect();
}

void vs1011e_sinetest_fini()
{
    while (VS1011E_CHK_DREQ()) {
    }

    spi_select(SpiTarget_VS1011E_DATA);
    spi_tx(0x45);
    spi_tx(0x78);
    spi_tx(0x69);
    spi_tx(0x74);
    spi_tx(0x00);
    spi_tx(0x00);
    spi_tx(0x00);
    spi_tx(0x00);
    spi_deselect();

    vs1011e_cancel_data();
}

void vs1011e_register_print()
{
#if 0
    uint8 i;
    uint16 val;
    xprintf(PSTR("===================\r\n"));
    for (i = 0; i <= 0x0F; i++) {
        vs1011e_read(i, &val);
        xprintf(PSTR("0x%02X: 0x%04X\r\n"), i, val);
    }
    xprintf(PSTR("===================\r\n"));
#endif
}

static void vs1011e_read(uint8 addr, uint16 * stat)
{
    while (VS1011E_CHK_DREQ()) {
    }

    spi_select(SpiTarget_VS1011E_CTRL);

    spi_tx(VS1011E_OPCODE_READ);
    spi_tx(addr);

    *stat = 0;
    *stat |= spi_rx() << 8;
    *stat |= spi_rx();

    spi_deselect();
}

static void vs1011e_write(uint8 addr, uint16 stat)
{
    while (VS1011E_CHK_DREQ()) {
    }

    spi_select(SpiTarget_VS1011E_CTRL);

    spi_tx(VS1011E_OPCODE_WRITE);
    spi_tx(addr);

    spi_tx(stat >> 8);
    spi_tx(stat >> 0);

    spi_deselect();
}
