#include "iic.h"


void IIC_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	

  IIC_SCL=1;
	IIC_SDA=1;	
	
}

void IIC_Start(void)
{

	SDA_OUT();
	IIC_SCL = 1;
	IIC_SDA = 1;
	delay_us(4);
	IIC_SDA = 0;
  delay_us(4);
  IIC_SCL = 0;
	
}



void IIC_Stop(void)
{

	SDA_OUT();
	IIC_SCL = 0;
	IIC_SDA = 0;
  delay_us(4);	
	IIC_SCL = 1;
  delay_us(4);
	IIC_SDA = 1;	
  delay_us(4);	
	
}



u8 IIC_Wait_Ack(void)
{

	u8 WaitTime = 0;
	SDA_IN();
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 	
	while(READ_SDA)
	{
		
		WaitTime++;
		if(WaitTime>250)
		{
			
			IIC_Stop();
			return 1;
			
		}
	}
	
	IIC_SCL = 0;
	return 0;
	

}


void IIC_Ack(void)
{

	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;

}

void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}	

void IIC_Send_Byte(u8 txd)
{

	u8 t;
	SDA_OUT();
	IIC_SCL = 0;
	for( t=0;t<8;t++ )
	{
		
		IIC_SDA=(txd&0x80)>>7;
    txd<<=1;
		delay_us(2);
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
		
	}

}


u8 IIC_Read_Byte(unsigned char ack)
{

	unsigned char i,receive = 0;
	SDA_IN();
	for( i=0;i<8;i++ )
	{
	
		IIC_SCL = 0;
		delay_us(2);
		IIC_SCL = 1;
		receive<<=1;
		if(READ_SDA)
			receive++;
		delay_us(2);
	
	}

	if (!ack)
     IIC_NAck();//·¢ËÍnACK
  else
     IIC_Ack(); //·¢ËÍACK   
  return receive;

}






