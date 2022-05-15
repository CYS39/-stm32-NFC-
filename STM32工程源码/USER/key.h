#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define High	1
#define Low		0

// IO方向设置
#define LINE_IN()  {GPIOB->CRL&=0XFFFF0000; GPIOB->CRL |= 0x888;}
#define LINE_OUT() {GPIOB->CRL&=0XFFFF0000; GPIOB->CRL |= 0x333;}

#define ROW_IN()   {GPIOC->CRL&=0XFFFF0000; GPIOC->CRL |= 0x8888;}
#define ROW_OUT()  {GPIOC->CRL&=0XFFFF0000; GPIOC->CRL |= 0x3333;}

#define line0_OUT  		PBout(0)							// 行0 输出
#define line1_OUT  		PBout(1)							// 行1 输出
#define line2_OUT  		PBout(2)							// 行2 输出
#define line3_OUT  		PBout(3)							// 行3 输出
#define row0_OUT  		PCout(0)							// 列0 输出
#define row1_OUT  		PCout(1)							// 列1 输出
#define row2_OUT  		PCout(2)							// 列2 输出
#define row3_OUT  		PCout(3)							// 列3 输出

#define line0_IN  		PBin(0)							 // 行0 输入
#define line1_IN  		PBin(1)							 // 行1 输入
#define line2_IN  		PBin(2)							 // 行2 输入
#define line3_IN  		PBin(3)						   // 行3 输入
#define row0_IN  			PCin(0)							 // 列0 输入
#define row1_IN  		  PCin(1)							 // 列1 输入
#define row2_IN  		  PCin(2)							 // 列2 输入
#define row3_IN  		  PCin(3)							 // 列3 输入

void KEY_Init(void);//IO初始化

void key_line_out(char ret);
void key_row_out(char ret);
void line_in(void);

#endif





