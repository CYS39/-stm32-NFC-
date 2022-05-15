#ifndef __OLED_H
#define __OLED_H


#include "sys.h"


#define OLED_CMD  0								// 写命令
#define OLED_DATA 1								// 写数据
#define asc 			0								// ascii码 模式
#define cn 				1								// 中文 模式


void OLED_Init(void);																					// oled初始化
void OLED_WR_Byte(u8 dat,u8 mode);                            // 写数据 或者 写命令
void OLED_Clear(void);          															// oled清屏

// 写入单个字符 x y ：开始坐标（第几列和第几页） p需要写入的字符 type 	写入的字符类型 才cn、asc
void oled_write_font(char x, char y, char *p, u8 type);  			

void oled_write_string(char x, char y, char *p, u8 len);      // 写入字符串  参数和写入单个字符一样 写入字符长度
void oled_write_str(char x, char y, u8 chr);        					// 写入单个ascii码 x y：坐标chr需要写入的ascii码


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





