#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  


//////////////////////////////////////////////////////////////////////////////////////////////////////
#define STM32_FLASH_SIZE 256 	 		//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
//FLASH������ֵ
#define FLASH_SAVE_ADDR 0X08032000
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //��������  
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
void ErasePage(u32 WriteAddress, u8 Num);            //���WriteAddress��ַ���Num������

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif















