/*
 * TM1640.h
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */

#ifndef TM1640_H_
#define TM1640_H_

#include "stm32f1xx_hal.h"

// Định nghĩa GPIO port và các chân
#define TM1640_GPIOPORT    GPIOA       // Cổng GPIO
#define TM1640_DIN         GPIO_PIN_12 // Chân dữ liệu đầu vào
#define TM1640_SCLK        GPIO_PIN_11 // Chân xung clock

#define TM1640_LEDPORT     0xC8        // Địa chỉ cổng LED cho TM1640

// Khai báo các hàm
void TM1640_Init(void);                        // Khởi tạo TM1640
void TM1640_led(uint8_t data);                // Điều khiển trạng thái LED
void TM1640_display(uint8_t address, uint8_t data); // Hiển thị dữ liệu tại địa chỉ cụ thể
void TM1640_display_add(uint8_t address, uint8_t *data); // Hiển thị dữ liệu với địa chỉ tự động tăng

#endif /* TM1640_H_ */

