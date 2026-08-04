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
 * SPI3_CS0 - PD0 - MS5611 Barometer
 * SPI3_CS1 - PD1 - ASM330LHHXTR IMU
 * SPI3_CS2 - PD3 - H3LIS331DLTR ACCEL
 * SPI3_CS3 - PD4 - MMC5983MA MAG
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

// local header includes
#include "gpio.h"
#include "usart.h"
#include "clock.h"
#include "delay.h"
#include "spi.h"

// port definitions
#define SPI3_SCK PC10

int main(void){

	//configure_system_clock();
	configure_systick();

	usart_init(RCC_GPIOB, RCC_USART3, GPIOB, GPIO11, GPIO10, USART3, 9600, USART_MODE_TX);

	spi_init(RCC_GPIOC, GPIOC, GPIO10, GPIO11, GPIO12, SPI3, SPI_CR1_BAUDRATE_FPCLK_DIV_32, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_MSBFIRST, SPI_CR2_DS_8BIT);
	volatile uint8_t chip_id = 0;
	
	while (1){
		usart_println(USART3, "Hello World!");

		set_pin(RCC_GPIOE, GPIOE, GPIO15);
		delay(200);

		clear_pin(RCC_GPIOE, GPIOE, GPIO15);
		delay(200);

		chip_id = spi_read_8(SPI3, RCC_GPIOD, GPIOD, GPIO1, 0x80);
	}

	return 0;
}
