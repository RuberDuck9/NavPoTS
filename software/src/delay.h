#ifndef delay_h
#define delay_h

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>

#include <stdint.h>

extern uint64_t clock_milliseconds;

void sys_tick_handler(void);
void configure_systick(void);
void delay(uint32_t delay_milliseconds);

#endif
