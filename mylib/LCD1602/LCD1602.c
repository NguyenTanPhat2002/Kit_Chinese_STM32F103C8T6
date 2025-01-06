/*
 * LCD1602.c
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */

#include "lcd1602.h"

// Các hàm nội bộ trợ giúp
static void LCD_Enable(void); // Kích xung để chốt dữ liệu
static void LCD_Send4Bit(unsigned char Data); // Gửi 4 bit dữ liệu đến LCD
static void LCD_SendCommand(unsigned char command); // Gửi lệnh điều khiển LCD

// Hàm nội bộ để điều khiển các chân GPIO
static void LCD_SetPin(GPIO_TypeDef *PORT, uint16_t PIN, GPIO_PinState STATE) {
    HAL_GPIO_WritePin(PORT, PIN, STATE);
}

// Kích xung chân Enable để chốt dữ liệu
static void LCD_Enable(void) {
    LCD_SetPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);  // Trễ ngắn để đáp ứng yêu cầu thời gian
    LCD_SetPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// Gửi dữ liệu 4 bit đến LCD
static void LCD_Send4Bit(unsigned char Data) {
    LCD_SetPin(LCD_D4_PORT, LCD_D4_PIN, (Data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SetPin(LCD_D5_PORT, LCD_D5_PIN, (Data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SetPin(LCD_D6_PORT, LCD_D6_PIN, (Data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SetPin(LCD_D7_PORT, LCD_D7_PIN, (Data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Gửi lệnh điều khiển đến LCD
static void LCD_SendCommand(unsigned char command) {
    LCD_Send4Bit(command >> 4);  // Gửi nibble cao (4 bit cao)
    LCD_Enable();
    LCD_Send4Bit(command);       // Gửi nibble thấp (4 bit thấp)
    LCD_Enable();
}

// Xóa màn hình LCD
void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);  // LCD cần thời gian để hoàn tất việc xóa
}

// Khởi tạo LCD ở chế độ 4-bit
void LCD_Init(void) {
    HAL_Delay(20);  // Đợi LCD khởi động sau khi bật nguồn
    LCD_SetPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
    LCD_SetPin(LCD_RW_PORT, LCD_RW_PIN, GPIO_PIN_RESET);

    LCD_Send4Bit(0x03);  // Khởi tạo LCD ở chế độ 4-bit
    LCD_Enable();
    HAL_Delay(5);
    LCD_Enable();
    HAL_Delay(1);
    LCD_Enable();
    LCD_Send4Bit(0x02);  // Thiết lập chế độ 4-bit cho LCD
    LCD_Enable();

    LCD_SendCommand(0x28);  // Thiết lập chức năng: 4-bit, 2 dòng, 5x8 điểm
    LCD_SendCommand(0x0C);  // Bật hiển thị, tắt con trỏ, không nhấp nháy
    LCD_SendCommand(0x06);  // Chế độ nhập: Tăng con trỏ
    LCD_SendCommand(0x01);  // Xóa màn hình
}

// Di chuyển con trỏ đến vị trí cụ thể
void LCD_Gotoxy(unsigned char x, unsigned char y) {
    unsigned char address;
    if (y == 0) address = 0x80 + x;  // Dòng đầu tiên
    else address = 0xC0 + x;         // Dòng thứ hai
    LCD_SendCommand(address);
}

// Gửi một ký tự đến LCD
void LCD_PutChar(unsigned char Data) {
    LCD_SetPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);
    LCD_SendCommand(Data);
    LCD_SetPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
}

// Gửi một chuỗi ký tự đến LCD
void LCD_Puts(char *s) {
    while (*s) {
        LCD_PutChar(*s++);
    }
}
