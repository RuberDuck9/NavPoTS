#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/usart.h>

#include <stdint.h>

#ifndef usart_h
#define usart_h

void usart_init(enum rcc_periph_clken usart_rcc_port, uint32_t usart_gpio_port, uint16_t usart_rx, uint16_t usart_tx, uint32_t usart_bus, uint8_t usart_baud_rate, uint8_t usart_mode);
void usart_print(char *buffer);
void usart_println(char *buffer);

#endif
