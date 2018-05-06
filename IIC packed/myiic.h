#ifndef _MYIIC_H
#define _MYIIC_H
#include "sys.h"

//IO方向设置
#define SDA_IN()  {GPIOG->MODER&=~(3<<(3*2));GPIOG->MODER|=0<<3*2;}	//PH5输入模式
#define SDA_OUT() {GPIOG->MODER&=~(3<<(3*2));GPIOG->MODER|=1<<3*2;} //PH5输出模式

#define IIC_SCL			PGout(2) //SCL
#define IIC_SDA_OUT		PGout(3) //SDA
#define IIC_SDA_IN		PGin(3)  //输入SDA

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
#endif

