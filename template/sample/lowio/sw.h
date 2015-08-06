#ifndef _SW_H_INCLUDED_
#define _SW_H_INCLUDED_

#include "defines.h"

typedef enum {
    Sw1,
    Sw2,
    SwRe,
} sw_target_t;

int sw_init(void);
uint8 sw_read(sw_target_t target);

#endif

