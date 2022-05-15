#include "name.h"


void init(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			// 设置中断优先级分组2
	delay_init();																				// 延时
	IIC_Init();																					// iic通讯
	OLED_Init();																				// OLED
	Remote_Init();																			// 红外
	TIM3_Int_Init(999, 71);															// 1ms
	LED_Init();																					// LED
	uart_init(9600);																		// 串口
	EXTIX_Init();
	
}


// RTC时钟
void rtc_init(){
	
	while(RTC_Init()){
		
		delay_ms(2);
		
	}
	
}


// 从flash读密码和门锁状态
void pass_state(){
	
	STMFLASH_Read(FLASH_SAVE_ADDR, (u16*)pass, 4);
	lock_state = pass[7];
	
}



int main(void){	
	
	u8 key;										// 红外键码
	int result = 0;						// 函数返回结果 	
	
	init();
	rtc_init();
	pass_state();
	LED2 = 0;
	printf("初始化完成！\r\n");
	delay_ms(1000);
	LED2 = 1;
	
	if(lock_state) relay = 1;
	oled_time();																		// oled时间页面
	
	while(1){
		
		key = Remote_Scan();													// 获得红外遥控码
		
		// 按 左键 进入开锁
		key_value_select(key);												// 选择键值
		if(key_value == 0x0F){
			
			// 输入密码错误次数不够三次可以进入开门
			if(input_num != 3){
				
				// 输入密码开锁
				unlock();
				
				// 清屏
				OLED_Clear();																// oled清屏
				oled_time();																// oled时间页面
			
			}
			else{
				
				// 显示警报
				oled_alarm();
				
				// 红外键码清空，防止误操作
				delay_ms(400);
				key = Remote_Scan();													// 获得红外遥控码
				key = 0;
				
				// 清屏
				OLED_Clear();																// oled清屏
				oled_time();																// oled时间页面

			}
			
		}
		
		// 按 OK 进入菜单
		if(key_value == 0x0E){
			
			time_flag = 0;
			timeout = 0;
			key_value = -1;
			OLED_Clear();																// oled清屏
			oled_menu();																// 菜单
			
			// 超时或返回 退出菜单页面
			while(key_value!=0x0F && timeout == 0){
					
				key = Remote_Scan();													// 获得红外遥控码
				
				if(key){
					
					time_flag = 0;
					key_value_select(key);												// 选择键值
					
					// 菜单选择
					menu_select();
					
					// 菜单确定
					result = menu_ensure();
					
					// 结束(未退出菜单页面)
					if(result){
						
						// 红外按键清空，防止多按误操作
						delay_ms(100);
						key = Remote_Scan();												// 获得红外遥控码
						key = 0;
						
						OLED_Clear();																// oled清屏
						oled_menu();																// 菜单
						timeout = 0;
						time_flag = 0;
						result = 0;
						key_value = -1;
						// key_value = 0x0F;														// 结束返回
						// break;																			// 退出while循环
						
					}
				
				}
				// 红外按键清空，防止多按误操作
				delay_ms(200);
				key = Remote_Scan();												// 获得红外遥控码
				key = 0;
				delay_ms(500);
				
			}
			
			// 返回或超时后
			if(timeout || key_value==0x0F){
				
				menu_dir_num = -1;													// 菜单目录选择值复位
				OLED_Clear();																// oled清屏
				oled_time();																// oled时间页面
				key = Remote_Scan();												// 获得红外遥控码
				key = 0;
				
			}
			
		}
		
		// 按右键关锁
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
		timeout = 0;																	// 超时复位
		oled_update_time();														// oled时间更新
		oled_lock_state();														// 门锁状态
		delay_ms(100);
		
	}
	
}





