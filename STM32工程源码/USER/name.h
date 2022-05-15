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


extern char admin_pass[6];								// ��λ����Ա����
extern char pass[8];										// ��λ����		����λ��¼����״̬

extern char pass_input_num;							// �������������

extern char input_num;									// �����������Ĵ��� ÿ�θ�λ������������ȷ��գ������α���������
extern int lock_state;									// ����״̬		0 ��		1 ��
extern int time_flag;										// ʱ�����
extern int timeout;											// ��ʱ
extern int menu_dir_num;								// �˵�Ŀ¼ѡ��ֵ


/*
 *	����ֵ
 *	-1			:	�޼�ֵ����
 *	0~9			:	0x00~0x09	
 *	*				��0x0A
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










