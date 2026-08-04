#include "spi.h"

void spi_init(enum rcc_periph_clken spi_rcc_port, uint32_t spi_gpio_port, uint16_t spi_sck, uint16_t spi_miso, uint16_t spi_mosi, uint32_t spi_bus, uint8_t spi_baud_rate, uint8_t spi_cpol, uint8_t spi_cpha, uint8_t spi_msb, uint16_t spi_data_size){

	// enable clocks for peripheral ports
	rcc_periph_clock_enable(spi_rcc_port);
	rcc_periph_clock_enable(spi_bus);

	// configure sck, miso, and mosi
	gpio_mode_setup(
		spi_gpio_port, 
		GPIO_MODE_AF, 
		GPIO_PUPD_NONE, 
		spi_sck | spi_miso | spi_mosi
	);

	gpio_set_af(
		spi_gpio_port,
		GPIO_AF5,
		spi_sck | spi_miso | spi_mosi
	);
	
	// initialize spi bus in master mode
	(void)spi_init_master(
			spi_bus,
			spi_baud_rate,
			spi_cpol,
			spi_cpha,
			spi_msb
	);

	// enable nss management through software
	spi_enable_software_slave_management(spi_bus);

	// setting nss high is very important, even if gpio is controlled manually this bit needs to be at least set to 1, otherwise the spi peripheral will not send any data out
	spi_set_nss_high(spi_bus);

	spi_set_data_size(spi_bus, spi_data_size);

	// enable the peripheral
	spi_enable(spi_bus);

}


uint8_t spi_transfer(uint32_t spi_bus, uint8_t write_data){

	spi_send(spi_bus, write_data);
	return spi_read(spi_bus);
}

void spi_write_8(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data){

	clear_pin(rcc_port, gpio_port, gpio);
	(void)spi_transfer(spi_bus, write_data);
	set_pin(rcc_port, gpio_port, gpio);
}

uint8_t spi_read_8(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data){

	clear_pin(rcc_port, gpio_port, gpio);
	(void)spi_transfer(spi_bus, write_data);
	uint8_t b1 = spi_transfer(spi_bus, 0x00);
	set_pin(rcc_port, gpio_port, gpio);
	
	return b1;
}

uint16_t spi_read_16(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data){

	clear_pin(rcc_port, gpio_port, gpio);
	(void)spi_transfer(spi_bus, write_data);
	uint8_t b1 = spi_transfer(spi_bus, 0x00);
	uint8_t b2 = spi_transfer(spi_bus, 0x00);
	set_pin(rcc_port, gpio_port, gpio);
	
	return (b1 << 8) | b2;
}


uint32_t spi_read_24(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data){

	clear_pin(rcc_port, gpio_port, gpio);
	(void)spi_transfer(spi_bus, write_data);
	uint8_t b1 = spi_transfer(spi_bus, 0x00);
	uint8_t b2 = spi_transfer(spi_bus, 0x00);
	uint8_t b3 = spi_transfer(spi_bus, 0x00);
	set_pin(rcc_port, gpio_port, gpio);
	
	return (b1 << 16) | (b2 << 8) | b3;
}


uint32_t spi_read_32(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data){

	clear_pin(rcc_port, gpio_port, gpio);
	(void)spi_transfer(spi_bus, write_data);
	uint8_t b1 = spi_transfer(spi_bus, 0x00);
	uint8_t b2 = spi_transfer(spi_bus, 0x00);
	uint8_t b3 = spi_transfer(spi_bus, 0x00);
	uint8_t b4 = spi_transfer(spi_bus, 0x00);
	set_pin(rcc_port, gpio_port, gpio);
	
	return (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
}
