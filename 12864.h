// ���ֿ�LCD12964
// �����Ϊ ���д���P �Լ� ���д���U ��������

#define __LCD12864_H__
#define uchar unsigned char
#define uint  unsigned int

/*	ʹ��ʱ�������Ҫ�������������޸�	*/
#define  LCD12864_Outport P2
#define  LCD12864_RS P3^0
#define  LCD12864_RW P3^1
#define  LCD12864_EN P3^2
#define  LCD12864_RES P3^4
#define  LCD12864_PSB P3^5
#define  LCD12864_CLK P3^6
#define  LCD12864_SID P3^7
/*	ʹ��ʱ�������Ҫ�������������޸�	*/


/*	���¶��岻�����޸�	*/
sbit lcd12864_rs = LCD12864_RS;
sbit lcd12864_rw = LCD12864_RW;
sbit lcd12864_en = LCD12864_EN;
sbit lcd12864_res = LCD12864_RES;
sbit lcd12864_psb = LCD12864_PSB;
sbit lcd12864_clk = LCD12864_CLK;
sbit lcd12864_sid = LCD12864_SID;
/*	���϶��岻�����޸�	*/

// ���ú���:

/*	���д����ã�
void LCD12864_P_clrScreen();
/*	��������	LCD12864_P_clrScreen

	�����ܣ�	���� ��

	���ò�����	�ޡ�

*/

void LCD12864_P_init_st7920();
/*	
	��������	init_st7920

	�����ܣ�	��ʼ������������ ��

	���ò�����	�ޡ�

	˵����		�ڲ��д����б����ȵ��ñ�������ʼ��

*/


///////////////////////////////////////
/*	�ڲ��������������	*/

void lcd1268_U_delayms(unsigned int t);
/*	���д���ʱ��Ҫ�ĵȴ�	*/ 

void lcd1268_U_delayus2x(unsigned char t);
/*	���д���ʱ��Ҫ�ĵȴ�	*/ 
void P_check_busy();
/*	����ʱ����Ƿ�æ������ȴ�	*/  

void P_write_cmd(unsigned char cmd);
/*	����ʱ��LCD12964д�����	*/ 

void P_write_dat(unsigned char dat);
/*	����ʱ��LCD12964д���ݺ���	*/ 


///////////////////////////////////
/*	�����Ǵ��д���������ú���	*/

void LCD12864_U_lineDisp(unsigned char *p,unsigned char lend,unsigned char row);
/*	��������	LCD12864_U_lineDisp

	�����ܣ�	���д���ʱ��ʾ�� ��

	���ò�����	

		*p	Ҫ��ʾ���ַ�

		lend	��ʾ����;���ܳ���8����

		row	��������;���ܳ���4��

*/

void LCD12864_U_init();
/*	��������	LCD12864_U_init

	�����ܣ�	���д���ʱ��ʼ��LCD12864��

	���ú�����	�ޡ�
*/



void write_U_12864dat(unsigned char dat,unsigned char flag);
/*	���д���ʱ��Ҫ��д����	
	���ò�����	

		dat	Ҫд������ݻ�������

		flag	0д���1д����

/*
