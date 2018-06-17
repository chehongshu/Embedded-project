#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "steper.h" 
#include "key.h" 
#include "movexy.h"
#include "ov7670.h"
#include "exti.h"
#include "lcd.h" 
//ALIENTEK Mini STM32�����巶������2
//��������ʵ��		   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
#define linecount 240
#define mean(x,y) (((x)+(y))>>1)
u32 y[linecount];
s32 aC,bC;
s32 aT,bT; //Ŀ��AB����
s32 aE,bE; //AB����λ��ʸ��
u32 x_min=240;
u32 x_max=0;
u32 y_min=320;
u32 y_max=0;
u32 x_start=0;
u32 y_start=0;
double stepnum = 392.16;  // ������
double xprepx;
double yprepx;
double xoffset;
double yoffset;
extern u8 ov_sta;
u16 RGB_565[19200];
u32 t=0;
u8 refresh_TFT_320()
{
	u16 i = 0 , j = 0 , k = 0;
	u16 color = 0;
	u8 temp = 1;
	t=0;
	if(ov_sta == 2)
	{
		lcddev.width=240;
		lcddev.height=320; 
		lcddev.dir = 1;
		LCD_Scan_Dir(L2R_D2U);			//���ϵ���,������ 
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		
		temp = 0;
		OV7670_CS=0;	 
 		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
	
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1; 
		x_min=240;
		x_max=0;
		//delay_ms(3);	
		//pixels();
		for(k = 0 ; k < 4 ; k ++)
		{
			
			GPIOB->CRL&=0X00000000;//IO״̬����
			GPIOB->CRL|=0X88888888;//IO״̬����
			GPIOB->ODR|=0X00FF;//IO״̬����
				
			//delay_ms(3);	
			for(i = 0 ; i < 60 ; i ++)
			{
				y_min=320;
				y_max=0;
				for(j = 0 ; j < 320 ; j ++)
				{
					color = 0;
					OV7670_RCK=0;           
					color= OV7670_DATA;   
					OV7670_RCK=1; 		
					color<<=8;
					OV7670_RCK=0;        
					color|= (OV7670_DATA);        
					OV7670_RCK=1;
					color>>=11;
					if((j>120&&j<270)&&((i+k*60)>10&&(i+k*60)<220))
					{
						if(color<17)
						{
							color=0;
							/*
							if(t==0)
							{
								printf("i:%d,j:%d,k:%d\r\n",i,j,k);
								x_min=i+k*60;													
								y_min=j;
							}*/
							if(x_min>=(i+k*60)) x_min=i+k*60;
							
							if(x_max<=(i+k*60)) x_max=i+k*60;	
							
							if(y_min>=j) y_min=j;
									
							if(y_max<=j) y_max=j;
							
							y[i+k*60]=320-mean(y_min,y_max);
											
							t=1;
						}	
						else	
						{
							color=0xffff;//white
						}	
					}
					else
					{
						color=0xf800; // red
					}
					if(j==y_min)
					{
						color=0x03e0;//
					}
					if((i+k*60)==x_min)
					{
						color=0x03e0;
					}
					
					RGB_565[j + i * 320] = color;
				}
			}
		
			
			GPIOB->CRL=0X33333333; //PB0-7  �������
			GPIOB->CRH=0X33333333; //PB8-15 �������
			GPIOB->ODR=0XFFFF;    //ȫ�������
			//delay_ms(3);		
			for(i = 0 ; i < 19200 ; i ++)
			{
				LCD_WR_DATA(RGB_565[i]); 
			}
		}
		
		
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		ov_sta=0;					//��ʼ��һ�βɼ�
	
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 	  
	}
	
	else
	{
	}
	
	//EXTI->PR=1<<15;     		//���LINE8�ϵ��жϱ�־λ
	//delay_ms(5);
	return temp;
}
int main(void)
{	
	double xl,yl;
	int	i;
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	delay_init(72);	     	//��ʱ��ʼ�� 
	uart_init(72,9600);		//���ڳ�ʼ��Ϊ9600
	LCD_Init();			   		//��ʼ��LCD  
	EXTI15_Init();
	steperInit();
	while(OV7670_Init())
 	{
		POINT_COLOR=RED;			//��������Ϊ��ɫ 
		LCD_ShowString(30,130,200,16,16,"ov7670 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}  
//	OV7670_Brightness(3);
	aC=31059;
	bC=44229;
//	for(i=0;i<linecount;i++)
//	{
//		moveTo(x[i],y[i]);
//	}
//	moveTo(0.0,0.0);
	POINT_COLOR=GREEN;
	refresh_TFT_320();
	refresh_TFT_320();
	refresh_TFT_320();
	xprepx=47.5/(x_max-x_min);
	xoffset=60.0-x_max*xprepx;
	yprepx=38.0/(y[x_max]-y[x_min]);
	yoffset=61-y[x_max]*yprepx;
	
	for(i=x_min;i<(x_max+1);i++)
	{
		xl=xprepx*i+xoffset;
		yl=yprepx*y[i]+yoffset;
		printf("moveto:x:%lf,y:%lf\r\n",xl,yl);
		printf("moveto:x:%d,y:%d\r\n",i,y[i]);
		moveTo(xl,yl);
//		LCD_DrawLine(0,y[i],320,y[i]);
//		LCD_DrawLine(i,0,i,240);

	}
	moveTo(0.0,0.0);
	while(1)
	{
//		printf("x_min:%d,y_min:%d,x_max:%d,y_max:%d\r\n",x_min,y[x_min],x_max,y[x_max]);
	}		 
}

























