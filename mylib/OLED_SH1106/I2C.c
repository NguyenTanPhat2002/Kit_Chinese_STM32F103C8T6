/*
 * I2C.c
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#include "I2C.h"
/**************Hàm gửi 1 chuỗi dữ liệu******************/
void I2C_SAND_BUFFER(uint8_t  SlaveAddr,uint8_t  WriteAddr,uint8_t * pBuffer,uint16_t  NumByteToWrite){
	 HAL_I2C_Mem_Write(&hi2c1, SlaveAddr, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToWrite, 1000);
}
/**************Hàm gửi 1 byte dữ liệu******************/
void I2C_SAND_BYTE(uint8_t  SlaveAddr,uint8_t  writeAddr,uint8_t  pBuffer){
	HAL_I2C_Mem_Write(&hi2c1, SlaveAddr, writeAddr, I2C_MEMADD_SIZE_8BIT, &pBuffer, 1, 1000);
}
/**************Hàm đọc 1 chuỗi dữ liệu******************/
void I2C_READ_BUFFER(uint8_t  SlaveAddr,uint8_t  readAddr,uint8_t * pBuffer,uint16_t NumByteToRead){
	HAL_I2C_Mem_Read(&hi2c1, SlaveAddr, readAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToRead, 1000);
}
/**************Hàm đọc 1 byte dữ liệu******************/
uint8_t I2C_READ_BYTE(uint8_t  SlaveAddr,uint8_t  readAddr){
    uint8_t receivedByte;
    HAL_I2C_Mem_Read(&hi2c1, SlaveAddr, readAddr, I2C_MEMADD_SIZE_8BIT, &receivedByte, 1, 1000);
    return receivedByte;
}





