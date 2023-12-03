// 
// Driver for I2C multiplexer
//
// Copyright (c) 2023 Jonathan Tainer
//

#include "main.h"
#include "i2c.h"
#include "mux.h"

#define I2C_MUX_ADDR	112
#define I2C_MUX_TIMEOUT	10

void I2C_MUX_Init(void) {
	// Hold multiplexer in reset while setting address lines
	HAL_GPIO_WritePin(MUX_RST_GPIO_Port, MUX_RST_Pin, GPIO_PIN_RESET);

	// Set bottom 3 bits of slave address
	HAL_GPIO_WritePin(MUX_AD0_GPIO_Port, MUX_AD0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MUX_AD1_GPIO_Port, MUX_AD1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MUX_AD2_GPIO_Port, MUX_AD2_Pin, GPIO_PIN_RESET);

	// Bring multiplexer out of reset
	HAL_GPIO_WritePin(MUX_RST_GPIO_Port, MUX_RST_Pin, GPIO_PIN_SET);

	// All channels are disabled by defaultq
	I2C_MUX_Select(-1);
}

void I2C_MUX_Select(int ch) {
	uint8_t data[] = { 1 << ch };
	HAL_I2C_Master_Transmit(&hi2c1, I2C_MUX_ADDR, data, sizeof(data), I2C_MUX_TIMEOUT);
}

