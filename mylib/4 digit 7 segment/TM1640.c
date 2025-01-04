/*
 * TM1640.c
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */


#include "TM1640.h"
#include "delay.h"

#define DEL  1   // Tốc độ truyền dữ liệu (tăng giá trị nếu gặp vấn đề giao tiếp)

// Địa chỉ chế độ
#define TM1640MEDO_ADD  0x40   // Chế độ tự động tăng địa chỉ
// #define TM1640MEDO_ADD  0x44   // Chế độ cố định địa chỉ (khuyến nghị)

// Điều chỉnh độ sáng hiển thị
// #define TM1640MEDO_DISPLAY  0x88   // Độ sáng tối thiểu
// #define TM1640MEDO_DISPLAY  0x89   // Độ sáng thấp
// #define TM1640MEDO_DISPLAY  0x8a   // Độ sáng trung bình thấp
// #define TM1640MEDO_DISPLAY  0x8b   // Độ sáng trung bình cao
#define TM1640MEDO_DISPLAY  0x8c   // Độ sáng (khuyến nghị)
// #define TM1640MEDO_DISPLAY  0x8d   // Độ sáng cao
// #define TM1640MEDO_DISPLAY  0x8f   // Độ sáng tối đa

#define TM1640MEDO_DISPLAY_OFF  0x80   // Tắt hiển thị

void TM1640_start() {
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_SET);
    delay_us(DEL);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_RESET);
    delay_us(DEL);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_RESET);
    delay_us(DEL);
}

void TM1640_stop() {
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_SET);
    delay_us(DEL);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_SET);
    delay_us(DEL);
}

void TM1640_write(uint8_t data) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_RESET);
        delay_us(DEL);

        if (data & 0x01) {
            HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_RESET);
        }
        delay_us(DEL);
        HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_SET);
        delay_us(DEL);

        data >>= 1;
    }
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_RESET);
}

void TM1640_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Kích hoạt clock cho GPIO
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Cấu hình các chân TM1640 làm Output
    GPIO_InitStruct.Pin = TM1640_DIN | TM1640_SCLK;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStruct);

    // Đặt trạng thái mặc định cho các chân
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_DIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TM1640_GPIOPORT, TM1640_SCLK, GPIO_PIN_SET);

    TM1640_start();
    TM1640_write(TM1640MEDO_ADD);  // Thiết lập chế độ địa chỉ
    TM1640_stop();

    TM1640_start();
    TM1640_write(TM1640MEDO_DISPLAY);  // Bật hiển thị với độ sáng đã chọn
    TM1640_stop();
}

void TM1640_led(uint8_t data) {
    TM1640_start();
    TM1640_write(TM1640_LEDPORT);  // Gửi địa chỉ hiển thị
    TM1640_write(data);            // Gửi dữ liệu hiển thị
    TM1640_stop();
}

void TM1640_display(uint8_t address, uint8_t data) {
    const uint8_t buff[21] = {
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
        0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef, 0x00
    };

    TM1640_start();
    TM1640_write(0xC0 + address);  // Gửi địa chỉ hiển thị
    TM1640_write(buff[data]);      // Gửi dữ liệu hiển thị
    TM1640_stop();
}

void TM1640_display_add(uint8_t address, uint8_t *data) {
    uint8_t i;
    const uint8_t buff[21] = {
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
        0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef, 0x00
    };

    TM1640_start();
    TM1640_write(0xC0 + address);  // Gửi địa chỉ bắt đầu
    for (i = 0; i < 8; i++) {
        TM1640_write(buff[data[i]]);
    }
    TM1640_stop();
}
