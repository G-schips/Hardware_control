#ifndef __LCD1602_H__
#define __LCD1602_H__

/*	此处只有函数声明，更多详情请访问.c文件			*/

/*	注：文件应该没问题，引用时报错是因为部分函数没有被调用		*/

#define uchar unsigned char
#define uint  unsigned int

/*	注：此处默认了各种硬件接口，另有需要请手动修改		*/
#define OutPort P1		//定义LCD的输出口
#define LCD_RS P2^2 		//定义LCD1602端口
#define LCD_RW P2^1		//定义LCD1602端口
#define LCD_EN P2^0		//定义LCD1602端口


extern void lcd_init();					//初始化LCD
extern void lcd_setCursor(bit c,bit b);				//置光标属性
extern void lcd_reSetCursor();				//光标复位（光标返回到地址00H）
extern void lcd_setRoll(bit sc,bit rl);				//移动光标或者滚屏一次
extern void lcd_showString(uchar *string,uchar x,uchar y);	//LCD显示字符串
extern void lcd_setPos(uint x,uchar y);				//设定写字符时的位置
extern void lcd_showCharInLine(uchar charr,uint x,uchar y);	//写字符到位置xy
extern void lcd_clr();					//LCD清屏
extern void lcd_dbSetBit(bit db7,bit db6,bit db5,bit db4,bit db3,bit db2,bit db1,bit db0);			//置LCD数据位
//============内部程序,不需要理会========//
static bit lcd_busy();
static void lcd_wcmd(uchar cmd);
static void lcd_wdat(uchar dat);

#endif
