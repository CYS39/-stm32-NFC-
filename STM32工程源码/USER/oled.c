#include "name.h"


int i;
u8 bulk,serve_flag;         // oled_write_font 写入中文和英文时不同字体的像素大小


/*
 *	OLED 屏幕和stm32进行iic通讯基础函数
 *	dat  需要通讯的内容 ： 一个字节
 *	mode 模式 ： 命令 或 数据
 */
void OLED_WR_Byte(u8 dat,u8 mode)
{
	IIC_Start();
	IIC_Send_Byte(0x78);
	IIC_Wait_Ack();
	if(mode) IIC_Send_Byte(0x40);
  else IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	IIC_Send_Byte(dat);
	IIC_Wait_Ack();
	IIC_Stop();
} 


/*
 *	写入单个字符 x y ：开始坐标（第几列和第几页） p需要写入的字符 type 	写入的字符类型 才cn、asc
 */
void oled_write_font(char x, char y, char *p, u8 type)
{
	
	if(type) bulk = 0x0f;
	else bulk = 0x07;
	OLED_WR_Byte(0x20,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0x21,OLED_CMD);
	OLED_WR_Byte(x,OLED_CMD);
	OLED_WR_Byte(x+bulk,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);
	OLED_WR_Byte(y,OLED_CMD);
	OLED_WR_Byte(y+0x01,OLED_CMD);
	
	for( i=0;i<(2*bulk+1);i++ )
	{
	
		OLED_WR_Byte(p[i],OLED_DATA);
		
	}
	
}


/*
 *	清屏
 */
void OLED_Clear(void)
{

	int i;
	
	OLED_WR_Byte(0x20,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0x21,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xFF,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0x07,OLED_CMD);
	
	for( i=0;i<1024;i++ )
	{
	
		OLED_WR_Byte(0x00,OLED_DATA);
		
	}
	
}


/*
 *	OLED 初始化工作
 */
void OLED_Init()
{
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x00,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_WR_Byte(0x21,OLED_CMD);	
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xFF,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);	
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0x07,OLED_CMD);
	OLED_Clear();
	
}


/*
 *	写入单个ascii码 x y：坐标chr需要写入的ascii码
 */
void oled_write_str(char x, char y, u8 chr)         //
{
	
	chr = chr - ' ';
	OLED_WR_Byte(0x20,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0x21,OLED_CMD);
	OLED_WR_Byte(x,OLED_CMD);
	OLED_WR_Byte(x+0x07,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);
	OLED_WR_Byte(y,OLED_CMD);
	OLED_WR_Byte(y+0x01,OLED_CMD);
	
	for(i = 0; i < 16; i++)
	{
	
		OLED_WR_Byte(asc2_1608[chr][i],OLED_DATA);
		
	}
	
}


/*
 *	写入字符串  参数和写入单个字符一样 写入字符长度
 */
void oled_write_string(char x, char y, char *p, u8 len)
{
	
	u8 str_x = x;
	for(u8 i = 0; i < len; i++)
	{
		
		u8 place = p[i];
		oled_write_str(str_x, y, place);
		str_x = str_x + 0x08;
		
	}
	
}


// 显示时间页面
void oled_time(){
	
	// 年月日
	oled_write_font(0x28, 0x01, China_1616[0], cn);
	oled_write_font(0x48, 0x01, China_1616[1], cn);
	oled_write_font(0x68, 0x01, China_1616[2], cn);
	
	// ：.
	oled_write_str(0x38, 0x03, ':');
	oled_write_str(0x50, 0x03, '.');
	
	// 时间
	oled_write_str(0x08, 0x01, (calendar.w_year/1000) 		+ 48);
	oled_write_str(0x10, 0x01, (calendar.w_year%1000/100) + 48);
	oled_write_str(0x18, 0x01, (calendar.w_year%100/10) 	+ 48);
	oled_write_str(0x20, 0x01, (calendar.w_year%10) 			+ 48);
	
	oled_write_time(calendar.w_month, 0x38, 0x01);
	oled_write_time(calendar.w_date, 	0x58, 0x01);
	oled_write_time(calendar.hour, 		0x28, 0x03);
	oled_write_time(calendar.min, 		0x40, 0x03);
	oled_write_time(calendar.sec, 		0x58, 0x03);
	
	// 状态：
	oled_write_font(0x00, 0x06, China_1616[19], cn);
	oled_write_font(0x10, 0x06, China_1616[20], cn);
	oled_write_str(0x20, 0x06, ':');
	
	// 菜单
	oled_write_font(0x58, 0x06, China_1616[21], cn);
	oled_write_font(0x68, 0x06, China_1616[22], cn);
	
}


