#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define LED1 	PBout(13) // 绿色      
#define LED2 	PBout(14) // 红色       低电平亮
#define BEEP 	PBout(11) // 蜂鸣器			
#define relay PBout(10) // 继电器			高电平 开 响
		
void LED_Init(void); //初始化

		 	
			
#endif





