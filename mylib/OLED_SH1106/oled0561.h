/*
 * oled0561.h
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#ifndef OLED0561_H_
#define OLED0561_H_

#include "i2c.h"

#define OLED0561_ADD	0x78  // OLED的I2C地址（禁止修改）
#define COM				0x00  // OLED 指令（禁止修改）
#define DAT 			0x40  // OLED 数据（禁止修改）

void OLED0561_Init(void);//初始化
void OLED_DISPLAY_ON (void);//OLED屏开显示
void OLED_DISPLAY_OFF (void);//OLED屏关显示
void OLED_DISPLAY_LIT (uint8_t x);//OLED屏亮度设置（0~255）
void OLED_DISPLAY_CLEAR(void);//清屏操作
void OLED_DISPLAY_8x16(uint8_t x,uint8_t y,uint16_t w);//显示8x16的单个字符
void OLED_DISPLAY_8x16_BUFFER(uint8_t row,uint8_t *str);//显示8x16的字符串
void INVERSE_OLED_DISPLAY_16x16(uint8_t x,uint8_t y,uint16_t w); //反显示汉子
void INVERSE_OLED_DISPLAY_8x16(uint8_t x, //显示汉字的页坐标（从0到7）（此处不可修改）
		uint8_t y, //显示汉字的列坐标（从0到128）
		uint16_t w);
void OLED_DISPLAY_16x16(uint8_t x,uint8_t y,uint16_t w); //汉字显示
void OLED_DISPLAY_PIC1(void);//图片显示

#endif /* OLED0561_H_ */
