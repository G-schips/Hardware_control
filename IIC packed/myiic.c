#include "myiic.h"
#include "delay.h"

void IIC_Init(void)
{
//IIC��ʼ��
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOG_CLK_ENABLE();   //ʹ��GPIOHʱ��
    
    //PH4,5��ʼ������
    GPIO_Initure.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    IIC_SDA_OUT=1;
    IIC_SCL=1;  
}


void IIC_Start(void)
{
//����IIC��ʼ�ź�
	SDA_OUT();     //sda�����
	IIC_SDA_OUT=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA_OUT=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

void IIC_Stop(void)
{
//����IICֹͣ�ź�
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA_OUT=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA_OUT=1;//����I2C���߽����ź�
	delay_us(4);							   	
}

u8 IIC_Wait_Ack(void)
{
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_OUT=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(IIC_SDA_IN)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA_OUT=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA_OUT=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA_OUT=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    

u8 IIC_Read_Byte(unsigned char ack)
{
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK  
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA_IN)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
/*
void IIC_SDA_Mode(u8 mode)
{
	if(mode == GPIO_MODE_OUTPUT_PP)
	{
		SDA_OUT();
	}else
	{
		SDA_IN();
	}
}
*/
