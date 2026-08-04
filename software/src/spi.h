#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

#include <stdint.h>

#include "gpio.h"

#ifndef spi_h
#define spi_h

void spi_init(enum rcc_periph_clken spi_rcc_port, uint32_t spi_gpio_port, uint16_t spi_sck, uint16_t spi_miso, uint16_t spi_mosi, uint32_t spi_bus, uint8_t spi_baud_rate, uint8_t spi_cpol, uint8_t spi_cpha, uint8_t spi_msb, uint16_t spi_data_size);
uint8_t spi_transfer(uint32_t spi_bus, uint8_t write_data);
void spi_write_8(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data);
uint8_t spi_read_8(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data);
uint16_t spi_read_16(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data);
uint32_t spi_read_24(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data);
uint32_t spi_read_32(uint32_t spi_bus, enum rcc_periph_clken rcc_port, uint32_t gpio_port, uint16_t gpio, uint8_t write_data);

#endif
