#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
extern int angle; 
extern int speed;
extern int t_angle;
extern int distance;
extern int page;
extern int arrow;
int flag=0;
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ��������Ӧioģʽ

    //GPIOC.5 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.15	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.0	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
}


//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����

	if(WK_UP==1)	 	 //WK_UP����
	{				 
				if(page==1)
		{
			LCD_Clear(WHITE);
			
			if(arrow<=1)
			{
			
			arrow=3;
			LCD_Clear(WHITE);
			}
			else
			arrow--;
			LCD_Clear(WHITE);
		}
		if(page==2)
		{
			speed++;
			if(speed>10)
			{speed=0;}
		}
		if(page==3)
		{
				t_angle++;	
			if(t_angle>60)
			{t_angle=0;}
	
		}		
				if(page==4)
		{
			distance++;	
			if(distance >15)
			{distance=7;}
		}		
	}
	LCD_Clear(WHITE);
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 
//�ⲿ�ж�2�������
//void EXTI2_IRQHandler(void)
//{
//	delay_ms(10);//����
//	LCD_Clear(WHITE);
//	if(KEY2==0)	  //����KEY2 ����
//	{
//		if(page==2||page==3||page==4)
//		{
//			page=1;
//		}
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
//}
//�ⲿ�ж�3�������
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//����

	if(KEY1==0)	 //����KEY1
	{				 
		if(page==1)
		{
			LCD_Clear(WHITE);
			
			if(arrow>=3)
				
			{
			LCD_Clear(WHITE);
			arrow=1;}
			
			else arrow++;
		}
		if(page==2)
		{
			speed--;
			if(speed<0)
			{speed=10;}
		}
		if(page==3)
		{
			t_angle--;	
			if(t_angle<0)
			{t_angle=60;}
		}		
				if(page==4)
		{
			distance--;	
			if(distance <7)
			{distance=15;}
		}		
		
	}		 
		LCD_Clear(WHITE);
 EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE15��·����λ
}

 void  EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//����
	LCD_Clear(WHITE);
	if(KEY0==0)	 //����KEY0
	{
		
		if (page==2||page==3||page==4)
		{  flag=1;
		   
		}
			

		if(page==1)
		{
			if(arrow==1)
			{page=2;}
			
			if(arrow==2)
			{page=3;}
			
			if(arrow==3)
			{page=4;}			

	}		
if (flag==1)
			page=1;
			flag=0;
	
		}		
	LCD_Clear(WHITE);
  EXTI_ClearITPendingBit(EXTI_Line5);    //���LINE5�ϵ��жϱ�־λ  
}
 
