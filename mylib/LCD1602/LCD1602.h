/*
 * LCD1602.h
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */

#ifndef LCD1602_H_
#define LCD1602_H_

#include "main.h"

/************** Định nghĩa chân GPIO *******************/
#define LCD_RS_PORT  GPIOA
#define LCD_RS_PIN   GPIO_PIN_9

#define LCD_RW_PORT  GPIOA
#define LCD_RW_PIN   GPIO_PIN_8

#define LCD_EN_PORT  GPIOA
#define LCD_EN_PIN   GPIO_PIN_7

#define LCD_D4_PORT  GPIOA
#define LCD_D4_PIN   GPIO_PIN_4

#define LCD_D5_PORT  GPIOA
#define LCD_D5_PIN   GPIO_PIN_3

#define LCD_D6_PORT  GPIOA
#define LCD_D6_PIN   GPIO_PIN_2

#define LCD_D7_PORT  GPIOA
#define LCD_D7_PIN   GPIO_PIN_1

/***********Khai báo hàm***********************/
void LCD_Init(void);
void LCD_Clear(void);
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar(unsigned char Data);
void LCD_Puts(char *s);

#endif /* LCD1602_H_ */
