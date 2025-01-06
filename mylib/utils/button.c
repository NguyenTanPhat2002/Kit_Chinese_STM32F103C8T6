/*
 * button.c
 *
 *  Created on: Dec 11, 2024
 *      Author: LAPTOP
 */


#include "button.h"


__weak void btn_pressing_callback(Button_Typedef_t *ButtonX)
{

}
__weak void btn_release_callback(Button_Typedef_t *ButtonX)
{

}

__weak void btn_press_short_callback(Button_Typedef_t *ButtonX) // nhan nha nhanh ra
{

}

__weak void btn_pressing_timeout_callback(Button_Typedef_t *ButtonX)
{

}
void button_handle(Button_Typedef_t *ButtonX)
{
	// -------------loc nhieu-------------
	uint8_t sta = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	if(sta != ButtonX -> button_fliter)
	{
		ButtonX->button_fliter = sta;
		ButtonX->is_debouncing = 1;
		ButtonX->time_debounce = HAL_GetTick();
	}
	//-------------tin hieu da xac lap--------
	if(ButtonX->is_debouncing && (HAL_GetTick() - ButtonX->time_debounce >=15))
	{
		ButtonX->button_current = ButtonX->button_fliter;
		ButtonX->is_debouncing =0;
	}

	//--------xu li---------
	if(ButtonX->button_current != ButtonX->button_last)
	{
		if(ButtonX->button_current ==0) // nhan xuong
		{
			ButtonX->is_press_timeout =1;
			btn_pressing_callback(ButtonX);
			ButtonX->time_start_press = HAL_GetTick();
		}
		else // nha ra
		{
			if(HAL_GetTick() - ButtonX->time_start_press <= 3000)
			{
				btn_press_short_callback(ButtonX);
			}
			ButtonX->is_press_timeout =0;
			btn_release_callback(ButtonX);
		}
		ButtonX->button_current = ButtonX->button_last;

	}
	//----------nhan giu---------
	if(ButtonX->is_press_timeout && (HAL_GetTick() - ButtonX->time_start_press >= 3000))
	{
		btn_pressing_timeout_callback(ButtonX);
		ButtonX->is_press_timeout =0;
	}
}

void Button_Init(Button_Typedef_t *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
}
