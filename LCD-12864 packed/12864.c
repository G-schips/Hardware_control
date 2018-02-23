#include "reg52.h"
#incdude "lcd12864.h"

void LCD12864_P_clrScreen()
{

/*	��������	LCD12864_ClrScreen

	�����ܣ�	���� ��

	���ò�����	�ޡ�

*/
  P_write_cmd(0x01);
  lcd1268_delayms(15);
}


void P_check_busy()
/*	�ڲ��������������	*/
/*	����Ƿ�æ������ȴ�	*/  
  lcd12864_rs = 0;
  lcd12864_rw = 1;
  lcd12864_en = 1;
  while ((LCD12864_Outport&0x80) == 0x80);
  lcd12864_en=0;
}

void P_write_cmd(unsigned char cmd)
{
/*	�ڲ��������������	*/
/*	��LCD12964д�����	*/ 
  Check_busy();
  lcd12864_rs = 0;
  lcd12864_rw = 0;
  lcd12864_en = 1;
  LCD12864_Outport = cmd;
  lcd1268_delayus2x(5);
  lcd12864_en=0;
  lcd1268_delayus2x(5);
}

void P_write_dat(unsigned char dat)
{
/*	�ڲ��������������	*/  
/*	��LCD12964д���ݺ���	*/ 
  Check_busy();
  lcd12864_rs=1;
  lcd12864_rw=0;
  lcd12864_en=1;
  LCD12864_Outport=dat;
  lcd1268_delayus2x(5);
  lcd12864_en=0;
  lcd1268_delayus2x(5);
}

Void LCD12864_P_init_st7920()
{

/*	
	��������	init_st7920

	�����ܣ�	��ʼ������������ ��

	���ò�����	�ޡ�

	˵����		�ڲ��д����б����ȵ��ñ�������ʼ��

*/
  lcd1268_delayms(40);
  lcd12864_psb = 1;
  lcd1268_delayms(1);
  lcd12864_res = 0;
  lcd1268_delayms(1);
  lcd12864_res = 1;
  lcd1268_delayms(10);
  Write_cmd(0x30);
  lcd1268_delayus2x(50);
  Write_cmd(0x06);
  lcd1268_delayus2x(20);
  Write_cmd(0x0c);
  lcd1268_delayus2x(50);
  Write_cmd(0x01);
  lcd1268_delayms(15);
  Write_cmd(0x06);
}

void lcd1268_U_delayms(unsigned int t)
{
/*	�ڲ��������������	*/  

 while(t--)
 {
	lcd1268_delayus2x(245);
	lcd1268_delayus2x(245);
 }
}
void lcd1268_U_delayus2x(unsigned char t)
{
/*	�ڲ��������������	*/   
	while(--t);
}
void write_U_12864dat(unsigned char dat,unsigned char flag)
{
/*	�ڲ��������������	*/

	unsigned char i,j,k;
	lcd12864_clk = 0;
	lcd12864_sid = 1;
	for(i=0;i<5;i++)
	{
		lcd12864_clk = 1;
		lcd12864_clk = 0;
	}
	if(flag==0)
	{
		lcd12864_sid =  0;
		for(i=0;i<3;i++)
		{
			lcd12864_clk = 1;
			lcd12864_clk = 0;
		}
	}
	else
	{
		lcd12864_sid =  0;
		lcd12864_clk =  1;
		lcd12864_clk =  0;
		lcd12864_sid =  1;
		lcd12864_clk =  1;
		lcd12864_clk =  0;
		lcd12864_sid =  0;
		lcd12864_clk =  1;
		lcd12864_clk =  0;		
	}
	k = 0x80;
	for(j = 0;j < 2;j++)
	{
		for(i = 0;i < 4;i++)
		{
			if(dat&k)
			{
				lcd12864_sid =  1;
			}
			else
			 lcd12864_sid =  0;
			k >>= 1;
			lcd12864_clk =  1;
			lcd12864_clk =  0;
		}
		lcd12864_sid =  0;
		for(i = 0;i < 4;i++)
		{
			lcd12864_clk =  1;
			lcd12864_clk =  0;
		}
	}
	lcd12864_sid =  0;
}


void LCD12864_U_lineDisp(unsigned char *p,unsigned char lend,unsigned char row)
{

/*	��������	LCD12864_lineDisp

	�����ܣ�	��ʾ�� ��

	���ò�����	

		*p	Ҫ��ʾ���ַ�

		lend	��ʾ����;���ܳ���8����

		row	��������;���ܳ���4��

*/
	unsigned char i;
	switch(row)
	{
		case 1:
			write_12864dat(0x80,0);
		  break;
		case 2:
			write_12864dat(0x90,0);
		  break;
		case 3:
			write_12864dat(0x88,0);
		  break;
    case 4:
			write_12864dat(0x98,0);
		  break;	
    default: break;		
	}
	for(i = 0;i<lend - 1;i++)
	write_12864dat(p[i],1);
}

void LCD12864_U_init()
{
/*	��������	LCD12864_init

	�����ܣ�	��ʼ��LCD12864��

	���ò�����	�ޡ�

	˵����		�ڴ��д��������õĳ�ʼ��������
*/
	lcd1268_delayms(40);
	lcd12864_psb = 0;
	lcd1268_delayms(10);
	write_12864dat(0x30,0);
	lcd1268_delayus2x(50);
	write_12864dat(0x06,0);
	lcd1268_delayus2x(20);
	write_12864dat(0x0c,0);
	lcd1268_delayus2x(50);
	write_12864dat(0x01,0);
	lcd1268_delayms(15);
	write_12864dat(0x06,0);
}


