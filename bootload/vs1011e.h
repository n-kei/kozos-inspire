#ifndef VS1011_H
#define VS1011_H

#include "defines.h"

void vs1011e_init(void);
void vs1011e_reset_by_hardware(void);
void vs1011e_reset_by_software(void);
void vs1011e_cancel_data(void);
void vs1011e_set_enhancer(uint8 st_amp, uint8 st_freq, uint8 sb_amp, uint8 sb_freq);
void vs1011e_get_enhancer(uint8 * st_amp, uint8 * st_freq, uint8 * sb_amp, uint8 * sb_freq);
void vs1011e_volume_read(uint8 * left, uint8 * right);
void vs1011e_volume_write(const uint8 left, const uint8 right);
void vs1011e_play(
        void *buf, int siz,
        int (*readfunc)(void * buf, const int len));
void vs1011e_decodetime_read(uint16 * sec);
void vs1011e_decodetime_write(const uint16 sec);
void vs1011e_register_print(void);

void vs1011e_sinetest_init(void);
void vs1011e_sinetest_fini(void);

#endif

