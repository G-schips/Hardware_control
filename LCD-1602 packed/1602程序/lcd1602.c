/**************************************************************
*����дʱ�䡿��	2016/10/14

*�����ߡ�	      ��	������

*���������ơ���	LCD1602��װ

*�����л�������	89c5x��Ƭ��������δ���ԣ�

*���������㡿��	ɵ��ʽ��װ��ָ�루lcd_showString������Ŀ���㣨lcd_showString��,λ�ӷ��ж�(lcd_setCursor)
		
*�����ú�������
	lcd_init 						��ʼ��

	void lcd_reInt					�س�ʼ��

	lcd_showCharInLine				LCD��ʾ�����ַ�
		pamt1 ��ʾ�ĵ����ַ�
		pamt2 ����λ��x
		pamt3 ��������y

	lcd_showString					LCD��ʾ�ַ���	
		pamt1 ��ʾ���ַ���
		pamt2 ��ʼλ��x
		pamt3 ��������y

	lcd_setPos					�趨д�ַ�ʱ��λ��
		pamt1 ����λ��x
		pamt2 ��������y

	lcd_clr						LCD����

	lcd_setCursor					��LCD�������
		pamt1 ����Ƿ���ʾ
		pamt2 ����,����Ƿ���˸

	lcd_dbSetBit					��LCD����λ
		pamt7����ֱ��дָ��
		
*�����̡���
	void main()
	{
		lcd_init();		//ʹ��ǰ�����ȳ�ʼ����
		lcd_showString("Test",0,0);
		while(1);
	}


************************************************************/
#include "lcd1602.h"
#include<reg52.h>			// ��Ƭ�������ļ�ͷ
#include<intrins.h>		// �������ͷ		�õ���_nop_����

#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};


/*������������ɸĶ�*/
#define Lcd_op OutPort
sbit Lcd_rs = LCD_RS;   	//����LCD1602�˿�
sbit Lcd_rw = LCD_RW;		//����LCD1602�˿�
sbit Lcd_en = LCD_EN;		//����LCD1602�˿�

//bit  Lcd_cursor_sh=1;		//�趨�Ƿ���ʾ���	(0:��,1��)		//��������Ӧ��ĳ��������˰ɡ�
//bit  Lcd_cursor_fl=1;		//�趨����Ƿ���˸	(0:��,1��)  	//��Ȼ���˱���������Щ�������ҷ��ֺ���û���ϵ�����


static void lcd_delay(uchar x)
{
	/*  ��ʱ		*/
	unsigned char i;
	while(x--){for (i = 0; i<113; i++){}}
}
//============�����ǳ���=================//
extern void lcd_init()
{ 
	/*		LCD		��ʼ���趨			*/
	/*		��ʾ��		����	����	*/
	/*		��Ļ�ƶ�	����	�ر�	*/
	/*		���ݳ���	����	8bit		*/
	/*		��ʾ����	����	����	*/
	/*		�������	Ĭ��	����ƶ�*/
	/*		�����ʾ	Ĭ��	�ر�	*/
	/*		�����˸	Ĭ��	�ر�	*/

		lcd_delay(15);                   
		lcd_wcmd(0x38);      //16*2��ʾ��5*8����8λ����
		lcd_delay(5);
		lcd_wcmd(0x38);      //����д3��0x38   
		lcd_delay(5);
		lcd_wcmd(0x38);         
		lcd_delay(5);
		lcd_wcmd(0x0c);      //��ʾ�����ع��
		lcd_delay(5);
		lcd_wcmd(0x06);      //�ƶ����
		lcd_delay(5);
		lcd_wcmd(0x01);      //���LCD����ʾ����
		lcd_delay(5);
}

// ָ��5��������ʾ��λ S/C���ߵ�ƽʱ�ƶ���ʾ�����֣��͵�ƽʱ�ƶ���ꡣ
//	0    0    0    1    1    R/L    *    *
extern void lcd_setRoll(bit sc,bit lr)
{
	/*	LCD	�ƶ������߹���һ��	*/
	/*	����1,�ƶ�1���ֻ���0���	*/		
	/*	����2,0���ƻ���1����		*/
	//	0   0   0   1   S/C   R/L   X   X	//		ϰ����������λxΪ0
	//  S/C���ߵ�ƽʱ�ƶ���ʾ�����֣��͵�ƽʱ�ƶ���ꡣ
	//	���������ָ����D7��D0, 			//
	//	lr	����0ʱ,���ƣ�����1ʱ������		//
	//ע�����򿪹��ʱ���ƶ����ֵ�ʱ���꽫�ڸ��档
	//ע�����ƶ����ʱ������ȷ������Ѿ���ʾ��
   	lcd_dbSetBit(0,0,0,1,sc,lr,0,0);
	//Lcd_cursor_sh=c;   	//��Ȼ���˱���������Щ�������ҷ��ֺ���û���ϵ�����
	//Lcd_cursor_fl=b;		//��������Ӧ��ĳ��������˰ɡ�
}
extern void lcd_setCursor(bit c,bit b)
{
	/*	LCD	���ù������		*/
	/*	����1,1��0����ʾ���	*/
	/*	����2,1��0����˸���	*/
	//	0	0	0	0	1	1	c	b			//
	//	���������ָ����D7��D0,			//
	//	c	����1ʱ,�����ʾ;����0ʱ��ֹ		//
	//	b	����1ʱ,�����˸;����0ʱ����		//

   	lcd_dbSetBit(0,0,0,0,1,1,c,b);
	//Lcd_cursor_sh=c;   	//��Ȼ���˱���������Щ�������ҷ��ֺ���û���ϵ�����
	//Lcd_cursor_fl=b;		//��������Ӧ��ĳ��������˰ɡ�
}

