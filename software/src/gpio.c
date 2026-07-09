#include "gpio.h"

void set_pin(enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio){

	rcc_periph_clock_enable(rcc_port);

	gpio_mode_setup(
		gpio_port, 
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		gpio
	);

	gpio_set(gpio_port, gpio);
}

void clear_pin(enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio){

	rcc_periph_clock_enable(rcc_port);

	gpio_mode_setup(
		gpio_port, 
		GPIO_MODE_OUTPUT, 
		GPIO_PUPD_NONE, 
		gpio
	);

	gpio_clear(gpio_port, gpio);
}
