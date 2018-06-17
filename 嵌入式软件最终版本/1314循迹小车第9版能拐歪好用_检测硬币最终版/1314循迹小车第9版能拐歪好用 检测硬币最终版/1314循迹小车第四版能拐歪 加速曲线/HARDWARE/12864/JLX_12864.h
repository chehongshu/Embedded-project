#ifndef _12864_H
#define _12864_H
#include "stm32f10x.h"

#ifndef _SHORT_CUT
#define uchar unsigned char 
#define uint unsigned int
#define ulong unsigned long
#endif
#define EPSILON 0.00001		 		//��ʾdoubleʱ�ľ��ȶ���
#define POINT_NUM  5		      //double��С������λ��


// Define the port of LCD12864
#define GPIO_LCD12864_CS    GPIOC
#define GPIO_LCD12864_RST   GPIOC
#define GPIO_LCD12864_RS  	GPIOC
#define GPIO_LCD12864_SID  	GPIOC
#define GPIO_LCD12864_SCLK  GPIOC
//#define GPIO_LCD12864_LED   GPIOC


// Define the pins of LCD12864
#define LCD12864_CS         GPIO_Pin_3
#define LCD12864_RST        GPIO_Pin_4
#define LCD12864_RS       	GPIO_Pin_5
#define LCD12864_SID       	GPIO_Pin_6
#define LCD12864_SCLK       GPIO_Pin_7
//#define LCD12864_LED        GPIO_Pin_8

// Define the clock of LCD12864
#define LCD12864_CLOCK      (RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB)


/*******************LCD12864�Ķ˿ڶ���********************/
#define J12864_CS1_1()   GPIO_SetBits(GPIO_LCD12864_CS,LCD12864_CS)		
#define J12864_CS1_0()   GPIO_ResetBits(GPIO_LCD12864_CS,LCD12864_CS)

#define J12864_RST_1()   GPIO_SetBits(GPIO_LCD12864_RST,LCD12864_RST)		
#define J12864_RST_0()   GPIO_ResetBits(GPIO_LCD12864_RST,LCD12864_RST)

#define J12864_RS_1()    GPIO_SetBits(GPIO_LCD12864_RS,LCD12864_RS)		
#define J12864_RS_0()    GPIO_ResetBits(GPIO_LCD12864_RS,LCD12864_RS)

#define J12864_SID_1()   GPIO_SetBits(GPIO_LCD12864_SID,LCD12864_SID)		
#define J12864_SID_0()   GPIO_ResetBits(GPIO_LCD12864_SID,LCD12864_SID)

#define J12864_SCLK_1()  GPIO_SetBits(GPIO_LCD12864_SCLK,LCD12864_SCLK) 	
#define J12864_SCLK_0()  GPIO_ResetBits(GPIO_LCD12864_SCLK,LCD12864_SCLK)

#define J12864_LED_1()   GPIO_SetBits(GPIO_LCD12864_LED,LCD12864_LED)		
#define J12864_LED_0()   GPIO_ResetBits(GPIO_LCD12864_LED,LCD12864_LED)

#define J12864_LIGHT_ON()  J12864_LED_1()
#define J12864_LIGHT_OFF() J12864_LED_0()




void delay_JLX(int n_ms);
void LCD12864_BSP_Init(void);
void transfer_command_lcd(int data1);
void transfer_data_lcd(int data1);
void initial_lcd(void);
void lcd_address(uint page,uint column);//��ַ
void clear_screen(void);
void J12864_Clear_Line(uchar _X);
void LCD12864_init(void);

void display_128x64(uchar *dp);
void display_graphic_16x16(uint page,uint column,uchar *dp);
void display_graphic_8x16(uint page,uchar column,uchar *dp);
void display_graphic_5x7(uint page,uchar column,uchar *dp);

void J12864_led_ASCALL(uint x,uint y,uchar c);
void J12864_led_ASCALLS(uint x,uint y,uchar *string);
void J12864_led_int(uint x,uint y,uint dat);
void J12864_led_double(uint x,uint y,double dat,uint point_n);
void J12864_led_double1(uint x,uint y,double dat,u8 z);//��ʾһλС��
void J12864_led_double2(uint x,uint y,double dat,u8 z);//��ʾ��λС��
void J12864_led_double3(uint x,uint y,double dat,u8 z);//��ʾ��λС��
void J12864_led_double4(uint x,uint y,double dat,u8 z);//��ʾ��λС��
void J12864_double1(uint x,uint y,double dat,u8 z);
void J12864_double2(uint x,uint y,double dat,u8 z);
void J12864_double3(uint x,uint y,double dat,u8 z);
void J12864_double4(uint x,uint y,double dat,u8 z);
void point(uchar x,uchar y);//��㺯��

extern  uchar  jiong1[];
extern  uchar  lei1[];
extern const uchar ASCALL[];
extern uchar goon;

#endif



/******************************ʹ��ʾ��***************************
#include "stm32f10x.h"
#include "12864.h"

int main()
{
  LCD12864_init();//12864��ʼ��
  J12864_led_int(1,1,250);
	while(1)
	{
	}
}	

******************************************************************/

