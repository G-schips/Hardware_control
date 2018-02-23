#ifndef __LCD1602_H__
#define __LCD1602_H__

/*	�˴�ֻ�к����������������������.c�ļ�			*/

/*	ע���ļ�Ӧ��û���⣬����ʱ��������Ϊ���ֺ���û�б�����		*/

#define uchar unsigned char
#define uint  unsigned int

/*	ע���˴�Ĭ���˸���Ӳ���ӿڣ�������Ҫ���ֶ��޸�		*/
#define OutPort P1		//����LCD�������
#define LCD_RS P2^2 		//����LCD1602�˿�
#define LCD_RW P2^1		//����LCD1602�˿�
#define LCD_EN P2^0		//����LCD1602�˿�


extern void lcd_init();					//��ʼ��LCD
extern void lcd_setCursor(bit c,bit b);				//�ù������
extern void lcd_reSetCursor();				//��긴λ����귵�ص���ַ00H��
extern void lcd_setRoll(bit sc,bit rl);				//�ƶ������߹���һ��
extern void lcd_showString(uchar *string,uchar x,uchar y);	//LCD��ʾ�ַ���
extern void lcd_setPos(uint x,uchar y);				//�趨д�ַ�ʱ��λ��
extern void lcd_showCharInLine(uchar charr,uint x,uchar y);	//д�ַ���λ��xy
extern void lcd_clr();					//LCD����
extern void lcd_dbSetBit(bit db7,bit db6,bit db5,bit db4,bit db3,bit db2,bit db1,bit db0);			//��LCD����λ
//============�ڲ�����,����Ҫ���========//
static bit lcd_busy();
static void lcd_wcmd(uchar cmd);
static void lcd_wdat(uchar dat);

#endif
