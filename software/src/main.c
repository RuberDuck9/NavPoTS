/*
 * The following is a list of a the most important hardware connections in the version 1.0 of this project's pcb
 *
 * DEBUG_0 - PE15
 * DEBUG_1 - PE14
 * DEBUG_2 - PG3
 * DEBUG_3 - PG4
 * DEBUG_4 - PG5
 * DEBUG_5 - PG6
 *
 * SPI3_SCK - PC10
 * SPI3_MISO - PC11
 * SPI3_MOSI - PC12
 * SPI3_CS0 - PD0
 * SPI3_CS1 - PD1
 * SPI3_CS2 - PD3
 * SPI3_CS3 - PD4
 * 
 * USART3_TX - PB10
 * USART3_RX - PB11
 *
 * UART7_RX - PE7
 * UART7_TX - PE8
 *
 * I2C4_SCL - PF14
 * I2C4_SDA - PF15
 *
 */

// libopencm3 includes
#include <libopencm3/stm32/gpio.h>

// local function includes
#include "gpio.h"

// port definitions
#define SPI3_SCK PC10

int main(void){

	set_pin(RCC_GPIOE, GPIOE, GPIO14);
	
	for (int i = 0; i < 999999999; i++){
		__asm__("nop");
	}

	clear_pin(RCC_GPIOE, GPIOE, GPIO15);

	return 0;
}
