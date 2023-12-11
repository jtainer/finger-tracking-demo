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

	for (int i = 0; i < IMU_CHANNELS; i++) {
		printf("Initializing IMU[%d]...", i);
		I2C_MUX_Select(i);
		err = MPU6050_Init(&hi2c1, &imu[i]);
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
		int err = I2C_MUX_Select(i);
		if (!err)
			printf("Switched to channel %d\r\n", i);
		else
			printf("Failed to switch channel\r\n");
		MPU6050_Read_All(&hi2c1, &imu[i]);
		printf("IMU[%d]: x = %f\ty = %f\r\n",
			i, imu[i].KalmanAngleX, imu[i].KalmanAngleY);
	}
	HAL_Delay(20);
}
