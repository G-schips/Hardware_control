/**************************************************************
*【编写时间】：	2016/10/14

*【作者】	      ：	薯条。

*【程序名称】：	LCD1602封装

*【运行环境】：	89c5x单片机（其他未测试）

*【程序亮点】：	傻瓜式封装，指针（lcd_showString），三目运算（lcd_showString）,位加法判断(lcd_setCursor)
		
*【可用函数】：
	lcd_init 						初始化

	void lcd_reInt					重初始化

	lcd_showCharInLine				LCD显示单个字符
		pamt1 显示的单个字符
		pamt2 所在位置x
		pamt3 所在行数y

	lcd_showString					LCD显示字符串	
		pamt1 显示的字符串
		pamt2 起始位置x
		pamt3 所在行数y

	lcd_setPos					设定写字符时的位置
		pamt1 所在位置x
		pamt2 所在行数y

	lcd_clr						LCD清屏

	lcd_setCursor					置LCD光标属性
		pamt1 光标是否显示
		pamt2 承上,光标是否闪烁

	lcd_dbSetBit					置LCD数据位
		pamt7个可直接写指令
		
*【例程】：
	void main()
	{
		lcd_init();		//使用前必须先初始化。
		lcd_showString("Test",0,0);
		while(1);
	}


************************************************************/
#include "lcd1602.h"
#include<reg52.h>			// 单片机程序文件头
#include<intrins.h>		// 类汇编程序头		用到了_nop_函数

#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};


/*下面的声明不可改动*/
#define Lcd_op OutPort
sbit Lcd_rs = LCD_RS;   	//定义LCD1602端口
sbit Lcd_rw = LCD_RW;		//定义LCD1602端口
sbit Lcd_en = LCD_EN;		//定义LCD1602端口

//bit  Lcd_cursor_sh=1;		//设定是否显示光标	(0:是,1否)		//我心想着应该某天就用上了吧。
//bit  Lcd_cursor_fl=1;		//设定光标是否闪烁	(0:是,1否)  	//虽然用了变量储存这些，但是我发现好像没用上的样子


static void lcd_delay(uchar x)
{
	/*  延时		*/
	unsigned char i;
	while(x--){for (i = 0; i<113; i++){}}
}
//============下面是程序=================//
extern void lcd_init()
{ 
	/*		LCD		初始化设定			*/
	/*		显示屏		锁定	开启	*/
	/*		屏幕移动	锁定	关闭	*/
	/*		数据长度	锁定	8bit		*/
	/*		显示行数	锁定	两行	*/
	/*		画面滚动	默认	光标移动*/
	/*		光标显示	默认	关闭	*/
	/*		光标闪烁	默认	关闭	*/

		lcd_delay(15);                   
		lcd_wcmd(0x38);      //16*2显示，5*8点阵，8位数据
		lcd_delay(5);
		lcd_wcmd(0x38);      //必须写3次0x38   
		lcd_delay(5);
		lcd_wcmd(0x38);         
		lcd_delay(5);
		lcd_wcmd(0x0c);      //显示开，关光标
		lcd_delay(5);
		lcd_wcmd(0x06);      //移动光标
		lcd_delay(5);
		lcd_wcmd(0x01);      //清除LCD的显示内容
		lcd_delay(5);
}

