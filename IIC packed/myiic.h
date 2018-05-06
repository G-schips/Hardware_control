#ifndef _MYIIC_H
#define _MYIIC_H
#include "sys.h"

//IO��������
#define SDA_IN()  {GPIOG->MODER&=~(3<<(3*2));GPIOG->MODER|=0<<3*2;}	//PH5����ģʽ
#define SDA_OUT() {GPIOG->MODER&=~(3<<(3*2));GPIOG->MODER|=1<<3*2;} //PH5���ģʽ

#define IIC_SCL			PGout(2) //SCL
#define IIC_SDA_OUT		PGout(3) //SDA
#define IIC_SDA_IN		PGin(3)  //����SDA

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
#endif

