/*
 * delay.h
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */

#ifndef DELAY_H_
#define DELAY_H_


#include "stm32f1xx_hal.h"

// Prototype của các hàm delay
void delay_s(uint16_t s);       // Hàm delay với đơn vị giây
void delay_ms(uint16_t ms);     // Hàm delay với đơn vị milli giây
void delay_us(uint32_t us);     // Hàm delay với đơn vị micro giây



#endif /* DELAY_H_ */
