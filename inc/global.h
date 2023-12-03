/*
 * global.h
 *
 *  Created on: Dec 3, 2023
 *      Author: jtain
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stm32f4xx_hal.h"

#ifndef MUX_RST_Pin
#define MUX_RST_Pin GPIO_PIN_5
#endif

#ifndef MUX_RST_GPIO_Port
#define MUX_RST_GPIO_Port GPIOB
#endif

extern I2C_HandleTypeDef hi2c1;

#endif /* INC_GLOBAL_H_ */
