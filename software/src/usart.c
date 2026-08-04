#include "usart.h"

void usart_init(enum rcc_periph_clken usart_rcc_port, enum rcc_periph_clken usart_rcc_bus, uint32_t usart_gpio_port, uint16_t usart_rx, uint16_t usart_tx, uint32_t usart_bus, uint32_t usart_baud_rate, uint8_t usart_mode){

	// enable closk for the peripheral ports
	rcc_periph_clock_enable(usart_rcc_port);
	rcc_periph_clock_enable(usart_rcc_bus);

	// configure tx rx 
	gpio_mode_setup(
		usart_gpio_port, 
		GPIO_MODE_AF, 
		GPIO_PUPD_NONE, 
		usart_rx | usart_tx
	);

	gpio_set_af(
		usart_gpio_port, 
		GPIO_AF7, 
		usart_rx | usart_tx);

	// configure usart frame parameters
	usart_set_baudrate(usart_bus, usart_baud_rate);
	usart_set_databits(usart_bus, 8);
	usart_set_stopbits(usart_bus, USART_STOPBITS_1);
	usart_set_parity(usart_bus, USART_PARITY_NONE);
	usart_set_flow_control(usart_bus, USART_FLOWCONTROL_NONE);
	usart_set_mode(usart_bus, usart_mode);

	usart_enable(usart_bus);
}

void usart_print(uint32_t usart_bus, char *buffer){

	while (*buffer){
		usart_send_blocking(usart_bus, *buffer);
		buffer++;
	}
}

void usart_println(uint32_t usart_bus, char *buffer){

	usart_print(usart_bus, buffer);
	usart_print(usart_bus, "\r\n");
}
