#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h" 
#include "sccb.h" 
#include "ov7670.h"
#include "exti.h"
#include "flash.h"
#include "spi.h"
#include "save_rgb.h"
#include "ff.h"  
#include "exfuns.h"

#define mean(x,y) (((x)+(y))>>1)
//ALIENTEK Mini STM32�������ov7670 ����ͷ 
//���ߣ�������

//ģ����Դ��
//ALIENTEK Mini STM32�����巶������1
//�����ʵ��		   


extern u8 ov_sta ,ultra_red;
typedef struct
{
	u32 X;  //ʵ������X
	u32 Y;  //ʵ������Y
	u32 XY; //ʵ��ֵ
	u32 x_min;
	u32 x_max;
	u32 y_min;
	u32 y_max;
	u32 rgb;
	u32 r;
	u32 g;
	u32 b;
	u16 tp_x;
	u16 tp_y;
}R_XY;
R_XY R;
//u16 buffer[50];
u16 RGB_565[19200];
void start_delay()
{
		POINT_COLOR=RED;//��������Ϊ��ɫ 		
		delay_ms(1000);
		printf("3\n");	
		LCD_ShowString(30,40,200,24,24,"3");	
		delay_ms(1000);
		printf("2\n");
		LCD_ShowString(30,40,200,24,24,"2");	
		delay_ms(1000);
		printf("1\n");
		LCD_ShowString(30,40,200,24,24,"1");	
		delay_ms(1000);
		printf("Start!\n");
		LCD_ShowString(30,40,200,24,24,"Start!");	
		delay_ms(1000);
}


u8 refresh_TFT_160()
{
	u16 i = 0 , j = 0;
	u16 color = 0;
	u8 temp = 1;

	if(ov_sta == 2)
	{
		lcddev.width=120;
		lcddev.height=160; 
		lcddev.dir = 0;
		LCD_Scan_Dir(D2U_R2L);			//���ϵ���,������ 
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		
		GPIOB->CRL&=0X00000000;//IO״̬����
		GPIOB->CRL|=0X88888888;//IO״̬����
		GPIOB->ODR|=0X00FF;//IO״̬����
		
		
		temp = 0;
		OV7670_CS=0;	 
 		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
	
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1; 
    		
		//delay_ms(3);	
		//pixels();
		//delay_ms(3);	
		for(i = 0 ; i < 120 ; i ++)
		{
			for(j = 0 ; j < 80 ; j ++)
			{
				//color = 0;   
				OV7670_RCK=0;    	
				//color= OV7670_DATA;   
				OV7670_RCK=1; 	
				//color<<=8;
				OV7670_RCK=0; 
				//color|= (OV7670_DATA);        
				OV7670_RCK=1;
			}
			
			for(j = 0 ; j < 160 ; j ++)
			{
				color = 0;
				OV7670_RCK=0;           
				color= OV7670_DATA;   
				OV7670_RCK=1; 		
				color<<=8;
				OV7670_RCK=0;        
				color|= (OV7670_DATA);        
				OV7670_RCK=1;
				RGB_565[j + i * 160] = color;
			}
			
			for(j = 0 ; j < 80 ; j ++)
			{
				//color = 0;   
				OV7670_RCK=0;    	
				//color= OV7670_DATA;   
				OV7670_RCK=1; 	
				//color<<=8;
				OV7670_RCK=0; 
				//color|= (OV7670_DATA);        
				OV7670_RCK=1;
			}
		}
		
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		ov_sta=0;					//��ʼ��һ�βɼ�
		
		
		GPIOB->CRL=0X33333333; //PB0-7  �������
		GPIOB->CRH=0X33333333; //PB8-15 �������
		GPIOB->ODR=0XFFFF;    //ȫ�������
		
		for(i = 0 ; i < 19200 ; i ++)
		{
			LCD_WR_DATA(RGB_565[i]); 
			//delay_ms(1);
		}
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 	  
	}
	
	
	//EXTI->PR=1<<15;     		//���LINE8�ϵ��жϱ�־λ
	//delay_ms(5);
	
	return temp;
}


