#include "name.h"



//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 // ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;				 // �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 // �������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);								 // �����趨������ʼ��
	
	LED1 = 1;
	LED2 = 1;
	BEEP = 0;
	relay = 0;
	
}
 



