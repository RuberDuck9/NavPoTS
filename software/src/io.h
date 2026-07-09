#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include <stdint.h>

#ifndef io_h
#define io_h

void set_pin(enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio);
void clear_pin(enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio);

#endif
