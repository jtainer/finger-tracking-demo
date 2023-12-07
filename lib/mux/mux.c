// 
// Driver for I2C multiplexer
//
// Copyright (c) 2023 Jonathan Tainer
//

// TODO: Pass in handles to I2C and reset pin instead of hardcoding them

#include "main.h"
#include "i2c.h"
#include "mux.h"

#define I2C_MUX_ADDR	112
#define I2C_MUX_TIMEOUT	1000

int I2C_MUX_Init(void) {
	// Hold multiplexer in reset while setting address lines
	HAL_GPIO_WritePin(MUX_RST_GPIO_Port, MUX_RST_Pin, GPIO_PIN_RESET);

	// Overkill but it works
	HAL_Delay(500);

	// Bring multiplexer out of reset
	HAL_GPIO_WritePin(MUX_RST_GPIO_Port, MUX_RST_Pin, GPIO_PIN_SET);

	HAL_Delay(500);

	// All channels are disabled by default
//	return I2C_MUX_Select(0);
	return 0;
}

int I2C_MUX_Select(int ch) {
	uint8_t txdata[1] = { 1 << ch };
	uint8_t rxdata[1] = { 0 };
	HAL_StatusTypeDef res;
	res = HAL_I2C_Master_Transmit(&hi2c1, I2C_MUX_ADDR<<1, txdata, sizeof(txdata), I2C_MUX_TIMEOUT);
	if (res != HAL_OK) {
		return 1;
	}
	res = HAL_I2C_Master_Receive(&hi2c1, I2C_MUX_ADDR<<1, rxdata, sizeof(rxdata), I2C_MUX_TIMEOUT);
	if (res != HAL_OK)
		return 1;
	else if (txdata[0] != rxdata[0])
		return 1;
	else
		return 0;
}

