/*
 * Lm75A.h
 *
 *  Created on: Jan 1, 2025
 *      Author: LAPTOP
 */

#ifndef LM75A_H_
#define LM75A_H_

#include "stm32f1xx_hal.h"

#define LM75A_ADDRESS (0x4F<<1) // A0, A1, A2 nối VCC
extern I2C_HandleTypeDef hi2c1;
float readTemperature(void);

#endif /* LM75A_H_ */
