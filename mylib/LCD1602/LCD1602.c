/*
 * LCD1602.c
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */


/*
 * lcd1602.c
 *
 *  Created on: Dec 29, 2024
 *      Author: LAPTOP
 */

#include "lcd1602.h"

// Internal helper functions
static void LCD_Enable(void);
static void LCD_Send4Bit(unsigned char Data);
static void LCD_SendCommand(unsigned char command);

// Internal helper to control pins
static void LCD_SetPin(GPIO_TypeDef *PORT, uint16_t PIN, GPIO_PinState STATE) {
    HAL_GPIO_WritePin(PORT, PIN, STATE);
}

// Pulse the enable pin to latch data
static void LCD_Enable(void) {
    LCD_SetPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);  // Short delay to meet timing requirements
    LCD_SetPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// Send 4-bit data to LCD
static void LCD_Send4Bit(unsigned char Data) {
    LCD_SetPin(LCD_D4_PORT, LCD_D4_PIN, (Data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SetPin(LCD_D5_PORT, LCD_D5_PIN, (Data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SetPin(LCD_D6_PORT, LCD_D6_PIN, (Data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SetPin(LCD_D7_PORT, LCD_D7_PIN, (Data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Send a command to the LCD
static void LCD_SendCommand(unsigned char command) {
    LCD_Send4Bit(command >> 4);  // Send higher nibble
    LCD_Enable();
    LCD_Send4Bit(command);       // Send lower nibble
    LCD_Enable();
}

// Clear the LCD screen
void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);  // LCD needs some time to clear
}

// Initialize the LCD in 4-bit mode
void LCD_Init(void) {
    HAL_Delay(20);  // Wait for LCD power-on initialization
    LCD_SetPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
    LCD_SetPin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);

    LCD_Send4Bit(0x03);  // Initialize in 4-bit mode
    LCD_Enable();
    HAL_Delay(5);
    LCD_Enable();
    HAL_Delay(1);
    LCD_Enable();
    LCD_Send4Bit(0x02);  // Set LCD to 4-bit mode
    LCD_Enable();

    LCD_SendCommand(0x28);  // Function set: 4-bit, 2-line, 5x8 dots
    LCD_SendCommand(0x0C);  // Display ON, Cursor OFF, Blink OFF
    LCD_SendCommand(0x06);  // Entry mode set: Increment cursor
    LCD_SendCommand(0x01);  // Clear display
}

// Move cursor to a specific position
void LCD_Gotoxy(unsigned char x, unsigned char y) {
    unsigned char address;
    if (y == 0) address = 0x80 + x;  // First line
    else address = 0xC0 + x;         // Second line
    LCD_SendCommand(address);
}

// Send a character to the LCD
void LCD_PutChar(unsigned char Data) {
    LCD_SetPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);
    LCD_SendCommand(Data);
    LCD_SetPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
}

// Send a string to the LCD
void LCD_Puts(char *s) {
    while (*s) {
        LCD_PutChar(*s++);
    }
}
