#include "MMC5983MA.h"

#include "stm32h7xx_hal.h"

static inline void MMC5983MA_CS_Low(void)
{
	HAL_GPIO_WritePin(MMC5983MA_CS_GPIO_PORT, MMC5983MA_CS_PIN, GPIO_PIN_RESET);
}

static inline void MMC5983MA_CS_High(void)
{
	HAL_GPIO_WritePin(MMC5983MA_CS_GPIO_PORT, MMC5983MA_CS_PIN, GPIO_PIN_SET);
}

static inline HAL_StatusTypeDef MMC5983MA_ConfigureSpi(void)
{
	MMC5983MA_SPI_BUS.Init.DataSize = SPI_DATASIZE_8BIT;
	MMC5983MA_SPI_BUS.Init.CLKPolarity = SPI_POLARITY_LOW;
	MMC5983MA_SPI_BUS.Init.CLKPhase = SPI_PHASE_1EDGE;
	MMC5983MA_SPI_BUS.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	MMC5983MA_SPI_BUS.Init.FirstBit = SPI_FIRSTBIT_MSB;
	return HAL_SPI_Init(&MMC5983MA_SPI_BUS);
}

HAL_StatusTypeDef MMC5983MA_ReadRegister(uint8_t REGISTER_ADDRESS, uint8_t *data, uint16_t length)
{
	uint8_t tx_address = REGISTER_ADDRESS | MMC5983MA_READ_BIT;
	HAL_StatusTypeDef spi_status;

	spi_status = MMC5983MA_ConfigureSpi();
	if (spi_status != HAL_OK) return spi_status;

	MMC5983MA_CS_Low();

	spi_status = HAL_SPI_Transmit(&MMC5983MA_SPI_BUS, &tx_address, 1, HAL_MAX_DELAY);

	if (spi_status == HAL_OK)
	{
		spi_status = HAL_SPI_Receive(&MMC5983MA_SPI_BUS, data, length, HAL_MAX_DELAY);
	}

	MMC5983MA_CS_High();

	return spi_status;
}

HAL_StatusTypeDef MMC5983MA_WriteRegister(uint8_t REGISTER_ADDRESS, uint8_t value)
{
	uint8_t tx_data[2] = { REGISTER_ADDRESS & MMC5983MA_WRITE_BIT, value };
	HAL_StatusTypeDef spi_status;

	spi_status = MMC5983MA_ConfigureSpi();
	if (spi_status != HAL_OK) return spi_status;

	MMC5983MA_CS_Low();

	spi_status = HAL_SPI_Transmit(&MMC5983MA_SPI_BUS, tx_data, 2, HAL_MAX_DELAY);

	MMC5983MA_CS_High();

	return spi_status;
}

HAL_StatusTypeDef MMC5983MA_Verify(void)
{
	uint8_t chip_id;
	HAL_StatusTypeDef spi_status;

	spi_status = MMC5983MA_ReadRegister(MMC5983MA_PRODUCTID, &chip_id, 1);

	if (spi_status == HAL_OK)
	{
		if (chip_id == MMC5983MA_PRODUCTID_VALUE)
		{
			return HAL_OK;
		}
		else
		{
			return HAL_ERROR;
		}
	}

	return spi_status;
}

//HAL_StatusTypeDef MMC5983MA_Init(void)
//{
//	HAL_StatusTypeDef spi_status;
//
////	spi_status = MMC5983MA_WriteRegister(MMC5983MA_CTRL1_XL, MMC5983MA_CTRL1_XL_VALUE);
////	if (spi_status != HAL_OK) return spi_status;
////
////	spi_status = MMC5983MA_WriteRegister(MMC5983MA_CTRL2_G, MMC5983MA_CTRL2_G_VALUE);
////	if (spi_status != HAL_OK) return spi_status;
////
////	spi_status = MMC5983MA_WriteRegister(MMC5983MA_CTRL3_C, MMC5983MA_CTRL3_C_VALUE);
//
//	return spi_status;
//}
//
//HAL_StatusTypeDef MMC5983MA_ReadData(MMC5983MA_Data *data)
//{
//	uint8_t MMC5983MA_status;
//	uint8_t rx_buffer[14];
//	HAL_StatusTypeDef spi_status;
//	int16_t raw_rx;
//
////	spi_status = MMC5983MA_ReadRegister(MMC5983MA_STATUS_REG, &MMC5983MA_status, 1);
////	if (spi_status != HAL_OK) return spi_status;
////
////	spi_status = MMC5983MA_ReadRegister(MMC5983MA_OUT_TEMP_L, rx_buffer, 14);
////	if (spi_status != HAL_OK) return spi_status;
////
////	if ( (MMC5983MA_status & MMC5983MA_STATUS_REG_TEMP_READY) != 0) // check if there's a new measurement
////	{
////		// 256 LSB/C, 25C offset
////		raw_rx = (int16_t)(rx_buffer[1] << 8 | rx_buffer[0]);
////		data->temp = (raw_rx / 256.0f) + 25.0f;
////	}
////
////	if ( (MMC5983MA_status & MMC5983MA_STATUS_REG_GYRO_READY) != 0)
////	{
////		// +/- 400 dps, sensitivity 140 mdps/LSB
////		raw_rx = (int16_t)(rx_buffer[3] << 8 | rx_buffer[2]);
////		data->gx = raw_rx * 140.0f / 1000.0f;
////		raw_rx = (int16_t)(rx_buffer[5] << 8 | rx_buffer[4]);
////		data->gy = raw_rx * 140.0f / 1000.0f;
////		raw_rx = (int16_t)(rx_buffer[7] << 8 | rx_buffer[6]);
////		data->gz = raw_rx * 140.0f / 1000.0f;
////	}
////
////	if ( (MMC5983MA_status & MMC5983MA_STATUS_REG_ACCEL_READY) != 0)
////	{
////		// +/- 16g, sensitivity 0.488 mg/LSB
////		raw_rx = (int16_t)(rx_buffer[9] << 8 | rx_buffer[8]);
////		data->ax = raw_rx * 0.488f / 1000.0f;
////		raw_rx = (int16_t)(rx_buffer[11] << 8 | rx_buffer[10]);
////		data->ay = raw_rx * 0.488f / 1000.0f;
////		raw_rx = (int16_t)(rx_buffer[13] << 8 | rx_buffer[12]);
////		data->az = raw_rx * 0.488f / 1000.0f;
////	}
//
//	return spi_status;
//}


