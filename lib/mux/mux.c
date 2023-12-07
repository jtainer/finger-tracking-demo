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

	// Set bottom 3 bits of slave address
//	HAL_GPIO_WritePin(MUX_AD0_GPIO_Port, MUX_AD0_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(MUX_AD1_GPIO_Port, MUX_AD1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(MUX_AD2_GPIO_Port, MUX_AD2_Pin, GPIO_PIN_RESET);

	HAL_Delay(500);

	// Bring multiplexer out of reset
	HAL_GPIO_WritePin(MUX_RST_GPIO_Port, MUX_RST_Pin, GPIO_PIN_SET);

	HAL_Delay(500);

	// All channels are disabled by defaultq
//	return I2C_MUX_Select(0);
	return 0;
}

int I2C_MUX_Select(int ch) {
	uint8_t data[1] = { 1 << ch };
	HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(&hi2c1, I2C_MUX_ADDR<<1, data, sizeof(data), I2C_MUX_TIMEOUT);
	if (res == HAL_OK) {
		HAL_Delay(100);
		return 0;
	}
	else {
		return 1;
	}
}