// 更新时间
void oled_update_time(){
	
	oled_write_time(calendar.sec, 0x58, 0x03);
	if(calendar.sec == 0){
		
		oled_write_time(calendar.min, 0x40, 0x03);
		if(calendar.min == 0){
		
			oled_write_time(calendar.hour, 0x28, 0x03);
			if(calendar.hour == 0){
			
				oled_write_time(calendar.w_date, 0x58, 0x01);
				oled_write_time(calendar.w_month, 0x38, 0x01);
			
			}
		
		}
		
	}
	
}


// 写时间
void oled_write_time(int dat, int x, int y){
	
	oled_write_str(x		, y, (dat/10) + 48);
	oled_write_str(x + 8, y, (dat%10) + 48);
	
}


// 显示键值
void oled_key_value(int value, int x, int y){
	
	oled_write_str(x, y, value);
	
}


void oled_lock_state(){
	
	if(lock_state) oled_write_font(0x28, 0x06, China_1616[17], cn);
	else oled_write_font(0x28, 0x06, China_1616[18], cn);
	
}


// 菜单
void oled_menu(){
	
	// 菜单
	oled_write_font(0x38, 0x00, China_1616[21], cn);
	oled_write_font(0x48, 0x00, China_1616[22], cn);
	
	// 更改密码
	oled_write_font(0x00, 0x02, China_1616[23], cn);
	oled_write_font(0x10, 0x02, China_1616[24], cn);
	oled_write_font(0x20, 0x02, China_1616[3], cn);
	oled_write_font(0x30, 0x02, China_1616[4], cn);
	
	// 更改时间
	oled_write_font(0x00, 0x04, China_1616[23], cn);
	oled_write_font(0x10, 0x04, China_1616[24], cn);
	oled_write_font(0x20, 0x04, China_1616[25], cn);
	oled_write_font(0x30, 0x04, China_1616[26], cn);
	
	// 管理员
	oled_write_font(0x00, 0x06, China_1616[14], cn);
	oled_write_font(0x10, 0x06, China_1616[15], cn);
	oled_write_font(0x20, 0x06, China_1616[16], cn);
	
}


// 选择效果图
void oled_select_pic(int x, int y){
	
	oled_write_font(x, 0x02, China_1616[28], cn);
	oled_write_font(x, 0x04, China_1616[28], cn);
	oled_write_font(x, 0x06, China_1616[28], cn);
	oled_write_font(x, y, China_1616[27], cn);
	
}


// 更改效果图
void oled_change_pic(int x, int y){
	
	oled_write_str(x, y, '_');
	
}


// 更改时间
void oled_change_time(){
	
		// 年月日
	oled_write_font(0x28, 0x01, China_1616[0], cn);
	oled_write_font(0x48, 0x01, China_1616[1], cn);
	oled_write_font(0x68, 0x01, China_1616[2], cn);
	
	// ：.
	oled_write_str(0x38, 0x03, ':');
	oled_write_str(0x50, 0x03, '.');
	
	// 时间
	oled_write_str(0x08, 0x01, (calendar.w_year/1000) 		+ 48);
	oled_write_str(0x10, 0x01, (calendar.w_year%1000/100) + 48);
	oled_write_str(0x18, 0x01, (calendar.w_year%100/10) 	+ 48);
	oled_write_str(0x20, 0x01, (calendar.w_year%10) 			+ 48);
	
	oled_write_time(calendar.w_month, 0x38, 0x01);
	oled_write_time(calendar.w_date, 	0x58, 0x01);
	oled_write_time(calendar.hour, 		0x28, 0x03);
	oled_write_time(calendar.min, 		0x40, 0x03);
	oled_write_time(calendar.sec, 		0x58, 0x03);
	
}


void oled_unlock(){
	
	// 请输入六位密码：
	oled_write_font(0x00, 0x01, China_1616[31], cn);
	oled_write_font(0x10, 0x01, China_1616[10], cn);
	oled_write_font(0x20, 0x01, China_1616[11], cn);
	oled_write_font(0x30, 0x01, China_1616[29], cn);
	oled_write_font(0x40, 0x01, China_1616[30], cn);
	oled_write_font(0x50, 0x01, China_1616[3], cn);
	oled_write_font(0x60, 0x01, China_1616[4], cn);
	oled_write_str(0x70, 0x01, ':');
	
}


// 密码对比结果
// 1	密码正确 门锁已打开
// 0 	密码错误 请重新输入
void oled_pass_result(char ret){
	
	OLED_Clear();																// oled清屏
	if(ret){
		
		oled_write_font(0x20, 0x01, China_1616[3], cn);
		oled_write_font(0x30, 0x01, China_1616[4], cn);
		oled_write_font(0x40, 0x01, China_1616[7], cn);
		oled_write_font(0x50, 0x01, China_1616[8], cn);
		oled_write_font(0x18, 0x04, China_1616[32], cn);
		oled_write_font(0x28, 0x04, China_1616[33], cn);
		oled_write_font(0x38, 0x04, China_1616[34], cn);
		oled_write_font(0x48, 0x04, China_1616[35], cn);
		oled_write_font(0x58, 0x04, China_1616[17], cn);
		
	}
	else{
		
		oled_write_font(0x20, 0x01, China_1616[3], cn);
		oled_write_font(0x30, 0x01, China_1616[4], cn);
		oled_write_font(0x40, 0x01, China_1616[5], cn);
		oled_write_font(0x50, 0x01, China_1616[6], cn);
		oled_write_font(0x18, 0x04, China_1616[9], cn);
		oled_write_font(0x28, 0x04, China_1616[36], cn);
		oled_write_font(0x38, 0x04, China_1616[37], cn);
		oled_write_font(0x48, 0x04, China_1616[10], cn);
		oled_write_font(0x58, 0x04, China_1616[11], cn);
		
	}
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
}


