/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : Encoder.c
* Author             : WYChen
* Version            : V1.0.2
* Date               : 06/25/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#include "Encoder.h"

//A�� --> PB6
//B�� --> PB7(PB3�����ã�ԭ����)
//Z�� --> PA0


signed int Encoder_counter=0;


/**********************************************************
*������EXTI4_IRQHandler(void)
*���ܣ�A���жϷ������
*��������
*���أ���
*��ע����
**********************************************************/
void EXTI9_5_IRQHandler(void)			
{
	if(Encoder_B==1)	
	{
		Encoder_counter--;
	}
	else
	{
		Encoder_counter++;
	}
	EXTI_ClearITPendingBit(EXTI_Line7);  //���EXTI4��·����λ 
}

/**********************************************************
*������EXTI0_IRQHandler(void)
*���ܣ�Z���жϷ������У׼���
*��������
*���أ���
*��ע����
**********************************************************/
void EXTI0_IRQHandler(void)			
{
	Encoder_counter = 0;									//���У׼
	EXTI_ClearITPendingBit(EXTI_Line0);  	//���EXTI4��·����λ 
}


/**********************************************************
*������Encoder_GPIO_Init(void)
*���ܣ�����ʽ������GPIO��ʼ��
*��������
*���أ���
*��ע����
**********************************************************/
void Encoder_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTBʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��JTAG���õ�PB3/PB4
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;//PAO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;//PA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3
//  
//	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;//PB4
//	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //���ó���������
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.4
}


/**********************************************************
*������Encoder_EXTIX_Init(void)
*���ܣ�IO�жϳ�ʼ��
*��������
*���أ���
*��ע������A���жϣ����жϺ����м��B���ƽ״̬
**********************************************************/
void Encoder_EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
//	Encoder_GPIO_Init();//��ʼ��GPIO
	
	//GPIOB.4 A.0�ж����Լ��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);//A���ж�
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//Z���ж�

	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


/**********************************************************
*������Encoder_Init(void)
*���ܣ�����ʽ��������ʼ��
*��������
*���أ���
*��ע����
**********************************************************/
void Encoder_Init(void)
{
	Encoder_GPIO_Init();
	Encoder_EXTIX_Init();
}


/**********************************************************
*������update_angle(void)
*���ܣ�������������ݵõ��Ƕ�ֵ
*��������
*���أ��Ƕ�ֵ
*��ע��Encoder_BM=360�ֱ���1��
**********************************************************/
signed int update_angle(void)
{
	double angle=0;
	
	//����Ƕ�
	while(Encoder_counter >=  (Encoder_BM/2))		{Encoder_counter -= Encoder_BM;}
	while(Encoder_counter <= -(Encoder_BM/2))		{Encoder_counter += Encoder_BM;}
	
	angle = Encoder_counter*360/Encoder_BM;
	
	return angle;
}

