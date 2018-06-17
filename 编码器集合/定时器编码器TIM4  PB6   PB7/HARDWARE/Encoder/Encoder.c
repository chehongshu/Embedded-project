/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : encoder.c
* Author             : WYChen
* Version            : V1.0.0
* Date               : 06/24/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#include "Encoder.h"

//A�� --> PB6 
//B�� --> PB7
//Z�� --> δ��



/**********************************************************
*������TIM4_Mode_Config(void)
*���ܣ�����ʱ��4������ģʽ����
*��������
*���أ���
*��ע����
**********************************************************/
void TIM4_Mode_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PB.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	

	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��TIM3
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =Encoder_BM*4-1;
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ:
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��:����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM4��ʱ�� */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*--------------��������---------------------����ģʽ------------------*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
	
 // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM4->CNT =0;
	
	
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��4
}


/**********************************************************
*������TIM4_Init(void)
*���ܣ���ʼ����ʱ��4
*��������
*���أ���
*��ע����
**********************************************************/
void TIM4_Init(void)
{
  TIM4_Mode_Config();
}


/**********************************************************
*������update_angle(void)
*���ܣ�������������ݵõ��Ƕ�ֵ
*��������
*���أ��Ƕ�ֵ
*��ע��Encoder_BM=360; �ֱ���0.25��,��������
**********************************************************/
signed int  update_angle(void)
{
	signed int angle=0;
	
	angle = TIM_GetCounter(TIM4);
	
	//����Ƕ�
	while(angle >=  Encoder_BM*2)		{angle -= Encoder_BM*4;}
	while(angle <= -Encoder_BM*2)		{angle += Encoder_BM*4;}
	
	angle = angle*360/(Encoder_BM*4);
	
	return angle;
}
