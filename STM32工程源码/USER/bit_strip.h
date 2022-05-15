#ifndef __BIT_STRIP_H
#define __BIT_STRIP_H	

#include "stm32f10x.h"
 
//位带输出
#define GPIOA_ODR_Addr 		(GPIOA_BASE + 0X0C)
#define GPIOB_ODR_Addr 		(GPIOB_BASE + 0X0C)
#define GPIOC_ODR_Addr 		(GPIOC_BASE + 0X0C)
#define GPIOD_ODR_Addr		(GPIOD_BASE + 0X0C)
#define GPIOE_ODR_Addr 		(GPIOE_BASE + 0X0C)
#define GPIOF_ODR_Addr 		(GPIOF_BASE + 0X0C)
#define GPIOG_ODR_Addr 		(GPIOG_BASE + 0X0C)
 
#define PAout(n) 	*(volatile unsigned int *)((GPIOA_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOA_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PBout(n)	*(volatile unsigned int *)((GPIOB_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOB_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PCout(n) 	*(volatile unsigned int *)((GPIOC_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOC_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2)) 
#define PDout(n) 	*(volatile unsigned int *)((GPIOD_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOD_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PEout(n) 	*(volatile unsigned int *)((GPIOE_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOE_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PFout(n) 	*(volatile unsigned int *)((GPIOF_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOF_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PGout(n) 	*(volatile unsigned int *)((GPIOG_ODR_Addr & 0xF0000000) + 0X02000000 + ((GPIOG_ODR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
 
//位带输入
#define GPIOA_IDR_Addr 		(GPIOA_BASE + 0X08)
#define GPIOB_IDR_Addr 		(GPIOB_BASE + 0X08)
#define GPIOC_IDR_Addr 		(GPIOC_BASE + 0X08)
#define GPIOD_IDR_Addr 		(GPIOD_BASE + 0X08)
#define GPIOE_IDR_Addr 		(GPIOE_BASE + 0X08)
#define GPIOF_IDR_Addr 		(GPIOF_BASE + 0X08)
#define GPIOG_IDR_Addr 		(GPIOG_BASE + 0X08)
 
#define PAin(n) 	*(volatile unsigned int *)((GPIOA_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOA_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PBin(n) 	*(volatile unsigned int *)((GPIOB_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOB_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PCin(n) 	*(volatile unsigned int *)((GPIOC_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOC_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PDin(n) 	*(volatile unsigned int *)((GPIOD_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOD_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PEin(n) 	*(volatile unsigned int *)((GPIOE_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOE_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PFin(n) 	*(volatile unsigned int *)((GPIOF_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOF_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
#define PGin(n) 	*(volatile unsigned int *)((GPIOG_IDR_Addr & 0xF0000000) + 0X02000000 + ((GPIOG_IDR_Addr & 0x00FFFFFF) << 5) + ((n) << 2))
 

#endif
