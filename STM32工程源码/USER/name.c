#include "name.h"

	
char admin_pass[6] = {'2', '5', '8', '1', '2', '3'};
char pass[8];
	
char input_num = 0;
char pass_input_num;
int key1_value = -1;

int key_value 		= -1;									
int lock_state 		= 0	;
int time_flag 		= 0	;
int timeout 			=	0	;

int menu_dir_num 	= -1;		// �˵�Ŀ¼ѡ��ֵ


// �˵�ѡ��
void menu_select(){
	
	// ��
	if(key_value == 0x0D){
		
		menu_dir_num++;
		if(menu_dir_num >= 2) menu_dir_num = 2;
		
	}
	
	// ��
	if(key_value == 0x0C){
		
		menu_dir_num--;
		if(menu_dir_num <= 0) menu_dir_num = 0;
		
	}
	
	// oledѡ��Ч��ͼ
	if(menu_dir_num != -1){
		
		oled_select_pic(0x60, 0x02 + (2 * menu_dir_num));
		
	}
	
}


// �˵�ȷ��
int menu_ensure(){
	
	int result = 0;
	if(key_value == 0x0E && menu_dir_num != -1){
		
		OLED_Clear();																// oled����
		// ��������
		if(menu_dir_num == 0)
		{
			
			while(key_value!=0x0F && timeout == 0){
				
				// ȷ�Ϲ���Ա����
				result = affirm_man_pass();
				
				// ��������
				if(result){
					
					result = change_pass();
					
				}
				
			}
			// ���� 1 �����˳��˵�ҳ��
			return 1;
			
		}
		
		// ����ʱ��  ��
		if(menu_dir_num == 1)
		{
			
			result = change_time();
			
		}
		
		// ����Ա
		if(menu_dir_num == 2)
		{
			
			while(key_value!=0x0F && timeout == 0){
				
				// ȷ�Ϲ���Ա����
				result = affirm_man_pass();
				
				// �������Ա  �鿴����
				if(result){
					
					result = manager();
					
				}
				
			}
			return 1;
			
		}
		
	}
	return result;
	
}


// ��������		���� 1 ����
int change_pass(){
	
	u8 key;										// �������
	char num = 0;
	char flag = 0;
	char input_pass1[6], input_pass2[6];
	char type;
	char result;
	
	OLED_Clear();
	oled_change_pass(0);
	
	// ������� ��ֹ�����
	delay_ms(200);
	key = Remote_Scan();													// ��ú���ң����
	key = 0;
	
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// ��ú���ң����
		
		if(key){
			
			time_flag  = 0;
			// ��������ֵ
			key_value_pass(key);
			if(key_value != -1){
					
				if(flag){
					
					input_pass2[num] = key_value;
					
				}
				else{
					
					input_pass1[num] = key_value;
					
				}
				
				num++;
				
			}
			
			// ���ѡ���ֵ
			key_value_select(key);
			
			// �� �� ��ʾ����
			if(key_value == 0x0C) type = 1;
			if(type){
				
				if(flag) show_pass(input_pass2, num);
				else show_pass(input_pass1, num);
				
			}
			
			// �� �� ��������
			if(key_value == 0x0D) type = 0;
			if(type == 0) hide_pass(num);
			delay_ms(200);
			
			
			// ������λ�����Զ�ȷ���Ա�����
			if(num == 6 && flag == 1){
				
				result = pass_com(input_pass1, input_pass2);
				if(result){
					
					oled_change_pass_result(1);
					
					for(num=0; num<6; num++) pass[num] = input_pass1[num];
					STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)pass, 4);
					timeout = 1;
					return 1;
					
				}
				else{
					
					oled_change_pass_result(0);
					
				}
				num = 0;
				flag = 0;
				OLED_Clear();
				oled_change_pass(0);
				
			}
			
			if(num == 6){
				
				flag = 1;
				num = 0;
				OLED_Clear();
				oled_change_pass(1);
				
			}
			
			// ������� ��ֹ�����
			key = Remote_Scan();													// ��ú���ң����
			key = 0;
		
		}
		delay_ms(500);
		
	}
	
	return 1;
	
}


