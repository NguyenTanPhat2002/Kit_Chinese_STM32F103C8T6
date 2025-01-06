/*
 * oled0561.h
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#ifndef OLED0561_H_
#define OLED0561_H_

#include "i2c.h"

#define OLED0561_ADD	0x78  // Địa chỉ I2C của OLED (không được sửa đổi)
#define COM				0x00  // Lệnh điều khiển OLED (không được sửa đổi)
#define DAT 			0x40  // Dữ liệu gửi đến OLED (không được sửa đổi)

void OLED0561_Init(void);
void OLED_DISPLAY_ON (void);
void OLED_DISPLAY_OFF (void);
void OLED_DISPLAY_LIT (uint8_t x);
void OLED_DISPLAY_CLEAR(void);
void OLED_DISPLAY_8x16(uint8_t x,uint8_t y,uint16_t w);
void OLED_DISPLAY_8x16_BUFFER(uint8_t row,uint8_t *str);
void INVERSE_OLED_DISPLAY_16x16(uint8_t x,uint8_t y,uint16_t w);
void INVERSE_OLED_DISPLAY_8x16(uint8_t x,
		uint8_t y,
		uint16_t w);
void OLED_DISPLAY_16x16(uint8_t x,uint8_t y,uint16_t w);
void OLED_DISPLAY_PIC1(void);

#endif /* OLED0561_H_ */
