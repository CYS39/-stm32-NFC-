#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  


//////////////////////////////////////////////////////////////////////////////////////////////////////
#define STM32_FLASH_SIZE 256 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1              //使能FLASH写入(0，不是能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
//FLASH解锁键值
#define FLASH_SAVE_ADDR 0X08032000
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据

void ErasePage(u32 WriteAddress, u8 Num);            //清除WriteAddress地址起的Num个扇区

//测试写入
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif








/*
flash写入一次为十六为两个字节，所以地址每次写入会加二 STMFLASH_Write传入的地址也必须为二的倍数
STMFLASH_Write函数传入八位数组会被强制转换成十六位数据 两个八位合成一个十六位
所以四个八位数据写入 STMFLASH_Write的参数NumToRead应该为2  因为四个八位数据会被合成两个十六位数据
但地址是增加了8
flash一位地址存一个八位数据  但一次写十六位数据，地址加二



	
char pass[8] = {2, 3, 4, 5, 6, 1, 0, 0};
char dat[16];

char 是四位

STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)pass, 4);
STMFLASH_Read(FLASH_SAVE_ADDR, (u16*)dat, 4);

当
int pass[8] = {2, 3, 4, 5, 6, 1, 0, 0};
char dat[16];
dat是四位存放pass的一个数。

实验，数组不同数据类型存放，得出结论。


*/







