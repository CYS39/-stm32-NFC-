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

int menu_dir_num 	= -1;		// 菜单目录选择值


// 菜单选择
void menu_select(){
	
	// 上
	if(key_value == 0x0D){
		
		menu_dir_num++;
		if(menu_dir_num >= 2) menu_dir_num = 2;
		
	}
	
	// 下
	if(key_value == 0x0C){
		
		menu_dir_num--;
		if(menu_dir_num <= 0) menu_dir_num = 0;
		
	}
	
	// oled选择效果图
	if(menu_dir_num != -1){
		
		oled_select_pic(0x60, 0x02 + (2 * menu_dir_num));
		
	}
	
}


// 菜单确定
int menu_ensure(){
	
	int result = 0;
	if(key_value == 0x0E && menu_dir_num != -1){
		
		OLED_Clear();																// oled清屏
		// 更改密码
		if(menu_dir_num == 0)
		{
			
			while(key_value!=0x0F && timeout == 0){
				
				// 确认管理员密码
				result = affirm_man_pass();
				
				// 更改密码
				if(result){
					
					result = change_pass();
					
				}
				
			}
			// 返回 1 不会退出菜单页面
			return 1;
			
		}
		
		// 更改时间  √
		if(menu_dir_num == 1)
		{
			
			result = change_time();
			
		}
		
		// 管理员
		if(menu_dir_num == 2)
		{
			
			while(key_value!=0x0F && timeout == 0){
				
				// 确认管理员密码
				result = affirm_man_pass();
				
				// 进入管理员  查看密码
				if(result){
					
					result = manager();
					
				}
				
			}
			return 1;
			
		}
		
	}
	return result;
	
}


// 更改密码		返回 1 结束
int change_pass(){
	
	u8 key;										// 红外键码
	char num = 0;
	char flag = 0;
	char input_pass1[6], input_pass2[6];
	char type;
	char result;
	
	OLED_Clear();
	oled_change_pass(0);
	
	// 按键清空 防止误操作
	delay_ms(200);
	key = Remote_Scan();													// 获得红外遥控码
	key = 0;
	
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// 获得红外遥控码
		
		if(key){
			
			time_flag  = 0;
			// 获得密码键值
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
			
			// 获得选择键值
			key_value_select(key);
			
			// 按 上 显示密码
			if(key_value == 0x0C) type = 1;
			if(type){
				
				if(flag) show_pass(input_pass2, num);
				else show_pass(input_pass1, num);
				
			}
			
			// 按 下 隐藏密码
			if(key_value == 0x0D) type = 0;
			if(type == 0) hide_pass(num);
			delay_ms(200);
			
			
			// 输入六位密码自动确定对比密码
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
			
			// 按键清空 防止误操作
			key = Remote_Scan();													// 获得红外遥控码
			key = 0;
		
		}
		delay_ms(500);
		
	}
	
	return 1;
	
}


// 时间数值位置
int time_place[][2] = {
	
	{0x08, 0x01}, {0x10, 0x01}, {0x18, 0x01}, {0x20, 0x01}, {0x38, 0x01}, 
	{0x40, 0x01}, {0x58, 0x01}, {0x60, 0x01}, {0x28, 0x03}, {0x30, 0x03}, 
	{0x40, 0x03}, {0x48, 0x03}, {0x58, 0x03}, {0x60, 0x03}, 
	
};
	

// 更改时间		返回 1 结束
int change_time(){
	
	u8 key;										// 红外键码
//	int key_type;							// 键值类型
	int place = -1;						// 位置
	int time_date[14];				// 时间更改存放
	
	// 显示时间
	time_assign(calendar.w_year	, 4, 0, time_date);
	time_assign(calendar.w_month, 2, 4, time_date);
	time_assign(calendar.w_date	, 2, 6, time_date);
	time_assign(calendar.hour		, 2, 8, time_date);
	time_assign(calendar.min		, 2, 10, time_date);
	time_assign(calendar.sec		, 2, 12, time_date);
	oled_change_time();
	
	while(timeout == 0){
		
		key = Remote_Scan();																		// 获得红外遥控码
		
		if(key){
			
			time_flag = 0;
			// 选择位置
			key_value_select(key);												// 时间键值
				
			// 上一个位置
			if(key_value == 0x0C){
				
				if(place != -1) oled_write_str(time_place[place][0], time_place[place][1], time_date[place] + 48);
				place--;
				if(place <= 0) place = 0;
				
			}
			
			// 下一个位置
			if(key_value == 0x0D){
				
				if(place != -1) oled_write_str(time_place[place][0], time_place[place][1], time_date[place] + 48);
				place++;
				if(place >= 13) place = 13;
				
			}
			
			// 返回 (不更改时间)
			if(key_value == 0x0F){
				
				key_value = -1;
				key = Remote_Scan();																		// 获得红外遥控码
				key = 0;
				delay_ms(500);
				return 1;
				
			}
			
			// OK 	(确认更改时间)
			if(key_value == 0x0E){
				
				save_time(time_date);
				return 1;
				
			}
			
			
			// 时间数值
			key_value_time(key);													// 时间键值
			if(key_value != -1){
				
				time_date[place] = key_value;
				if(place != -1) oled_write_str(time_place[place][0], time_place[place][1], time_date[place] + 48);
				place++;
				if(place == 14) place = -1;
				
			}
			
			// 选择效果图
			if(place != -1) oled_change_pic(time_place[place][0], time_place[place][1]);
			
		}
		delay_ms(200);
		key = Remote_Scan();																		// 获得红外遥控码
		key = 0;
		delay_ms(500);
		
	}
	
	return 1;
	
}


