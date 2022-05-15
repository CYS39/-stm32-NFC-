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
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

void ErasePage(u32 WriteAddress, u8 Num);            //���WriteAddress��ַ���Num������

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif








/*
flashд��һ��Ϊʮ��Ϊ�����ֽڣ����Ե�ַÿ��д���Ӷ� STMFLASH_Write����ĵ�ַҲ����Ϊ���ı���
STMFLASH_Write���������λ����ᱻǿ��ת����ʮ��λ���� ������λ�ϳ�һ��ʮ��λ
�����ĸ���λ����д�� STMFLASH_Write�Ĳ���NumToReadӦ��Ϊ2  ��Ϊ�ĸ���λ���ݻᱻ�ϳ�����ʮ��λ����
����ַ��������8
flashһλ��ַ��һ����λ����  ��һ��дʮ��λ���ݣ���ַ�Ӷ�



	
char pass[8] = {2, 3, 4, 5, 6, 1, 0, 0};
char dat[16];

char ����λ

STMFLASH_Write(FLASH_SAVE_ADDR, (u16*)pass, 4);
STMFLASH_Read(FLASH_SAVE_ADDR, (u16*)dat, 4);

��
int pass[8] = {2, 3, 4, 5, 6, 1, 0, 0};
char dat[16];
dat����λ���pass��һ������

ʵ�飬���鲻ͬ�������ʹ�ţ��ó����ۡ�


*/







