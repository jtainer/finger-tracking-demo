// 
// Entry point for user code
// 'setup' is called once after device reset
// 'loop' is called repeatedly
//
// Copyright (c) 2023 Jonathan Tainer
//

#include <stdio.h>
#include "main.h"
#include "mux.h"
#include "mpu6050.h"

#define IMU_CHANNELS 3
MPU6050_t imu[IMU_CHANNELS] = { 0 };

void setup(void) {

	printf("Initializing I2C multiplexer...");
	int err = I2C_MUX_Init();
	if (!err) {
		printf(" Success!\r\n");
	}
	else {
		printf( "Failed\r\n");
		Error_Handler();
	}

	// On breadboard setup, IMUs are connected to mux channels 1-3
	for (int i = 0; i < IMU_CHANNELS; i++) {
		printf("Initializing IMU[%d]...", i);
		I2C_MUX_Select(i+1);
		err = MPU6050_Init(&hi2c1);
		if (!err) {
			printf(" Success!\r\n");
		}
		else {
			printf(" Failed\r\n");
			Error_Handler();
		}
	}
}

void loop(void) {
	for (int i = 0; i < IMU_CHANNELS; i++) {
//		I2C_MUX_Select(i+1);
		uint8_t data[1] = { 2<<i };
		HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(&hi2c1, 112<<1, data, sizeof(data), 1000);
		if (res == HAL_OK)
			printf("Received ACK from multiplexer\r\n");
		else
			printf("No response from multiplexer\r\n");
		HAL_Delay(500);
		MPU6050_Read_All(&hi2c1, &imu[i]);
		printf("IMU[%d]: x = %f\ty = %f\r\n",
			i, imu[i].KalmanAngleX, imu[i].KalmanAngleY);
	}
//	HAL_Delay(500);
}
