/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : Encoder.h
* Author             : WYChen
* Version            : V1.0.2
* Date               : 06/25/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#ifndef _Encoder_H
#define _Encoder_H
#include "stm32f10x.h"

#define Encoder_BM 390	//������ÿȦ������
#define Encoder_A  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//��ȡA���ƽ״̬
#define Encoder_B  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡB���ƽ״̬
//#define Encoder_Z  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//��ȡZ���ƽ״̬


extern signed int Encoder_counter;	

	 
void Encoder_GPIO_Init(void);	//GPIO��ʼ��
void Encoder_EXTIX_Init(void);//IO�жϳ�ʼ��	
void Encoder_Init(void);			//����ʽ��������ʼ��
signed int update_angle(void);//����Ƕ�


#endif


/******************************ʹ��ʾ��***************************
#include "stm32f10x.h"
#include "delay.h"
#include "12864.h"
#include "Encoder.h"

int main()
{
	double a=0;
	delay_init();
  LCD12864_init();//12864��ʼ��
	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	Encoder_Init();
	
 while(1)
 {
//	 J12864_led_int(1,1,Encoder_counter);
//	 J12864_led_int(3,1,Encoder_B);
	 a = update_angle();
	 if(a >= 0)
	 {
		 J12864_led_double(1,1,a,1);
		 J12864_led_double(2,1,0,1);
	 }
	 else
	 {
		 J12864_led_double(1,1,0,1);
		 J12864_led_double(2,1,-a,1);
	 }
	 delay_ms(50);
 }
}	
******************************************************************/

