#include "name.h"


void init(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			// �����ж����ȼ�����2
	delay_init();																				// ��ʱ
	IIC_Init();																					// iicͨѶ
	OLED_Init();																				// OLED
	Remote_Init();																			// ����
	TIM3_Int_Init(999, 71);															// 1ms
	LED_Init();																					// LED
	uart_init(9600);																		// ����
	EXTIX_Init();
	
}


// RTCʱ��
void rtc_init(){
	
	while(RTC_Init()){
		
		delay_ms(2);
		
	}
	
}


// ��flash�����������״̬
void pass_state(){
	
	STMFLASH_Read(FLASH_SAVE_ADDR, (u16*)pass, 4);
	lock_state = pass[7];
	
}



int main(void){	
	
	u8 key;										// �������
	int result = 0;						// �������ؽ�� 	
	
	init();
	rtc_init();
	pass_state();
	LED2 = 0;
	printf("��ʼ����ɣ�\r\n");
	delay_ms(1000);
	LED2 = 1;
	
	if(lock_state) relay = 1;
	oled_time();																		// oledʱ��ҳ��
	
	while(1){
		
		key = Remote_Scan();													// ��ú���ң����
		
		// �� ��� ���뿪��
		key_value_select(key);												// ѡ���ֵ
		if(key_value == 0x0F){
			
			// ���������������������ο��Խ��뿪��
			if(input_num != 3){
				
				// �������뿪��
				unlock();
				
				// ����
				OLED_Clear();																// oled����
				oled_time();																// oledʱ��ҳ��
			
			}
			else{
				
				// ��ʾ����
				oled_alarm();
				
				// ���������գ���ֹ�����
				delay_ms(400);
				key = Remote_Scan();													// ��ú���ң����
				key = 0;
				
				// ����
				OLED_Clear();																// oled����
				oled_time();																// oledʱ��ҳ��

			}
			
		}
		
		// �� OK ����˵�
		if(key_value == 0x0E){
			
			time_flag = 0;
			timeout = 0;
			key_value = -1;
			OLED_Clear();																// oled����
			oled_menu();																// �˵�
			
			// ��ʱ�򷵻� �˳��˵�ҳ��
			while(key_value!=0x0F && timeout == 0){
					
				key = Remote_Scan();													// ��ú���ң����
				
				if(key){
					
					time_flag = 0;
					key_value_select(key);												// ѡ���ֵ
					
					// �˵�ѡ��
					menu_select();
					
					// �˵�ȷ��
					result = menu_ensure();
					
					// ����(δ�˳��˵�ҳ��)
					if(result){
						
						// ���ⰴ����գ���ֹ�ఴ�����
						delay_ms(100);
						key = Remote_Scan();												// ��ú���ң����
						key = 0;
						
						OLED_Clear();																// oled����
						oled_menu();																// �˵�
						timeout = 0;
						time_flag = 0;
						result = 0;
						key_value = -1;
						// key_value = 0x0F;														// ��������
						// break;																			// �˳�whileѭ��
						
					}
				
				}
				// ���ⰴ����գ���ֹ�ఴ�����
				delay_ms(200);
				key = Remote_Scan();												// ��ú���ң����
				key = 0;
				delay_ms(500);
				
			}
			
			// ���ػ�ʱ��
			if(timeout || key_value==0x0F){
				
				menu_dir_num = -1;													// �˵�Ŀ¼ѡ��ֵ��λ
				OLED_Clear();																// oled����
				oled_time();																// oledʱ��ҳ��
				key = Remote_Scan();												// ��ú���ң����
				key = 0;
				
			}
			
		}
		
		// ���Ҽ�����
		if(key_value == 0x0D){
			
			if(lock_state){
				
				relay = 0;
				lock_state = 0;
				pass[7] = lock_state;
				STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)pass, 4);
				
			}
			
		}
		
		time_flag = 0;
		key_value = -1;
		timeout = 0;																	// ��ʱ��λ
		oled_update_time();														// oledʱ�����
		oled_lock_state();														// ����״̬
		delay_ms(100);
		
	}
	
}





