#ifndef _LED_H_INCLUDED_
#define _LED_H_INCLUDED_

typedef enum {
  Led1,
  Led2,
  LedG,
  LedR,
} led_target_t;

typedef enum {
  LedOn,
  LedOff,
} led_state_t;

int led_init(void);
int led_write(led_target_t target, led_state_t state);
int led_toggle(led_target_t target);

#endif

