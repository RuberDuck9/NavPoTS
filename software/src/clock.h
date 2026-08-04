#ifndef clock_h
#define clock_h

#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/rcc.h>

#include <stdint.h>

void configure_system_clock(void);

#endif