extern void lcd_showCharInLine(uchar charr,uint x,uchar y)
{
	/*				LCDд��ʾ�ַ�					*/
	/*	����1,����������ַ�,���ܳ���16λ,�ᱻ��ȡ	*/
	/*	����2,д��ʱ������,	0�ǵ�һ��;	1�ǵڶ���	*/
	/*	����3,д��ʱ�ĵڼ���λ��,ֵ���ܳ���15.		*/
	lcd_setPos(x,y); 
	lcd_wdat(charr);
}
void lcd_reSetCursor()
{
	lcd_wcmd(0x02);
}
	

void lcd_showString(uchar *string,uchar x,uchar y)
{
	/*	����1,������ַ���,���ܳ���16λ		*/
	/*	����2,������x,0��15					*/
	/*	����3,������y,0��1		.			*/
	lcd_wcmd((y==0?0x80:0xc0)+x);
	while(*string!='\0')
	{
		lcd_wdat(*string);
		string++;
	}
}

extern void lcd_setPos(uint x,uchar y)
{
	/*	LCDд��ʾλ��						*/
	/*	����2,������x,0��15					*/
	/*	����3,������y,0��1					*/
	lcd_wcmd((y==0?0x80:0xc0)+x);
}
extern void lcd_clr()
{
	/*	LCD����		*/	
	/*	����λ	*/
	while(lcd_busy());
   	lcd_wcmd(0x01);      //���LCD����ʾ����
	lcd_delay(20);
}	

extern void lcd_dbSetBit(bit db7,bit db6,bit db5,bit db4,bit db3,bit db2,bit db1,bit db0)
{
	/*		LCD			����ָ��ֱ��		*/
	/*		����1~8,����ָ�����ĳλ		*/
	/*		�����������,�κ�дָ�����		*/
	/*		ֱ���޸�LCD����ڵ�����		*/
	uchar cbd7,cbd6,cbd5,cbd4,cbd3,cbd2,cbd1,cbd0;
	signed char dbSum=0x00;
	cbd7=cbd6=cbd5=cbd4=cbd3=cbd2=cbd1=cbd0=0x00;
	if(db7==1)   cbd7=0x80;
	if(db6==1)   cbd6=0x40;	
	if(db5==1)   cbd5=0x20;
	if(db4==1)   cbd4=0x10;
	if(db3==1)   cbd3=0x08;
	if(db2==1)   cbd2=0x04;	
	if(db1==1)   cbd1=0x02;
	if(db0==1)   cbd0=0x01;
	dbSum= cbd7+cbd6+cbd5+cbd4+cbd3+cbd2+cbd1+cbd0;
	lcd_wcmd(dbSum);
}

//============�ڲ�����,����Ҫ���========//
static bit lcd_busy()
{                          
	/*���LCDæ״̬	*/
	/*lcd_busyΪ1ʱ,æ,�ȴ���			*/
	/*lcd-busyΪ0ʱ,��,��дָ�������ݡ�	*/
	bit result;	
	Lcd_rs = 0;
	Lcd_rw = 1;
	Lcd_en = 1;
	delayNOP();
	result = (bit)(Lcd_op&0x80);
	Lcd_en = 0;
	return(result); 
}

static void lcd_wcmd(uchar cmd)
{                          
	/*	дָ�����ݵ�LCD                     	*/
	/*	RS=L��RW=L��E=�����壬D0-D7=ָ���롣	*/
	while(lcd_busy());
	Lcd_rs = 0;
	Lcd_rw = 0;
	Lcd_en = 0;
	_nop_();
	_nop_(); 
	Lcd_op = cmd;
	delayNOP();
	Lcd_en = 1;
	delayNOP();
	Lcd_en = 0;  
}


static void lcd_wdat(uchar dat)
{                          
	/*	д��ʾ���ݵ�LCD                   		*/
	/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�		*/
	while(lcd_busy());
	Lcd_rs = 1;		//ѡ�����ݼĴ���
	Lcd_rw = 0;		//ѡ��д
	Lcd_en = 0;
	Lcd_op = dat;		//��Ҫ��ʾ����������Lcd_op��
	delayNOP();		//��ʱһС�������1602׼����������,Ҳ���Ǽ��æ�ź�
	Lcd_en = 1;		//ʹ���ߵ�ƽ�仯����������1602��8λ���ݿ�
	delayNOP();
	Lcd_en = 0; 
}

	
