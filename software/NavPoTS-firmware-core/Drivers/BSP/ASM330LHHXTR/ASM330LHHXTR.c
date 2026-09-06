#include "stm32h7xx_hal.h"
#include "ASM330LHHXTR.h"

static inline void ASM330LHHXTR_CS_Low(void)
{
	HAL_GPIO_WritePin(ASM330LHHXTR_CS_GPIO_PORT, ASM330LHHXTR_CS_PIN, GPIO_PIN_RESET);
}

static inline void ASM330LHHXTR_CS_High(void)
{
	HAL_GPIO_WritePin(ASM330LHHXTR_CS_GPIO_PORT, ASM330LHHXTR_CS_PIN, GPIO_PIN_SET);
}

HAL_StatusTypeDef ASM330LHHXTR_ReadRegister(uint8_t REGISTER_ADDRESS, uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef spi_status;
	uint8_t tx_address = REGISTER_ADDRESS | ASM330LHHXTR_READ_BIT;

	ASM330LHHXTR_CS_Low();

	spi_status = HAL_SPI_Transmit(&hspi3, &tx_address, 1, HAL_MAX_DELAY);
	if (spi_status == HAL_OK)
	{
		spi_status = HAL_SPI_Receive(&hspi3, data, length, HAL_MAX_DELAY);
	}

	ASM330LHHXTR_CS_High();

	return spi_status;
}

HAL_StatusTypeDef ASM330LHXXTR_Verify(void)
{
	uint8_t chip_id;
	HAL_StatusTypeDef chip_status = ASM330LHHXTR_ReadRegister(ASM330LHHXTR_WHO_AM_I_REGISTER, &chip_id, 1);

	if (chip_status == HAL_OK)
	{
		if (chip_id == ASM330LHHXTR_WHO_AM_I_VALUE)
		{
			return HAL_OK;
		}
		else
		{
			return HAL_ERROR;
		}
	}

	return chip_status;
}



