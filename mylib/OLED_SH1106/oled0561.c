/*
 * oled0561.c
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#include "oled0561.h"
#include "ASCII_8x16.h" //Đưa vào font chữ ASCII

#include "CHS_16x16.h" //Data tiếng Trung
#include "PIC1.h" //Data hình ảnh

/*****************Khởi tạo Oled*************************/
void OLED0561_Init (void){
	OLED_DISPLAY_OFF(); //tắt màn hình
	OLED_DISPLAY_CLEAR(); //xóa màn hình
	OLED_DISPLAY_ON(); //Bật màn hình và cấu hình ban đầu
}
/****************Cấu hình OLED và bật màn hình***********/
void OLED_DISPLAY_ON (void){ // Cấu hình ban đầu và bật màn hình OLED
	uint8_t buf[28]={
	0xae,// 0xae: tắt hiển thị, 0xaf: bật hiển thị
    0x00,0x10,// Địa chỉ bắt đầu (2 byte)
	0xd5,0x80,// Tần số xung hiển thị
	0xa8,0x3f,// Tỷ lệ nhân
	0xd3,0x00,// Độ lệch hiển thị
	0XB0,// Địa chỉ trang ghi (0xB0~7)
	0x40,// Dòng bắt đầu hiển thị
	0x8d,0x14,// Điện áp VCC
	0xa1,// Thiết lập phân đoạn ánh xạ lại
	0xc8,// Chế độ đầu ra COM
	0xda,0x12,// Cấu hình đầu ra COM
	0x81,0xff,// Độ tương phản, lệnh: 0x81, dữ liệu: 0~255 (255 là cao nhất)
	0xd9,0xf1,// Chu kỳ sạc
	0xdb,0x30,// Điện áp đầu ra VCC
	0x20,0x00,// Thiết lập tìm kiếm ngang
	0xa4,// 0xa4: hiển thị bình thường, 0xa5: hiển thị tất cả điểm
	0xa6,// 0xa6: hiển thị bình thường, 0xa7: hiển thị đảo ngược
	0xaf// 0xae: tắt hiển thị, 0xaf: bật hiển thị
	}; //
	I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,28);
}
/****************Tắt màn hình OLED*************************/
void OLED_DISPLAY_OFF (void){
	uint8_t buf[3]={
		0xae,// 0xae: tắt hiển thị, 0xaf: bật hiển thị
		0x8d,0x10,// Điện áp VCC
	};
	I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,3);
}
void OLED_DISPLAY_LIT (uint8_t x){// Thiết lập độ sáng màn hình OLED (0~255)
	I2C_SAND_BYTE(OLED0561_ADD,COM,0x81);
	I2C_SAND_BYTE(OLED0561_ADD,COM,x);// Giá trị độ sáng
}
void OLED_DISPLAY_CLEAR(void){ // Xóa nội dung màn hình
	uint8_t j,t;
	for(t=0xB0;t<0xB8;t++){	// Thiết lập địa chỉ trang bắt đầu là 0xB0
		I2C_SAND_BYTE(OLED0561_ADD,COM,t); 	// Địa chỉ trang (từ 0xB0 đến 0xB7)
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x10); // Địa chỉ cột bắt đầu (4 bit cao)
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x00);	// Địa chỉ cột bắt đầu (4 bit thấp)
		for(j=0;j<132;j++){	// Điền nội dung vào toàn bộ trang
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,0x00);
 		}
	}
}