// 请输入管理员密码
void oled_input_man_pass(){
	
	oled_write_font(0x00, 0x01, China_1616[10], cn);
	oled_write_font(0x10, 0x01, China_1616[11], cn);
	oled_write_font(0x20, 0x01, China_1616[14], cn);
	oled_write_font(0x30, 0x01, China_1616[15], cn);
	oled_write_font(0x40, 0x01, China_1616[16], cn);
	oled_write_font(0x50, 0x01, China_1616[3], cn);
	oled_write_font(0x60, 0x01, China_1616[4], cn);
	oled_write_str(0x70, 0x01, ':');
	
}


// 更改密码
// 1 确认新密码
// 0 输入新密码
void oled_change_pass(char arg){
	
	if(arg){
		
		oled_write_font(0x00, 0x01, China_1616[8], cn);
		oled_write_font(0x10, 0x01, China_1616[13], cn);
		oled_write_font(0x20, 0x01, China_1616[12], cn);
		oled_write_font(0x30, 0x01, China_1616[3], cn);
		oled_write_font(0x40, 0x01, China_1616[4], cn);
		oled_write_str(0x50, 0x01, ':');
		
	}
	else{
		
		oled_write_font(0x00, 0x01, China_1616[10], cn);
		oled_write_font(0x10, 0x01, China_1616[11], cn);
		oled_write_font(0x20, 0x01, China_1616[12], cn);
		oled_write_font(0x30, 0x01, China_1616[3], cn);
		oled_write_font(0x40, 0x01, China_1616[4], cn);
		oled_write_str(0x50, 0x01, ':');
		
	}
	
}


// 密码更改结构
// 1   更改成功
// 0   前后不一致   请再次输入
void oled_change_pass_result(char arg){
	
	OLED_Clear();
	if(arg){
		
		oled_write_font(0x20, 0x01, China_1616[23], cn);
		oled_write_font(0x30, 0x01, China_1616[24], cn);
		oled_write_font(0x40, 0x01, China_1616[38], cn);
		oled_write_font(0x50, 0x01, China_1616[39], cn);
		
	}
	else{
		
		oled_write_font(0x18, 0x01, China_1616[40], cn);
		oled_write_font(0x28, 0x01, China_1616[41], cn);
		oled_write_font(0x38, 0x01, China_1616[42], cn);
		oled_write_font(0x48, 0x01, China_1616[43], cn);
		oled_write_font(0x58, 0x01, China_1616[44], cn);
		
		oled_write_font(0x18, 0x03, China_1616[9], cn);
		oled_write_font(0x28, 0x03, China_1616[36], cn);
		oled_write_font(0x38, 0x03, China_1616[37], cn);
		oled_write_font(0x48, 0x03, China_1616[10], cn);
		oled_write_font(0x58, 0x03, China_1616[11], cn);
		
	}
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
}


// 管理员页面显示密码
void oled_man_shwo_pass(){
	
	OLED_Clear();
	
	// 门锁密码：
	oled_write_font(0x00, 0x01, China_1616[32], cn);
	oled_write_font(0x10, 0x01, China_1616[33], cn);
	oled_write_font(0x20, 0x01, China_1616[3], cn);
	oled_write_font(0x30, 0x01, China_1616[4], cn);
	oled_write_str(0x40, 0x01, ':');
	
	// 密码
	oled_write_string(0x00, 0x03, pass, 6);
	
}


// 警报显示
void oled_alarm(){
	
	OLED_Clear();
	
	// 已错误三次
	oled_write_font(0x18, 0x01, China_1616[34], cn);
	oled_write_font(0x28, 0x01, China_1616[5], cn);
	oled_write_font(0x38, 0x01, China_1616[6], cn);
	oled_write_font(0x48, 0x01, China_1616[45], cn);
	oled_write_font(0x58, 0x01, China_1616[37], cn);
	
	// 门锁已锁死
	oled_write_font(0x18, 0x03, China_1616[32], cn);
	oled_write_font(0x28, 0x03, China_1616[33], cn);
	oled_write_font(0x38, 0x03, China_1616[34], cn);
	oled_write_font(0x48, 0x03, China_1616[33], cn);
	oled_write_font(0x58, 0x03, China_1616[46], cn);
	
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
}



