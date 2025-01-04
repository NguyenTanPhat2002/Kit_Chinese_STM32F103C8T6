/*
 * Lm75A.c
 *
 *  Created on: Jan 1, 2025
 *      Author: LAPTOP
 */


#include "Lm75A.h"

float readTemperature() {
    uint8_t buffer[2];  // Bộ đệm nhận dữ liệu
    int16_t rawTemp;
    float temperature;

    // Doc 2 byte từ thanh ghi địa chỉ 0x00
    HAL_I2C_Mem_Read(&hi2c1, LM75A_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, buffer, 2, HAL_MAX_DELAY);

    // Kết hợp 2 byte thành giá trị nhiệt độ
    rawTemp = (buffer[0] << 8) | buffer[1];  // Ghép MSB và LSB
    rawTemp >>= 5;  // Chuyển đổi thành dữ liệu 11 bit (0.125°C mỗi bước)

    // Xử lý dữ liệu âm hoặc dương
    if (rawTemp & 0x0400) {  // Kiểm tra bit dấu D10
        rawTemp |= 0xF800;  // Chuyển sang dạng bù 2
    }

    temperature = rawTemp * 0.125;  // Nhân với độ phân giải 0.125°C
    return temperature;
}
