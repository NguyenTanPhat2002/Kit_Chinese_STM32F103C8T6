/*
 * oled0561.c
 *
 *  Created on: Jan 2, 2025
 *      Author: LAPTOP
 */

#include "oled0561.h"
#include "ASCII_8x16.h" //引入字体 ASCII

#include "CHS_16x16.h" //引入汉字字体
#include "PIC1.h" //引入图片


void OLED0561_Init (void){//OLED屏开显示初始化
	OLED_DISPLAY_OFF(); //OLED关显示
	OLED_DISPLAY_CLEAR(); //清空屏幕内容
	OLED_DISPLAY_ON(); //OLED屏初始值设置并开显示
}
void OLED_DISPLAY_ON (void){//OLED屏初始值设置并开显示
	uint8_t buf[28]={
	0xae,//0xae:关显示，0xaf:开显示
    0x00,0x10,//开始地址（双字节）
	0xd5,0x80,//显示时钟频率？
	0xa8,0x3f,//复用率？
	0xd3,0x00,//显示偏移？
	0XB0,//写入页位置（0xB0~7）
	0x40,//显示开始线
	0x8d,0x14,//VCC电源
	0xa1,//设置段重新映射？
	0xc8,//COM输出方式？
	0xda,0x12,//COM输出方式？
	0x81,0xff,//对比度，指令：0x81，数据：0~255（255最高）
	0xd9,0xf1,//充电周期？
	0xdb,0x30,//VCC电压输出
	0x20,0x00,//水平寻址设置
	0xa4,//0xa4:正常显示，0xa5:整体点亮
	0xa6,//0xa6:正常显示，0xa7:反色显示
	0xaf//0xae:关显示，0xaf:开显示
	}; //
	I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,28);
}
void OLED_DISPLAY_OFF (void){//OLED屏关显示
	uint8_t buf[3]={
		0xae,//0xae:关显示，0xaf:开显示
		0x8d,0x10,//VCC电源
	}; //
	I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,3);
}
void OLED_DISPLAY_LIT (uint8_t x){//OLED屏亮度设置（0~255）
	I2C_SAND_BYTE(OLED0561_ADD,COM,0x81);
	I2C_SAND_BYTE(OLED0561_ADD,COM,x);//亮度值
}
void OLED_DISPLAY_CLEAR(void){//清屏操作
	uint8_t j,t;
	for(t=0xB0;t<0xB8;t++){	//设置起始页地址为0xB0
		I2C_SAND_BYTE(OLED0561_ADD,COM,t); 	//页地址（从0xB0到0xB7）
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x10); //起始列地址的高4位
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x00);	//起始列地址的低4位
		for(j=0;j<132;j++){	//整页内容填充
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,0x00);
 		}
	}
}

//显示英文与数字8*16的ASCII码
//取模大小为8*16，取模方式为“从左到右从上到下”“纵向8点下高位”
void OLED_DISPLAY_8x16(uint8_t x, //显示汉字的页坐标（从0到7）（此处不可修改）
		uint8_t y, //显示汉字的列坐标（从0到128）
		uint16_t w){ //要显示汉字的编号
	uint8_t j,t,c=0;
	y=y+2; //因OLED屏的内置驱动芯片是从0x02列作为屏上最左一列，所以要加上偏移量
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); //页地址（从0xB0到0xB7）
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); //起始列地址的高4位
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);	//起始列地址的低4位
		for(j=0;j<8;j++){ //整页内容填充
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,ASCII_8x16[(w*16)+c-512]);//为了和ASII表对应要减512
			c++;}x++; //页地址加1
	}
}
//向LCM发送一个字符串,长度64字符之内。
//应用：OLED_DISPLAY_8_16_BUFFER(0," DoYoung Studio");
void OLED_DISPLAY_8x16_BUFFER(uint8_t row,uint8_t *str){
	uint8_t r=0;
	while(*str != '\0'){
		OLED_DISPLAY_8x16(row,r*8,*str++);
		r++;
    }
}
void INVERSE_OLED_DISPLAY_8x16(uint8_t x, //显示汉字的页坐标（从0到7）（此处不可修改）
		uint8_t y, //显示汉字的列坐标（从0到128）
		uint16_t w){ //要显示汉字的编号
	uint8_t j,t,c=0;
	y=y+2; //因OLED屏的内置驱动芯片是从0x02列作为屏上最左一列，所以要加上偏移量
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); //页地址（从0xB0到0xB7）
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); //起始列地址的高4位
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);	//起始列地址的低4位
		for(j=0;j<8;j++){ //整页内容填充
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,~ASCII_8x16[(w*16)+c-512]);//为了和ASII表对应要减512
			c++;}x++; //页地址加1

	}
}

//----- 用于汉字显示的程序 ------//

//显示汉字16*16
//取模大小为16*16，取模方式为“从左到右从上到下”“纵向8点下高位”
void OLED_DISPLAY_16x16(uint8_t x, //显示汉字的页坐标（从0xB0到0xB7）
		uint8_t y, //显示汉字的列坐标（从0到63）
		uint16_t w){ //要显示汉字的编号
	uint8_t j,t,c=0;
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); //页地址（从0xB0到0xB7）
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); //起始列地址的高4位
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16+2);	//起始列地址的低4位
		for(j=0;j<16;j++){ //整页内容填充
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,GB_16[(w*32)+c]);
			c++;}x++; //页地址加1
	}
	I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF); //开显示
}
void INVERSE_OLED_DISPLAY_16x16(uint8_t x, //显示汉字的页坐标（从0xB0到0xB7）
		uint8_t y, //显示汉字的列坐标（从0到63）
		uint16_t w){ //要显示汉字的编号
	uint8_t j,t,c=0;
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); //页地址（从0xB0到0xB7）
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); //起始列地址的高4位
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16+2);	//起始列地址的低4位
		for(j=0;j<16;j++){ //整页内容填充

 			I2C_SAND_BYTE(OLED0561_ADD,DAT,~GB_16[(w*32)+c]);//按位取反
			c++;}x++; //页地址加1
	}
	I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF); //开显示
}


void OLED_DISPLAY_PIC1(void){ //显示全屏图片
	uint8_t m,i;
	for(m=0;m<8;m++){//
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+m);
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x10); //起始列地址的高4位
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x02);	//起始列地址的低4位
		for(i=0;i<128;i++){//送入128次图片显示内容
			I2C_SAND_BYTE(OLED0561_ADD,DAT,PIC1[i+m*128]);}
	}
}
