/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : encoder.h
* Author             : WYChen
* Version            : V1.0.0
* Date               : 06/24/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

#define Encoder_BM 390	//������ÿȦ������

void TIM4_Init(void);
void TIM4_Mode_Config(void);
signed int  update_angle(void);


#endif

/*****************************ʹ��ʾ��*************************************
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"	
#include "12864.h"
#include "Encoder.h"
#include "timer.h"

volatile s16 encoder_num;

int main()
{
	double a=0;
	
	uart_init(9600);	 									//���ڳ�ʼ��Ϊ9600
	delay_init();
  LCD12864_init();//12864��ʼ��
	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	TIM3_Init();
	Timerx_Init(1000,72);//��ʱ��2��ʼ��,10Khz�ļ���Ƶ��,������1ms 

	while(1)
	{
		encoder_num = update_angle();
		if(encoder_num >= 0)
		{
			J12864_led_double(1,1,encoder_num,0);
			J12864_led_double(2,1,0,0);
		}
		else
		{
			J12864_led_double(1,1,0,0);
			J12864_led_double(2,1,-encoder_num,0);
		}
		delay_ms(50);
 }
}
**************************************************************************/