u8 refresh_TFT_320()
{
	u16 i = 0 , j = 0 , k = 0;
	u16 color = 0;
	u32 t=0;
	u8 temp = 1;
	
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
    		
		//delay_ms(3);	
		//pixels();
		for(k = 0 ; k < 4 ; k ++)
		{
			
			GPIOB->CRL&=0X00000000;//IO״̬����
			GPIOB->CRL|=0X88888888;//IO״̬����
			GPIOB->ODR|=0X00FF;//IO״̬����
				
			//delay_ms(3);	
			for(i = 0 ; i < 320 ; i ++)
			{
				for(j = 0 ; j < 60 ; j ++)
				{
					color = 0;
					OV7670_RCK=0;           
					color= OV7670_DATA;   
					OV7670_RCK=1; 		
					color<<=8;
					OV7670_RCK=0;        
					color|= (OV7670_DATA);        
					OV7670_RCK=1;
					if((j+k*60)>=2&&(j+k*60)<=237&&i>=41&&i<=274)
					{
						if(color>=54000)	
						{	
							R.r=color;		
							if(t<=3)
							{
									R.x_min=j;
									R.y_min=i;
							}
								
							if(R.x_max<=j) R.x_max=j;
						
							if(R.y_max<=i) R.y_max=i;	
						//����е�
							R.X=mean(R.x_min,R.x_max);
							R.Y=mean(R.y_min,R.y_max);	
							
							t++;
						}	
					}	
					RGB_565[j + i * 60] = color;
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
		
	}
	
	
	
	//EXTI->PR=1<<15;     		//���LINE8�ϵ��жϱ�־λ
	//delay_ms(5);
	return temp;
}



int main(void)
{		 		
	u32 num_i ;
	u8 choice = 0;
	
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	delay_init(72);	     	//��ʱ��ʼ��
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	EXTI15_Init();
	SCCB_Init();
	OV7670_Init();
	/*
	if(lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X5510) //ǿ��������Ļ�ֱ���Ϊ320*240.��֧��3.5����� �ޱ�Ҫ
	{
	
		LCD_Clear(BLUE);
		delay_ms(500);
		lcddev.width=120;
		lcddev.height=160; 
		lcddev.dir = 1;
	}
	*/
		//MYDMA_Config(DMA1_Channel1 , (u32)&GPIOB->IDR , (u32)RGB_565[0] , 160);
		//TIM2_Cap_Init(0XFFFF,2-1);		//��72Mhz��Ƶ�ʼ��� 
	
		LCD_Init();

		//start_delay();
		LCD_Clear(WHITE);
		POINT_COLOR=RED;//��������Ϊ��ɫ 			
		LCD_ShowString(30,240,200,24,24,"LCDTFT   OK");
		delay_ms(500);
		
		for(num_i = 0 ; num_i < 19200 ; num_i ++)
		{
			RGB_565[num_i] = 200;
		}
		
	
  //GPIOB->CRL=0X88888888;//IO״̬����
	//GPIOB->CRH=0X88888888;//IO״̬����
	//GPIOB->ODR&=0XFFFF;//IO״̬����
	LCD_ShowString(30,70,200,24,24,"1/4");
		
		 
  	OV7670_CS=0;	
	while(1)
	{
		if(ultra_red == 1)
		{
			choice = 1;
		}
		switch(choice)
		{
			case 0:
				while(refresh_TFT_320())
				{
					choice = 0;
					printf("x:%d,y:%d\r\n",R.X,R.Y);
				}				
				//LCD_Clear(BLACK);
				break;
			case 1:
				ultra_red = 0;
				save_to_sdcard();
				delay_ms(3000);
				choice = 0;
				break;
			case 2:
					for(num_i = 0 ; num_i < 20 ; num_i ++)
				{
					while(refresh_TFT_160())
				{choice = 0;}
				}				
				break;
			default:
				choice = 1;
		}
		
		
		//delay_ms(20);
	}	 
	
}








/*



	
	for(j = 0 ; j< 50 ; j ++)
				{
					buffer[j] = 0;
				}



for(j = 0 ; j< 50 ; j ++)
				{
					buffer[j] = (GPIOB->IDR);
				}
				for(j = 0 ; j< 50 ; j ++)
				{
					printf("%x%x%x%x%x%x%x%x " , (buffer[j]&0x80) >> 7 ,  (buffer[j]&0x40) >>6,  (buffer[j]&0x20) >>5 ,( buffer[j]&0x10) >>4, (buffer[j]&0x08) >>3,  (buffer[j]&0x04) >>2,  (buffer[j]&0x02 )>>1  , buffer[j]&0x01);
				}






void refresh_TFT()
{
	u16 i = 0 , j = 0;
	u16 color = 0;
	
	lcddev.width=120;
	lcddev.height=160; 
	lcddev.dir = 1;
	LCD_Scan_Dir(L2R_U2D);			//���ϵ���,������ 
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
	
	GPIOB->CRL&=0X00000000;//IO״̬����
	GPIOB->CRL|=0X88888888;//IO״̬����
	GPIOB->ODR|=0X00FF;//IO״̬����
	
	
		OV7670_CS=0;	 
 		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
	
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1; 
    		
		delay_ms(3);	
		//pixels();
		//delay_ms(3);	
		for(i = 0 ; i < 120 ; i ++)
		{
		
		  
			for(j = 0 ; j < 480 ; j ++)
			{
				color = 0;   
				OV7670_RCK=0;    	
				color= OV7670_DATA;   
				OV7670_RCK=1; 	
				color<<=8;
				OV7670_RCK=0; 
				color|= (OV7670_DATA);        
				OV7670_RCK=1;
			}
			for(j = 0 ; j < 160 ; j ++)
			{
				color = 0;
				OV7670_RCK=0;           
				color= OV7670_DATA;   
				OV7670_RCK=1; 		
				color<<=8;
				OV7670_RCK=0;        
				color|= (OV7670_DATA);        
				OV7670_RCK=1;
				RGB_565[j + i * 160] = color;
			}
		}
		
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		ov_sta=0;					//��ʼ��һ�βɼ�
	
	
	GPIOB->CRL=0X33333333; //PB0-7  �������
	GPIOB->CRH=0X33333333; //PB8-15 �������
	GPIOB->ODR=0XFFFF;    //ȫ�������
	
	delay_ms(50);
	for(i = 0 ; i < 19200 ; i ++)
	{
		LCD_WR_DATA(RGB_565[i]); 
	}
	LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 	  
	EXTI->PR=1<<15;     		//���LINE8�ϵ��жϱ�־λ
}

*/














