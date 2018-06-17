/*
    PC3----->LCD_CS
		PC4----->LCD_RST
		PC5----->LCD_RS
		PC6----->LCD_SDA
		PC7----->LCD_SCK
		3V3----->LCD_VDD
		GND----->LCD_VSS
		3V3----->LCD_LEDA
*/

# ifndef __12864_H
# define __12864_H
# include "sys.h"

//Ƭѡ
# define LCD_CS_0()   GPIO_ResetBits(GPIOC, GPIO_Pin_3)
# define LCD_CS_1()   GPIO_SetBits(GPIOC, GPIO_Pin_3)

//��λ��
# define LCD_RST_0()  GPIO_ResetBits(GPIOC, GPIO_Pin_4)
# define LCD_RST_1()  GPIO_SetBits(GPIOC, GPIO_Pin_4)

//����/���ݼĴ���ѡ��
# define LCD_RS_0()   GPIO_ResetBits(GPIOC, GPIO_Pin_5)
# define LCD_RS_1()   GPIO_SetBits(GPIOC, GPIO_Pin_5)

//���ݿ�
# define LCD_DAT_0()  GPIO_ResetBits(GPIOC, GPIO_Pin_6)
# define LCD_DAT_1()  GPIO_SetBits(GPIOC, GPIO_Pin_6)

//ʱ�ӿ�
# define LCD_SCLK_0() GPIO_ResetBits(GPIOC, GPIO_Pin_7)
# define LCD_SCLK_1() GPIO_SetBits(GPIOC, GPIO_Pin_7)

//IO�ڳ�ʼ��
void MYGPIO_Init(void);

//��ʼ��LCD
void LCD_Init(void);

//����
void LCD_Clear_Screen(void);

//�����
void LCD_Clear_Line(u8 _X);

//��LCD����8�ֽ�����
void LCD_Send_8Bits(u8 dat);

//��LCDдָ��
void LCD_Send_Order(u8 cmd);

//��LCDд����
void LCD_Send_Data(u8 dat);

//��ʾ����
void LCD_HZ(u8 x, u8 y, u8 dat);

//ѡ�к���
void LCD_HZ_OP(u8 x, u8 y,  u8 dat);

//��ʾ�ַ���
void LCD_HZS(u8 x,u8 y,u8 *string);

//ѡ���ַ���
void LCD_HZS_OP(u8 x,u8 y,u8 *string);

//��������
void LCD_Add_XY(u8 x, u8 y);

//��ʾASCALL�ַ�
void LCD_ASCALL(u8 c);

//ѡ��ASCALL
void LCD_ASCALL_OP(u8 c);

//��ʾ�ַ���
void LCD_ASCALLS(u8 *string);

//ѡ���ַ���
void LCD_ASCALLS_OP(u8 *string);

//��ʾ����
void LCD_int(int dat);
	
# endif


