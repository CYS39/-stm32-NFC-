#include "name.h"


//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
	
 	GPIO_InitTypeDef GPIO_InitStructure;
  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         // 设置成下拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);                // 初始化
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         // 设置成下拉输入	  
	GPIO_Init(GPIOC, &GPIO_InitStructure);                // 初始化

	LINE_IN();
	//PD2in();
	key_row_out(High);
	
}


void PD2out(){
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		   //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 
	
}


void PD2in(){
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         // 设置成下拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);                // 初始化	
	
}


// 行输出
void key_line_out(char ret){
	
	LINE_OUT();
	//PD2out();
	if(ret == High){
		
		line0_OUT = 1;
		line1_OUT = 1;
		line2_OUT = 1;
		line3_OUT = 1;
		
	}
	if(ret == Low){
		
		line0_OUT = 0;
		line1_OUT = 0;
		line2_OUT = 0;
		line3_OUT = 0;
		
	}
	
}


// 列输出
void key_row_out(char ret){
	
	ROW_OUT();
	if(ret == High){
		
		row0_OUT = 1;
		row1_OUT = 1;
		row2_OUT = 1;
		row3_OUT = 1;
		
	}
	if(ret == Low){
		
		row0_OUT = 0;
		row1_OUT = 0;
		row2_OUT = 0;
		row3_OUT = 0;
		
	}
	
}


void line_in(){
	
	LINE_IN();
	
}










