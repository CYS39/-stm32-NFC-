#include "name.h" 
 
//外部中断初始化函数
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);						//外部中断，需要使能AFIO时钟

	  KEY_Init();																										//初始化按键对应io模式

    //GPIOB 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;							//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  													//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;							//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  													//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;							//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  													//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;							//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  													//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
}


void EXTI0_IRQHandler(void){
	
	delay_ms(10);    	//消抖			 
  if(line0_IN == 1){
		
		key_line_out(Low);
		ROW_IN();
		delay_ms(10);
		
		// 1
		if(row0_IN == 0){
			
			//oled_write_str(0x00, 0x03, '1');
			key1_value = 162;
			
		}
		
		// 2
		if(row1_IN == 0){
			
			//oled_write_str(0x00, 0x03, '2');
			key1_value = 98;
			
		}
		
		// 3
		if(row2_IN == 0){
			
			//oled_write_str(0x00, 0x03, '3');
			key1_value = 226;
			
		}
		
		// back
		if(row3_IN == 0){
			
			//oled_write_str(0x00, 0x03, 'f');
			key1_value = 16;
			
		}
		
	}
	line_in();
	key_row_out(High);
	EXTI_ClearITPendingBit(EXTI_Line0);  		//清除EXTI0线路挂起位
	
}


void EXTI1_IRQHandler(void){
	
	delay_ms(10);    	//消抖			 
  if(line1_IN == 1){
		
		key_line_out(Low);
		ROW_IN();
		delay_ms(10);
		
		// 4
		if(row0_IN == 0){
			
			//oled_write_str(0x00, 0x03, '4');
			key1_value = 34;
			
		}
		
		// 5
		if(row1_IN == 0){
			
			//oled_write_str(0x00, 0x03, '5');
			key1_value = 2;
			
		}
		
		// 6
		if(row2_IN == 0){
			
			//oled_write_str(0x00, 0x03, '6');
			key1_value = 194;
			
		}
		
		// up
		if(row3_IN == 0){
			
			//oled_write_str(0x00, 0x03, 'e');
			key1_value = 24;
			
		}
		
	}
	line_in();
	key_row_out(High);
	EXTI_ClearITPendingBit(EXTI_Line1);  		//清除EXTI1线路挂起位
	
}


void EXTI2_IRQHandler(void){
	
	delay_ms(10);    	//消抖			 
  if(line2_IN == 1){
		
		key_line_out(Low);
		ROW_IN();
		delay_ms(10);
		
		// 7
		if(row0_IN == 0){
			
			//oled_write_str(0x00, 0x03, '7');
			key1_value = 224;
			
		}
		
		// 8
		if(row1_IN == 0){
			
			//oled_write_str(0x00, 0x03, '8');
			key1_value = 168;
			
		}
		
		// 9
		if(row2_IN == 0){
			
			//oled_write_str(0x00, 0x03, '9');
			key1_value = 144;
			
		}
		
		// down
		if(row3_IN == 0){
			
			//oled_write_str(0x00, 0x03, 'd');
			key1_value = 74;
			
		}
		
	}
	line_in();
	key_row_out(High);
	
	EXTI_ClearITPendingBit(EXTI_Line2);  		//清除EXTI2线路挂起位
	
}


void EXTI3_IRQHandler(void){
	
	if(line3_IN == 1){
		
		key_line_out(Low);
		ROW_IN();
		delay_ms(10);
		
		// *
		if(row0_IN == 0){
			
			//oled_write_str(0x00, 0x03, 'a');
			key1_value = 104;
			
		}
		
		// 0
		if(row1_IN == 0){
			
			//oled_write_str(0x00, 0x03, '0');
			key1_value = 152;
			
		}
		
		// #
		if(row2_IN == 0){
			
			//oled_write_str(0x00, 0x03, 'b');
			key1_value = 176;
			
		}
		
		// ok
		if(row3_IN == 0){
			
			//oled_write_str(0x00, 0x03, 'c');
			key1_value = 56;
			
		}
		
	}
	line_in();
	key_row_out(High);
	
	EXTI_ClearITPendingBit(EXTI_Line3);  		//清除EXTI12线路挂起位
	
}




