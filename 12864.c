#include "reg52.h"
#incdude "lcd12864.h"

void LCD12864_P_clrScreen()
{

/*	程序名：	LCD12864_ClrScreen

	程序功能：	清屏 。

	调用参数：	无。

*/
  P_write_cmd(0x01);
  lcd1268_delayms(15);
}


void P_check_busy()
/*	内部函数，无须理会	*/
/*	检测是否忙，是则等待	*/  
  lcd12864_rs = 0;
  lcd12864_rw = 1;
  lcd12864_en = 1;
  while ((LCD12864_Outport&0x80) == 0x80);
  lcd12864_en=0;
}

void P_write_cmd(unsigned char cmd)
{
/*	内部函数，无须理会	*/
/*	向LCD12964写命令函数	*/ 
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
/*	内部函数，无须理会	*/  
/*	向LCD12964写数据函数	*/ 
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
	程序名：	init_st7920

	程序功能：	初始化并行驱动器 。

	调用参数：	无。

	说明：		在并行传输中必须先调用本函数初始化

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
/*	内部函数，无须理会	*/  

 while(t--)
 {
	lcd1268_delayus2x(245);
	lcd1268_delayus2x(245);
 }
}
void lcd1268_U_delayus2x(unsigned char t)
{
/*	内部函数，无须理会	*/   
	while(--t);
}
void write_U_12864dat(unsigned char dat,unsigned char flag)
{
/*	内部函数，无须理会	*/

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

/*	程序名：	LCD12864_lineDisp

	程序功能：	显示字 。

	调用参数：	

		*p	要显示的字符

		lend	显示长度;不能超过8个字

		row	放置行数;不能超过4行

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
/*	程序名：	LCD12864_init

	程序功能：	初始化LCD12864。

	调用参数：	无。

	说明：		在串行传输中所用的初始化函数。
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


