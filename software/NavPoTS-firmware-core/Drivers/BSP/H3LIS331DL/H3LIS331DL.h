#ifndef H3LIS331DL_H
#define H3LIS331DL_H

#include "spi.h"

#define H3LIS331DL_SPI_BUS hspi3

#define H3LIS331DL_CS_GPIO_PORT GPIOD
#define H3LIS331DL_CS_PIN GPIO_PIN_3

#define H3LIS331DL_READ_BIT 0x80
#define H3LIS331DL_WRITE_BIT 0x7F

#define H3LIS331DL_WHO_AM_I 0x0F
#define H3LIS331DL_WHO_AM_I_VALUE 0x32

typedef struct {
	float ax, ay, az;
} H3LIS331DL_Data;

HAL_StatusTypeDef H3LIS331DL_ReadRegister(uint8_t REGISTER_ADDRESS, uint8_t *data, uint16_t length);
HAL_StatusTypeDef H3LIS331DL_WriteRegister(uint8_t REGISTER_ADDRESS, uint8_t value);
HAL_StatusTypeDef H3LIS331DL_Verify(void);
//HAL_StatusTypeDef H3LIS331DL_Init(void);
//HAL_StatusTypeDef H3LIS331DL_ReadData(H3LIS331DL_Data *data);

#endif
