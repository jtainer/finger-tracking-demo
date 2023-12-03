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

#define IMU_CHANNELS 16
MPU6050_t imu[IMU_CHANNELS] = { 0 };

void setup(void) {
	I2C_MUX_Init();
	I2C_MUX_Select(0);
	while (MPU6050_Init(&hi2c1) == 1);
}

void loop(void) {
	static int screen_on = 0;
	screen_on = !screen_on;
	MPU6050_Read_All(&hi2c1, &imu[0]);
	printf("Ang.x = %d\t\tAng.y = %d\t\tAcc.x = %d\t\tAcc.y = %d\t\tAcc.z = %d\r\n",
		(int)imu[0].KalmanAngleX, (int)imu[0].KalmanAngleY,
		(int)imu[0].Accel_X_RAW, (int)imu[0].Accel_Y_RAW, (int)imu[0].Accel_Z_RAW);
	HAL_Delay(10);
}
