#include "pwm.h"
#include "stm32f10x.h"



//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
				GPIO_InitTypeDef GPIO_InitStructure;
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				TIM_OCInitTypeDef  TIM_OCInitStructure;
				//Step2, ʹ������ʱ�� TIM2 TIM3 GPIOA
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
				//Step3, ��ʼ��Ҫ�õ���GPIO
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
	
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				//Step4, ����Ϊȱʡֵ
				TIM_DeInit(TIM3); //����Ϊȱʡֵ
				//Step5, TIM1ʱ������
			
				TIM_TimeBaseStructure.TIM_Prescaler = psc; //Ԥ��Ƶ(ʱ�ӷ�Ƶ)
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
				TIM_TimeBaseStructure.TIM_Period = arr;//װ��ֵ 
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
				TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;  //���ڼ�����ֵ ���ù�
				TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
				//Step6, Configuration in PWM mode
				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //PWMģʽһ
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //����ͨ����Ч  
				TIM_OCInitStructure.TIM_Pulse = 0; //TIM_Pulse/TIM_Period=duty_cycle
				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //�������
				TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //����״̬��Ϊ�ǹ���״̬

				TIM_OC3Init(TIM3,&TIM_OCInitStructure);
			  TIM_OC4Init(TIM3,&TIM_OCInitStructure);
				//Step7,  TIM3 counter enable��������
				TIM_Cmd(TIM3,ENABLE);
		

				TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
				TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
				
			 
				TIM_ARRPreloadConfig(TIM3, ENABLE);	//??ARR?????? 
				//Step8,  TIM2 TIM3 Main Output Enable ʹ��TIM3�����������  �����
				TIM_CtrlPWMOutputs(TIM3,ENABLE);
   
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{  
				GPIO_InitTypeDef GPIO_InitStructure;
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				TIM_OCInitTypeDef  TIM_OCInitStructure;
				//Step2, ʹ������ʱ�� TIM4  PB
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
				//Step3, ��ʼ��Ҫ�õ���GPIO
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);

				//Step4, ����Ϊȱʡֵ
				TIM_DeInit(TIM4); //����Ϊȱʡֵ
				//Step5, TIM1ʱ������
			
				TIM_TimeBaseStructure.TIM_Prescaler = psc; //Ԥ��Ƶ(ʱ�ӷ�Ƶ)
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
				TIM_TimeBaseStructure.TIM_Period = arr;//װ��ֵ 
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
				TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;  //���ڼ�����ֵ ���ù�
				TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
				//Step6, Configuration in PWM mode
				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //PWMģʽһ
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //����ͨ����Ч  
				TIM_OCInitStructure.TIM_Pulse = 0; //TIM_Pulse/TIM_Period=duty_cycle
				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //�������
				TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //����״̬��Ϊ�ǹ���״̬

				TIM_OC1Init(TIM4,&TIM_OCInitStructure);
			  TIM_OC2Init(TIM4,&TIM_OCInitStructure);
				
				TIM_OC3Init(TIM4,&TIM_OCInitStructure);
			  TIM_OC4Init(TIM4,&TIM_OCInitStructure);
				
				//Step7,  TIM4 counter enable��������
				TIM_Cmd(TIM4,ENABLE);
		
	      TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  
				TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  
				TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
				TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
				
				TIM_ARRPreloadConfig(TIM4, ENABLE);	//??ARR?????? 
				//Step8,  TIM4 Main Output Enable ʹ��TIM3�����������  �����
				TIM_CtrlPWMOutputs(TIM4,  ENABLE);
   
}

