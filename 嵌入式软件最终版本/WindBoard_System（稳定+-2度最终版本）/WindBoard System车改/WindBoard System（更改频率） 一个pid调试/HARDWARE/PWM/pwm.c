# include "pwm.h"

//��ʱ��pwm�����ʼ��
void TIM3_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//ʹ��GPIOAʱ��Դ����ʱ��1ʱ��Դ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//��ʼ��IO��Ϊ����ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//��ʼ����ʱ��
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//������ʱ��
	TIM_Cmd(TIM3, ENABLE);
	
	//��ʼ��PWM���ģ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//ʹ��Ԥװ��
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	//ʹ��ARR
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	//ʹ�������
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	
	//���ñȽ�ֵ
	TIM_SetCompare1(TIM3,0);	 
}

void TIM4_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//ʹ��GPIOAʱ��Դ����ʱ��1ʱ��Դ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//��ʼ��IO��Ϊ����ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//��ʼ����ʱ��
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	//������ʱ��
	TIM_Cmd(TIM4, ENABLE);
	
	//��ʼ��PWM���ģ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	
	//ʹ��Ԥװ��
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	//ʹ��ARR
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	//ʹ�������
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	
	//���ñȽ�ֵ
	TIM_SetCompare1(TIM4,0);	 
}