// ʱ����ֵλ��
int time_place[][2] = {
	
	{0x08, 0x01}, {0x10, 0x01}, {0x18, 0x01}, {0x20, 0x01}, {0x38, 0x01}, 
	{0x40, 0x01}, {0x58, 0x01}, {0x60, 0x01}, {0x28, 0x03}, {0x30, 0x03}, 
	{0x40, 0x03}, {0x48, 0x03}, {0x58, 0x03}, {0x60, 0x03}, 
	
};
	

// ����ʱ��		���� 1 ����
int change_time(){
	
	u8 key;										// �������
//	int key_type;							// ��ֵ����
	int place = -1;						// λ��
	int time_date[14];				// ʱ����Ĵ��
	
	// ��ʾʱ��
	time_assign(calendar.w_year	, 4, 0, time_date);
	time_assign(calendar.w_month, 2, 4, time_date);
	time_assign(calendar.w_date	, 2, 6, time_date);
	time_assign(calendar.hour		, 2, 8, time_date);
	time_assign(calendar.min		, 2, 10, time_date);
	time_assign(calendar.sec		, 2, 12, time_date);
	oled_change_time();
	
	while(timeout == 0){
		
		key = Remote_Scan();																		// ��ú���ң����
		
		if(key){
			
			time_flag = 0;
			// ѡ��λ��
			key_value_select(key);												// ʱ���ֵ
				
			// ��һ��λ��
			if(key_value == 0x0C){
				
				if(place != -1) oled_write_str(time_place[place][0], time_place[place][1], time_date[place] + 48);
				place--;
				if(place <= 0) place = 0;
				
			}
			
			// ��һ��λ��
			if(key_value == 0x0D){
				
				if(place != -1) oled_write_str(time_place[place][0], time_place[place][1], time_date[place] + 48);
				place++;
				if(place >= 13) place = 13;
				
			}
			
			// ���� (������ʱ��)
			if(key_value == 0x0F){
				
				key_value = -1;
				key = Remote_Scan();																		// ��ú���ң����
				key = 0;
				delay_ms(500);
				return 1;
				
			}
			
			// OK 	(ȷ�ϸ���ʱ��)
			if(key_value == 0x0E){
				
				save_time(time_date);
				return 1;
				
			}
			
			
			// ʱ����ֵ
			key_value_time(key);													// ʱ���ֵ
			if(key_value != -1){
				
				time_date[place] = key_value;
				if(place != -1) oled_write_str(time_place[place][0], time_place[place][1], time_date[place] + 48);
				place++;
				if(place == 14) place = -1;
				
			}
			
			// ѡ��Ч��ͼ
			if(place != -1) oled_change_pic(time_place[place][0], time_place[place][1]);
			
		}
		delay_ms(200);
		key = Remote_Scan();																		// ��ú���ң����
		key = 0;
		delay_ms(500);
		
	}
	
	return 1;
	
}


// ����Ա			���� 1 ����
int manager(){
	
	u8 key;										// �������
	char num = 0;
	oled_man_shwo_pass();
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// ��ú���ң����
		key_value_select(key);												// ʱ���ֵ
		if(timeout){
			
			timeout = 0;
			num++;
			if(num == 3) timeout = 1;
			
		}
		
	}
	
	return 1;
	
}


// ʱ�丳ֵ
// date 	����
// digit 	λ��
// num		���
// 
int* time_assign(int date, int digit, int num, int *array){
	
	if(digit == 4){
		
		array[num] 		= date/1000;
		array[num+1] 	= date%1000/100;
		array[num+2] 	= date%100/10;
		array[num+3] 	= date%10;
		
	}
	else if(digit == 2){
		
		array[num] 		= date/10;
		array[num+1] 	= date%10;
		
	}
	return array;
	
}


// ����ʱ��		0 �ɹ�
int save_time(int* date){
	
	int result = -1;
	int year, month, day, hour, min, sec;
	year 	= (date[0]*1000 + date[1]*100 + date[2]*10 + date[3]);
	month = (date[4]*10 + date[5]);
	day 	= (date[6]*10 + date[7]);
	hour 	= (date[8]*10 + date[9]);
	min 	= (date[10]*10 + date[11]);
	sec	 	= (date[12]*10 + date[13]);
	
	result = RTC_Set(year, month, day, hour, min, sec);
	
	return result;
	
}


