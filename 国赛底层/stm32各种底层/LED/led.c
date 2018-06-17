#include "led.h"

/*
*********************************************************************************************************
*	�� �� ��:     LED_Init
*	����˵��:     LED��ʼ��
*	��    �Σ�    void 
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void LED_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 //ʹ��PB�˿�ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
 
 //IO�ڳ�ʼ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;			
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
 GPIO_ResetBits(GPIOC,GPIO_Pin_8);					
 GPIO_ResetBits(GPIOC,GPIO_Pin_9 | GPIO_Pin_10);					
}

/*
*********************************************************************************************************
*	�� �� ��:     buzzer_Init
*	����˵��:     ��������ʼ��
*	��    �Σ�    void 
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void buzzer_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 //ʹ��PB�˿�ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 

 //IO�ڳ�ʼ��	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
 GPIO_ResetBits(GPIOC,GPIO_Pin_12);					
}

/*
*********************************************************************************************************
*	�� �� ��:     Waring_Start
*	����˵��:     ���濪ʼ(���� ��������)
*	��    �Σ�    void 
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void Warning_Start(void)
{
	LED0 = 1;                                     //ָʾ����
	LED1 = 1;
	LED2 = 1;
	GPIO_SetBits(GPIOC, GPIO_Pin_12);              //��������
}

/*
*********************************************************************************************************
*	�� �� ��:     Waring_Stop
*	����˵��:     ����ֹͣ(���� ��������)
*	��    �Σ�    void 
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void Warning_Stop(void)
{
	LED0 = 0;                                          //ָʾ����
	LED1 = 0;
	LED2 = 0;
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);           //������ֹ
}
 
