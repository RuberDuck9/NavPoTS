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

static inline HAL_StatusTypeDef ASM330LHHXTR_ConfigureSpi(void)
{
	ASM330LHHXTR_SPI_BUS.Init.DataSize = SPI_DATASIZE_8BIT;
	ASM330LHHXTR_SPI_BUS.Init.CLKPolarity = SPI_POLARITY_HIGH;
	ASM330LHHXTR_SPI_BUS.Init.CLKPhase = SPI_PHASE_2EDGE;
	ASM330LHHXTR_SPI_BUS.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	ASM330LHHXTR_SPI_BUS.Init.FirstBit = SPI_FIRSTBIT_MSB;
	return HAL_SPI_Init(&ASM330LHHXTR_SPI_BUS);
}

HAL_StatusTypeDef ASM330LHHXTR_ReadRegister(uint8_t REGISTER_ADDRESS, uint8_t *data, uint16_t length)
{
	uint8_t tx_address = REGISTER_ADDRESS | ASM330LHHXTR_READ_BIT;

	HAL_StatusTypeDef spi_status;

	spi_status = ASM330LHHXTR_ConfigureSpi();

	ASM330LHHXTR_CS_Low();

	if (spi_status == HAL_OK)
	{
		spi_status = HAL_SPI_Transmit(&hspi3, &tx_address, 1, HAL_MAX_DELAY);
	}
	else
	{
		return spi_status;
	}

	if (spi_status == HAL_OK)
	{
		spi_status = HAL_SPI_Receive(&hspi3, data, length, HAL_MAX_DELAY);
	}
	else
	{
		return spi_status;
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



