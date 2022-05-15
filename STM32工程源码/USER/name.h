#ifndef __NAME_H
#define __NAME_H	

#include "sys.h"
#include "exti.h"
#include "led.h"
#include "remote.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "iic.h"
#include "oled.h"
#include "oled_font.h"
#include "rtc.h"
#include "time3.h"
#include "stmflash.h"


extern char admin_pass[6];								// 六位管理员密码
extern char pass[8];										// 六位密码		第七位记录门锁状态

extern char pass_input_num;							// 已输入密码次数

extern char input_num;									// 输入密码错误的次数 每次复位和输入密码正确清空，满三次报警，锁死
extern int lock_state;									// 门锁状态		0 关		1 开
extern int time_flag;										// 时间计数
extern int timeout;											// 超时
extern int menu_dir_num;								// 菜单目录选择值


/*
 *	按键值
 *	-1			:	无键值输入
 *	0~9			:	0x00~0x09	
 *	*				：0x0A
 *	#				:	0x0B
 *	up			:	0x0C
 *	down		:	0x0D
 *	ok			: 0x0E
 *	back		:	0x0F
 */
extern int key_value;
extern int key1_value;



void menu_select(void);
int menu_ensure(void);
int change_pass(void);
int change_time(void);
int manager(void);
int* time_assign(int date, int digit, int num, int *array);
int save_time(int* date);
char unlock(void);
void show_pass(char* input_pass, int num);
void hide_pass(char num);

char pass_com(char* input_pass, char* sou_pass);
char affirm_man_pass(void);
void alarm(char arg);




#endif