// 指令5：光标或显示移位 S/C：高电平时移动显示的文字，低电平时移动光标。
//	0    0    0    1    1    R/L    *    *
extern void lcd_setRoll(bit sc,bit lr)
{
	/*	LCD	移动光标或者滚屏一次	*/
	/*	参数1,移动1文字还是0光标	*/		
	/*	参数2,0左移还是1右移		*/
	//	0   0   0   1   S/C   R/L   X   X	//		习惯上置任意位x为0
	//  S/C：高电平时移动显示的文字，低电平时移动光标。
	//	上面这个是指令码D7到D0, 			//
	//	lr	等于0时,左移，等于1时，右移		//
	//注：当打开光标时，移动文字的时候光标将在跟随。
	//注：当移动光标时，必须确保光标已经显示。
   	lcd_dbSetBit(0,0,0,1,sc,lr,0,0);
	//Lcd_cursor_sh=c;   	//虽然用了变量储存这些，但是我发现好像没用上的样子
	//Lcd_cursor_fl=b;		//我心想着应该某天就用上了吧。
}
extern void lcd_setCursor(bit c,bit b)
{
	/*	LCD	设置光标属性		*/
	/*	参数1,1是0否显示光标	*/
	/*	参数2,1是0否闪烁光标	*/
	//	0	0	0	0	1	1	c	b			//
	//	上面这个是指令码D7到D0,			//
	//	c	等于1时,光标显示;等于0时禁止		//
	//	b	等于1时,光标闪烁;等于0时不闪		//

   	lcd_dbSetBit(0,0,0,0,1,1,c,b);
	//Lcd_cursor_sh=c;   	//虽然用了变量储存这些，但是我发现好像没用上的样子
	//Lcd_cursor_fl=b;		//我心想着应该某天就用上了吧。
}

extern void lcd_showCharInLine(uchar charr,uint x,uchar y)
{
	/*				LCD写显示字符					*/
	/*	参数1,用来输出的字符,不能超过16位,会被截取	*/
	/*	参数2,写出时的行数,	0是第一行;	1是第二行	*/
	/*	参数3,写出时的第几个位置,值不能超过15.		*/
	lcd_setPos(x,y); 
	lcd_wdat(charr);
}
void lcd_reSetCursor()
{
	lcd_wcmd(0x02);
}
	

void lcd_showString(uchar *string,uchar x,uchar y)
{
	/*	参数1,输出的字符串,不能超过16位		*/
	/*	参数2,所在列x,0到15					*/
	/*	参数3,所在行y,0到1		.			*/
	lcd_wcmd((y==0?0x80:0xc0)+x);
	while(*string!='\0')
	{
		lcd_wdat(*string);
		string++;
	}
}

extern void lcd_setPos(uint x,uchar y)
{
	/*	LCD写显示位置						*/
	/*	参数2,所在列x,0到15					*/
	/*	参数3,所在行y,0到1					*/
	lcd_wcmd((y==0?0x80:0xc0)+x);
}
extern void lcd_clr()
{
	/*	LCD清屏		*/	
	/*	光标归位	*/
	while(lcd_busy());
   	lcd_wcmd(0x01);      //清除LCD的显示内容
	lcd_delay(20);
}	

extern void lcd_dbSetBit(bit db7,bit db6,bit db5,bit db4,bit db3,bit db2,bit db1,bit db0)
{
	/*		LCD			数据指令直改		*/
	/*		参数1~8,都是指令码的某位		*/
	/*		有了这个函数,任何写指令可行		*/
	/*		直接修改LCD输出口的数据		*/
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

//============内部程序,不需要理会========//
static bit lcd_busy()
{                          
	/*检查LCD忙状态	*/
	/*lcd_busy为1时,忙,等待。			*/
	/*lcd-busy为0时,闲,可写指令与数据。	*/
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
	/*	写指令数据到LCD                     	*/
	/*	RS=L，RW=L，E=高脉冲，D0-D7=指令码。	*/
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
	/*	写显示数据到LCD                   		*/
	/*RS=H，RW=L，E=高脉冲，D0-D7=数据。		*/
	while(lcd_busy());
	Lcd_rs = 1;		//选择数据寄存器
	Lcd_rw = 0;		//选择写
	Lcd_en = 0;
	Lcd_op = dat;		//把要显示的数据送入Lcd_op口
	delayNOP();		//延时一小会儿，让1602准备接收数据,也就是检测忙信号
	Lcd_en = 1;		//使能线电平变化，数据送入1602的8位数据口
	delayNOP();
	Lcd_en = 0; 
}

	