// 管理员			返回 1 结束
int manager(){
	
	u8 key;										// 红外键码
	char num = 0;
	oled_man_shwo_pass();
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// 获得红外遥控码
		key_value_select(key);												// 时间键值
		if(timeout){
			
			timeout = 0;
			num++;
			if(num == 3) timeout = 1;
			
		}
		
	}
	
	return 1;
	
}


// 时间赋值
// date 	数据
// digit 	位数
// num		序号
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


// 保存时间		0 成功
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


// 输入密码开锁
char unlock(){
	
	int key;											// 红外键码
	int num = 0;									// 已输入密码个数
	char input_pass[10];					// 输入密码存放
	char type;										// 密码显示模式
	char result;									// 密码对比结果		1 正确  0 错误
	
	// 清屏 显示 请输入密码
	OLED_Init();
	oled_unlock();
	
	// 按键清空 防止误操作
	key_value = -1;
	delay_ms(200);
	key = Remote_Scan();													// 获得红外遥控码
	key = 0;
	delay_ms(200);
	
	// 返回或超时退出
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// 获得红外遥控码
		// printf("timeout = %d\r\n", timeout);
		
		if(key){
			
			time_flag  = 0;
			// 获得密码键值
			key_value_pass(key);
			if(key_value != -1){
				
				input_pass[num] = key_value;
				input_pass[9] = num;
				num++;
				
			}
			
			// 获得选择键值
			key_value_select(key);
			
			// 按 上 显示密码
			if(key_value == 0x0C) type = 1;
			if(type) show_pass(input_pass, num);
			
			// 按 下 隐藏密码
			if(key_value == 0x0D) type = 0;
			if(type == 0) hide_pass(num);
			delay_ms(200);
			
			
			// 输入六位密码自动确定对比密码
			if(num == 6){
				
				result = pass_com(input_pass, pass);
				if(result){
					
					input_num = 0;										// 输入错误次数清空
					relay = 1;
					oled_pass_result(1);							// 显示输入密码正确
					lock_state = 1;										// 门锁状态打开
					pass[7] = lock_state;							// 保存状态
					STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)pass, 4);				// 写入flash
					timeout = 1;											// 超时，函数返回后直接退出到时间页面
					return 1;
					
				}
				else{
					
					input_num++;												// 输入错误次数加一
					if(input_num != 3) oled_pass_result(0);
					
				}
				num = 0;														// 已输入密码个数清空，准备下次密码输入
				
				// 三次错误警报
				if(input_num == 3){
					
					alarm(1);
					oled_alarm();
					timeout = 1;
					return(1);
					
				}
				OLED_Clear();
				oled_unlock();
				
			}
			
			// 按键清空 防止误操作
			key = Remote_Scan();													// 获得红外遥控码
			key = 0;
		
		}
		delay_ms(500);
		
	}
	return 0;
	
}


// 显示密码
void show_pass(char* input_pass, int num){
	
	oled_write_string(0x08, 0x04, (char*)input_pass, num);
	
}

// 隐藏密码
void hide_pass(char num){
	
	char i;
	for(i=1; i<=num; i++){
		
		oled_write_str(0x08*i, 0x04, '*');
		
	}
	
}


// 密码对比
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


// 确认管理员密码  1 密码正确		0 密码错误
char affirm_man_pass(){
	
	int key;
	char num;
	char result;
	char type;
	char input_pass[6];
	
	OLED_Clear();
	oled_input_man_pass();
	
	// 超时或返回 退出
	while(key_value!=0x0F && timeout == 0){
		
		key = Remote_Scan();													// 获得红外遥控码
		if(key){
			
			time_flag  = 0;
			// 获得密码键值
			key_value_pass(key);
			if(key_value != -1){
				
				input_pass[num] = key_value;
				num++;
				
			}
			
			// 获得选择键值
			key_value_select(key);
			
			// 按 上 显示密码
			if(key_value == 0x0C) type = 1;
			if(type) show_pass(input_pass, num);
			
			// 按 下 隐藏密码
			if(key_value == 0x0D) type = 0;
			if(type == 0) hide_pass(num);
			
			// 输入六位密码自动确定对比密码
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
			
			// 按键清空 防止误操作
			delay_ms(200);
			key = Remote_Scan();													// 获得红外遥控码
			key = 0;
			
		}
		delay_ms(500);
		
	}
	return 0;
	
}


// 门锁锁死和报警
// 1  警报
// 0  解除警报
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


















