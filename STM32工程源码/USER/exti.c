#include "name.h" 
 
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);						//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();																										//��ʼ��������Ӧioģʽ

    //GPIOB �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 															//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  													//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  													//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  													//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;							//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  													//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
}


void EXTI0_IRQHandler(void){
	
	delay_ms(10);    	//����			 
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
	EXTI_ClearITPendingBit(EXTI_Line0);  		//���EXTI0��·����λ
	
}


void EXTI1_IRQHandler(void){
	
	delay_ms(10);    	//����			 
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
	EXTI_ClearITPendingBit(EXTI_Line1);  		//���EXTI1��·����λ
	
}


void EXTI2_IRQHandler(void){
	
	delay_ms(10);    	//����			 
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
	
	EXTI_ClearITPendingBit(EXTI_Line2);  		//���EXTI2��·����λ
	
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
	
	EXTI_ClearITPendingBit(EXTI_Line3);  		//���EXTI12��·����λ
	
}




