/*
 * I2C.h
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#ifndef I2C_H_
#define I2C_H_
#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
void I2C_SAND_BUFFER(uint8_t  SlaveAddr,uint8_t  WriteAddr,uint8_t * pBuffer,uint16_t  NumByteToWrite);
void I2C_SAND_BYTE(uint8_t  SlaveAddr,uint8_t  writeAddr,uint8_t  pBuffer);
void I2C_READ_BUFFER(uint8_t  SlaveAddr,uint8_t  readAddr,uint8_t * pBuffer,uint16_t NumByteToRead);
uint8_t I2C_READ_BYTE(uint8_t  SlaveAddr,uint8_t  readAddr);


#endif /* I2C_H_ */
