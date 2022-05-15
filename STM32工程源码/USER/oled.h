#ifndef __OLED_H
#define __OLED_H


#include "sys.h"


#define OLED_CMD  0								// д����
#define OLED_DATA 1								// д����
#define asc 			0								// ascii�� ģʽ
#define cn 				1								// ���� ģʽ


void OLED_Init(void);																					// oled��ʼ��
void OLED_WR_Byte(u8 dat,u8 mode);                            // д���� ���� д����
void OLED_Clear(void);          															// oled����

// д�뵥���ַ� x y ����ʼ���꣨�ڼ��к͵ڼ�ҳ�� p��Ҫд����ַ� type 	д����ַ����� ��cn��asc
void oled_write_font(char x, char y, char *p, u8 type);  			

void oled_write_string(char x, char y, char *p, u8 len);      // д���ַ���  ������д�뵥���ַ�һ�� д���ַ�����
void oled_write_str(char x, char y, u8 chr);        					// д�뵥��ascii�� x y������chr��Ҫд���ascii��


void oled_time(void);
void oled_update_time(void);
void oled_write_time(int dat, int x, int y);

void oled_key_value(int value, int x, int y);
void oled_lock_state(void);
void oled_menu(void);
void oled_select_pic(int x, int y);
void oled_change_pic(int x, int y);
void oled_change_time(void);
void oled_unlock(void);
void oled_pass_result(char ret);
void oled_input_man_pass(void);
void oled_change_pass(char arg);
void oled_change_pass_result(char arg);
void oled_man_shwo_pass(void);
void oled_alarm(void);



#endif





