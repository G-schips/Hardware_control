// 带字库LCD12964
// 程序分为 并行传输P 以及 串行传输U 两个部分

#define __LCD12864_H__
#define uchar unsigned char
#define uint  unsigned int

/*	使用时请根据需要对下面语句进行修改	*/
#define  LCD12864_Outport P2
#define  LCD12864_RS P3^0
#define  LCD12864_RW P3^1
#define  LCD12864_EN P3^2
#define  LCD12864_RES P3^4
#define  LCD12864_PSB P3^5
#define  LCD12864_CLK P3^6
#define  LCD12864_SID P3^7
/*	使用时请根据需要对上面语句进行修改	*/


/*	以下定义不允许修改	*/
sbit lcd12864_rs = LCD12864_RS;
sbit lcd12864_rw = LCD12864_RW;
sbit lcd12864_en = LCD12864_EN;
sbit lcd12864_res = LCD12864_RES;
sbit lcd12864_psb = LCD12864_PSB;
sbit lcd12864_clk = LCD12864_CLK;
sbit lcd12864_sid = LCD12864_SID;
/*	以上定义不允许修改	*/

// 可用函数:

/*	并行传输用：
void LCD12864_P_clrScreen();
/*	程序名：	LCD12864_P_clrScreen

	程序功能：	清屏 。

	调用参数：	无。

*/

void LCD12864_P_init_st7920();
/*	
	程序名：	init_st7920

	程序功能：	初始化并行驱动器 。

	调用参数：	无。

	说明：		在并行传输中必须先调用本函数初始化

*/


///////////////////////////////////////
/*	内部函数，无须理会	*/

void lcd1268_U_delayms(unsigned int t);
/*	串行传输时需要的等待	*/ 

void lcd1268_U_delayus2x(unsigned char t);
/*	串行传输时需要的等待	*/ 
void P_check_busy();
/*	并行时检测是否忙，是则等待	*/  

void P_write_cmd(unsigned char cmd);
/*	并行时向LCD12964写命令函数	*/ 

void P_write_dat(unsigned char dat);
/*	并行时向LCD12964写数据函数	*/ 


///////////////////////////////////
/*	以下是串行传输调用所用函数	*/

void LCD12864_U_lineDisp(unsigned char *p,unsigned char lend,unsigned char row);
/*	程序名：	LCD12864_U_lineDisp

	程序功能：	串行传输时显示字 。

	调用参数：	

		*p	要显示的字符

		lend	显示长度;不能超过8个字

		row	放置行数;不能超过4行

*/

void LCD12864_U_init();
/*	程序名：	LCD12864_U_init

	程序功能：	串行传输时初始化LCD12864。

	调用函数：	无。
*/



void write_U_12864dat(unsigned char dat,unsigned char flag);
/*	串行传输时需要的写操作	
	调用参数：	

		dat	要写入的数据或者命令

		flag	0写命令；1写数据

/*
