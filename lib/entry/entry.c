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
	I2C_MUX_Init();

	// On breadboard setup, IMUs are connected to mux channels 1-3
	for (int i = 0; i < IMU_CHANNELS; i++) {
		printf("Initializing IMU[%d]...", i);
		I2C_MUX_Select(i);
		while (MPU6050_Init(&hi2c1) == 1);
		printf(" Success!\r\n");
	}
}

void loop(void) {
	for (int i = 0; i < IMU_CHANNELS; i++) {
		I2C_MUX_Select(i+1);
		MPU6050_Read_All(&hi2c1, &imu[i]);
		printf("IMU[%d]: x = %d\ty = %d\r\n", i, (int)imu[i].KalmanAngleX, (int)imu[i].KalmanAngleY);
	}
	HAL_Delay(100);
}