// Hiển thị ký tự ASCII kích thước 8*16
// Lấy mẫu kích thước 8*16, lấy mẫu theo chiều "từ trái sang phải, từ trên xuống dưới", "theo hàng dọc 8 bit thấp trước"
void OLED_DISPLAY_8x16(uint8_t x,  // Tọa độ hàng hiển thị ký tự (từ 0 đến 7) (không thể thay đổi)
		uint8_t y,// Tọa độ cột hiển thị ký tự (từ 0 đến 128)
		uint16_t w){// Số thứ tự ký tự cần hiển thị
	uint8_t j,t,c=0;
	y=y+2; // Vì chip điều khiển OLED bắt đầu từ cột 0x02 nên cần thêm độ dịch
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); // Địa chỉ trang (từ 0xB0 đến 0xB7)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10);// Địa chỉ cột bắt đầu (4 bit cao)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);	// Địa chỉ cột bắt đầu (4 bit thấp)
		for(j=0;j<8;j++){// Điền nội dung vào toàn bộ trang
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,ASCII_8x16[(w*16)+c-512]);// Phù hợp với bảng ASCII cần trừ 512
			c++;}x++;  // Tăng địa chỉ trang
	}
}
// Gửi một chuỗi ký tự đến màn hình, độ dài tối đa 64 ký tự
// Ứng dụng: OLED_DISPLAY_8_16_BUFFER(0," DoYoung Studio");
void OLED_DISPLAY_8x16_BUFFER(uint8_t row,uint8_t *str){
	uint8_t r=0;
	while(*str != '\0'){
		OLED_DISPLAY_8x16(row,r*8,*str++);
		r++;
    }
}
void INVERSE_OLED_DISPLAY_8x16(uint8_t x, // Tọa độ hàng hiển thị ký tự (từ 0 đến 7) (không thể thay đổi)
		uint8_t y, // Tọa độ cột hiển thị ký tự (từ 0 đến 128)
		uint16_t w){ // Số thứ tự ký tự cần hiển thị
	uint8_t j,t,c=0;
	y=y+2; // Vì chip điều khiển OLED bắt đầu từ cột 0x02 nên cần thêm độ dịch
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); // Địa chỉ trang (từ 0xB0 đến 0xB7)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); // Địa chỉ cột bắt đầu (4 bit cao)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);	// Địa chỉ cột bắt đầu (4 bit thấp)
		for(j=0;j<8;j++){ // Điền nội dung vào toàn bộ trang
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,~ASCII_8x16[(w*16)+c-512]);// Phù hợp với bảng ASCII cần trừ 512
			c++;}x++; // Tăng địa chỉ trang

	}
}

//----- Chương trình hiển thị ký tự tiếng Trung ------//

// Hiển thị ký tự tiếng Trung 16*16
// Lấy mẫu kích thước 16*16, lấy mẫu theo chiều "từ trái sang phải, từ trên xuống dưới", "theo hàng dọc 8 bit thấp trước"
void OLED_DISPLAY_16x16(uint8_t x, // Tọa độ hàng hiển thị ký tự (từ 0xB0 đến 0xB7)
		uint8_t y, // Tọa độ cột hiển thị ký tự (từ 0 đến 63)
		uint16_t w){ // Số thứ tự ký tự cần hiển thị
	uint8_t j,t,c=0;
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); // Địa chỉ trang (từ 0xB0 đến 0xB7)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); // Địa chỉ cột bắt đầu (4 bit cao)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16+2);	// Địa chỉ cột bắt đầu (4 bit thấp)
		for(j=0;j<16;j++){ // Điền nội dung vào toàn bộ trang
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,GB_16[(w*32)+c]);
			c++;}x++; // Tăng địa chỉ trang
	}
	I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF); // Bật hiển thị
}
void INVERSE_OLED_DISPLAY_16x16(uint8_t x, // Tọa độ hàng hiển thị ký tự (từ 0xB0 đến 0xB7)
		uint8_t y, // Tọa độ cột hiển thị ký tự (từ 0 đến 63)
		uint16_t w){ // Số thứ tự ký tự cần hiển thị
	uint8_t j,t,c=0;
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); // Địa chỉ trang (từ 0xB0 đến 0xB7)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); // Địa chỉ cột bắt đầu (4 bit cao)
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16+2);	// Địa chỉ cột bắt đầu (4 bit thấp)
		for(j=0;j<16;j++){ // Điền nội dung vào toàn bộ trang

 			I2C_SAND_BYTE(OLED0561_ADD,DAT,~GB_16[(w*32)+c]);// Đảo bit dữ liệu
			c++;}x++; // Tăng địa chỉ trang
	}
	I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF); // Bật hiển thị
}


void OLED_DISPLAY_PIC1(void){ // Hiển thị toàn màn hình hình ảnh
	uint8_t m,i;
	for(m=0;m<8;m++){//
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+m);
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x10); // Địa chỉ cột bắt đầu (4 bit cao)
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x02);	// Địa chỉ cột bắt đầu (4 bit thấp)
		for(i=0;i<128;i++){// Gửi 128 lần nội dung hình ảnh
			I2C_SAND_BYTE(OLED0561_ADD,DAT,PIC1[i+m*128]);}
	}
}
