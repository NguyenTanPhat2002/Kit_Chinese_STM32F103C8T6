/*
 * I2C.c
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#include "I2C.h"

void I2C_SAND_BUFFER(uint8_t  SlaveAddr,uint8_t  WriteAddr,uint8_t * pBuffer,uint16_t  NumByteToWrite){ //I2C发送数据串（器件地址，寄存器，内部地址，数量）
	 HAL_I2C_Mem_Write(&hi2c1, SlaveAddr, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToWrite, 1000);
}
void I2C_SAND_BYTE(uint8_t  SlaveAddr,uint8_t  writeAddr,uint8_t  pBuffer){ //I2C发送一个字节（从地址，内部地址，内容）
	HAL_I2C_Mem_Write(&hi2c1, SlaveAddr, writeAddr, I2C_MEMADD_SIZE_8BIT, &pBuffer, 1, 1000);
}
void I2C_READ_BUFFER(uint8_t  SlaveAddr,uint8_t  readAddr,uint8_t * pBuffer,uint16_t NumByteToRead){ //I2C读取数据串（器件地址，寄存器，内部地址，数量）
	HAL_I2C_Mem_Read(&hi2c1, SlaveAddr, readAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToRead, 1000);
}
uint8_t I2C_READ_BYTE(uint8_t  SlaveAddr,uint8_t  readAddr){ //I2C读取一个字节
    uint8_t receivedByte;
    HAL_I2C_Mem_Read(&hi2c1, SlaveAddr, readAddr, I2C_MEMADD_SIZE_8BIT, &receivedByte, 1, 1000);
    return receivedByte;
}



/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT
*********************************************************************************************/


