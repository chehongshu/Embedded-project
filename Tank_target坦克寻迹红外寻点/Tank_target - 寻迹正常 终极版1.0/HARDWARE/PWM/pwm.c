# include "pwm.h"

/*
*********************************************************************************************************
*	�� �� ��:     TIM3CH1_PWM_Init
*	����˵��:     ��ʱ��3ͨ��1PWM�����ʼ�� ��PA6 ���֣�
*	��    �Σ�    arr װ��ֵ  psc Ԥ��Ƶ
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM3CH1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//ʹ��GPIO����ʱ��ʹ�� ʹ�ܶ�ʱ��1ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//��ʼ����ʱ��ģ��
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

  //��ʼ��PWM���ģ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 100; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 

	//MOE �����ʹ��	
  TIM_CtrlPWMOutputs(TIM3,ENABLE);	

	//CH1Ԥװ��ʹ��	 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	
	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	 
	//��ʹ��TIM3  �����ֲ�ת��
	TIM_Cmd(TIM3, DISABLE);  
}

/*   
*********************************************************************************************************
*	�� �� ��:     TIM1CH4_PWM_Init
*	����˵��:     ��ʱ��1ͨ��4PWM�����ʼ�� ( PA11 ����)
*	��    �Σ�    arr װ��ֵ  psc Ԥ��Ƶ
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM1CH4_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//ʹ��GPIO����ʱ��ʹ�� ʹ�ܶ�ʱ��1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//��ʼ����ʱ��ģ��
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

  //��ʼ��PWM���ģ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 100; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 

	//MOE �����ʹ��	
  TIM_CtrlPWMOutputs(TIM1,ENABLE);	

	//CH4Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	
	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1, ENABLE); 
	
	//��ʹ��TIM1  �����ֲ�ת��
	TIM_Cmd(TIM1, DISABLE);  
}