// �������뿪��
char unlock(){
	
	int key;											// �������
	int num = 0;									// �������������
	char input_pass[10];					// ����������
	char type;										// ������ʾģʽ
	char result;									// ����ԱȽ��		1 ��ȷ  0 ����
	
	// ���� ��ʾ ����������
	OLED_Init();
	oled_unlock();
	
	// ������� ��ֹ�����
	key_value = -1;
	delay_ms(200);
	key = Remote_Scan();													// ��ú���ң����
	key = 0;
	delay_ms(200);
	
	// ���ػ�ʱ�˳�
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// ��ú���ң����
		// printf("timeout = %d\r\n", timeout);
		
		if(key){
			
			time_flag  = 0;
			// ��������ֵ
			key_value_pass(key);
			if(key_value != -1){
				
				input_pass[num] = key_value;
				input_pass[9] = num;
				num++;
				
			}
			
			// ���ѡ���ֵ
			key_value_select(key);
			
			// �� �� ��ʾ����
			if(key_value == 0x0C) type = 1;
			if(type) show_pass(input_pass, num);
			
			// �� �� ��������
			if(key_value == 0x0D) type = 0;
			if(type == 0) hide_pass(num);
			delay_ms(200);
			
			
			// ������λ�����Զ�ȷ���Ա�����
			if(num == 6){
				
				result = pass_com(input_pass, pass);
				if(result){
					
					input_num = 0;										// �������������
					relay = 1;
					oled_pass_result(1);							// ��ʾ����������ȷ
					lock_state = 1;										// ����״̬��
					pass[7] = lock_state;							// ����״̬
					STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)pass, 4);				// д��flash
					timeout = 1;											// ��ʱ���������غ�ֱ���˳���ʱ��ҳ��
					return 1;
					
				}
				else{
					
					input_num++;												// ������������һ
					if(input_num != 3) oled_pass_result(0);
					
				}
				num = 0;														// ���������������գ�׼���´���������
				
				// ���δ��󾯱�
				if(input_num == 3){
					
					alarm(1);
					oled_alarm();
					timeout = 1;
					return(1);
					
				}
				OLED_Clear();
				oled_unlock();
				
			}
			
			// ������� ��ֹ�����
			key = Remote_Scan();													// ��ú���ң����
			key = 0;
		
		}
		delay_ms(500);
		
	}
	return 0;
	
}


// ��ʾ����
void show_pass(char* input_pass, int num){
	
	oled_write_string(0x08, 0x04, (char*)input_pass, num);
	
}

// ��������
void hide_pass(char num){
	
	char i;
	for(i=1; i<=num; i++){
		
		oled_write_str(0x08*i, 0x04, '*');
		
	}
	
}


// ����Ա�
char pass_com(char* input_pass, char* sou_pass){
	
	char i;
	for(i=0; i<6; i++){
		
		if(input_pass[i] != sou_pass[i]){
			
			//oled_pass_result(0);
			return 0;
			
		}
		
	}
	//oled_pass_result(1);
	return 1;
	
}


// ȷ�Ϲ���Ա����  1 ������ȷ		0 �������
char affirm_man_pass(){
	
	int key;
	char num;
	char result;
	char type;
	char input_pass[6];
	
	OLED_Clear();
	oled_input_man_pass();
	
	// ��ʱ�򷵻� �˳�
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// ��ú���ң����
		if(key){
			
			time_flag  = 0;
			// ��������ֵ
			key_value_pass(key);
			if(key_value != -1){
				
				input_pass[num] = key_value;
				num++;
				
			}
			
			// ���ѡ���ֵ
			key_value_select(key);
			
			// �� �� ��ʾ����
			if(key_value == 0x0C) type = 1;
			if(type) show_pass(input_pass, num);
			
			// �� �� ��������
			if(key_value == 0x0D) type = 0;
			if(type == 0) hide_pass(num);
			
			// ������λ�����Զ�ȷ���Ա�����
			if(num == 6){
				
				result = pass_com(input_pass, admin_pass);
				if(result){
					
					return 1;
					
				}
				num = 0;
				OLED_Clear();
				oled_pass_result(0);
				return 0;
				
			}
			
			// ������� ��ֹ�����
			delay_ms(200);
			key = Remote_Scan();													// ��ú���ң����
			key = 0;
			
		}
		delay_ms(500);
		
	}
	return 0;
	
}


// ���������ͱ���
// 1  ����
// 0  �������
void alarm(char arg){
	
	if(arg){
		
		LED1 = 0;
		BEEP = 1;
		
	}
	else{
		
		LED1 = 1;
		BEEP = 0;
		
	}
	
}


















