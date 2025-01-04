/*
 * delay.c
 *
 *  Created on: Dec 30, 2024
 *      Author: LAPTOP
 */


#include "delay.h"

// Hệ số AHB (theo xung nhịp hệ thống, đơn vị MHz)
#define AHB_INPUT 72

// Hàm delay với đơn vị micro giây
void delay_us(uint32_t uS) {
    uint32_t ticks = AHB_INPUT * uS; // Tính số xung nhịp cần để đạt được uS
    SysTick->LOAD = ticks;          // Nạp giá trị vào thanh ghi LOAD
    SysTick->VAL = 0;               // Xóa bộ đếm
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Bật SysTick với HCLK làm nguồn

    // Đợi đến khi bộ đếm đếm về 0
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));

    SysTick->CTRL = 0; // Tắt SysTick
}

// Hàm delay với đơn vị milli giây
void delay_ms(uint16_t ms) {
    while (ms-- != 0) {
        delay_us(1000); // Gọi hàm delay micro giây với 1000us = 1ms
    }
}

// Hàm delay với đơn vị giây
void delay_s(uint16_t s) {
    while (s-- != 0) {
        delay_ms(1000); // Gọi hàm delay milli giây với 1000ms = 1s
    }
}
