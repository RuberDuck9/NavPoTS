#ifndef MMC5983MA_H
#define MMC5983MA_H

#include "spi.h"

#define MMC5983MA_SPI_BUS hspi3

#define MMC5983MA_CS_GPIO_PORT GPIOD
#define MMC5983MA_CS_PIN GPIO_PIN_4

#define MMC5983MA_READ_BIT 0x80
#define MMC5983MA_WRITE_BIT 0x7F

#define MMC5983MA_XOUT0 0x00
#define MMC5983MA_XOUT1 0x01
#define MMC5983MA_YOUT0 0x02
#define MMC5983MA_YOUT1 0x03
#define MMC5983MA_ZOUT0 0x04
#define MMC5983MA_ZOUT1 0x05
#define MMC5983MA_XYZOUT2 0x06
#define MMC5983MA_TOUT 0x07
#define MMC5983MA_STATUS 0x08
#define MMC5983MA_IC0 0x09
#define MMC5983MA_IC1 0x0A
#define MMC5983MA_IC2 0x0B
#define MMC5983MA_IC3 0x0C
#define MMC5983MA_PRODUCTID 0x2F
#define MMC5983MA_PRODUCTID_VALUE 0x30

typedef struct {
	float ax, ay, az;
} MMC5983MA_Data;

HAL_StatusTypeDef MMC5983MA_ReadRegister(uint8_t REGISTER_ADDRESS, uint8_t *data, uint16_t length);
HAL_StatusTypeDef MMC5983MA_WriteRegister(uint8_t REGISTER_ADDRESS, uint8_t value);
HAL_StatusTypeDef MMC5983MA_Verify(void);
//HAL_StatusTypeDef MMC5983MA_Init(void);
//HAL_StatusTypeDef MMC5983MA_ReadData(MMC5983MA_Data *data);

#endif
