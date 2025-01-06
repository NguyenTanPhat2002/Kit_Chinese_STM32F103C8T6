/*
 * button.h
 *
 *  Created on: Dec 11, 2024
 *      Author: LAPTOP
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

typedef struct{
	uint8_t button_current;
	uint8_t button_last;
	uint8_t button_fliter ;
	uint8_t is_debouncing;
	uint32_t time_debounce;
	uint32_t time_start_press;
	uint8_t is_press_timeout;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_Typedef_t;


void button_handle(Button_Typedef_t *ButtonX);
void Button_Init(Button_Typedef_t *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* BUTTON_H_ */
