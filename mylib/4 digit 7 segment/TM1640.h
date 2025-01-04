/*
 * TM1640.h
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */

#ifndef TM1640_H_
#define TM1640_H_

#include "stm32f1xx_hal.h"

// GPIO port and pins definition
#define TM1640_GPIOPORT    GPIOA       // GPIO port
#define TM1640_DIN         GPIO_PIN_12 // Data input pin
#define TM1640_SCLK        GPIO_PIN_11 // Clock pin

#define TM1640_LEDPORT     0xC8        // LED port address for TM1640

// Function declarations
void TM1640_Init(void);                        // Initialize TM1640
void TM1640_led(uint8_t data);                // Control LED state
void TM1640_display(uint8_t address, uint8_t data); // Display data at specific address
void TM1640_display_add(uint8_t address, uint8_t *data); // Display data with auto-increment address




#endif /* TM1640_H_ */
