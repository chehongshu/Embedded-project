#include "pwm.h"
#include "led.h"
/////////////        ���PWM
//  PB6    TIM4_CH1   ����

//  PA1    TIM2_CH2    ����
void TIM4_PWM_Init(u16 arr,u16 psc)      //  ����  ���pwm����  ת��
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef           N;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܶ�ʱ�� 4 ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1 CH2 CH3 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������     B6    CH1    ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx        CH_1
    
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
    
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ��TIM3�����жϣ��������� �Ƚ�ֵ��
     N.NVIC_IRQChannel=TIM2_IRQn;
	 N.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�
	 N.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	 N.NVIC_IRQChannelCmd=ENABLE;//ʹ���ж�2����
	 NVIC_Init(&N);//��ʼ���жϷ���
    	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
 
   
}
void TIM2_PWM_Init(u16 arr,u16 psc)      //   �������pwm����  ת��
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef           N;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ�ܶ�ʱ�� 2 ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1 CH2 CH3 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������     B5     CH1    ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx        CH_2
    
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ��TIM3�����жϣ��������� �Ƚ�ֵ��
     N.NVIC_IRQChannel=TIM2_IRQn;
	 N.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�
	 N.NVIC_IRQChannelSubPriority=4;//��Ӧ���ȼ�
	 N.NVIC_IRQChannelCmd=ENABLE;//ʹ���ж�2����
	 NVIC_Init(&N);//��ʼ���жϷ���
    	
	 TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
  
}





extern u32  pulseamount_Left ;
extern u32  pulseamount_Right ;
 // TIM_SetCompare1(TIM4,0); //       ����
 // TIM_SetCompare2(TIM2,0);  //
////*****************************   (  �����  ) �����жϺ��� ************************////

extern int pwm_left;
extern int pwm_right;


void TIM4_IRQHandler(void)   //TIM4�ж�           ����   ��  pwm������Ŀ
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM1  
             if(pwm_left!=0)
                 pulseamount_Left++;              //Ҫ����������ʱ�ſ�ʼ��
            
              
		}
}
void TIM2_IRQHandler(void)   //TIM2�ж�            ����     ��  pwm  ������Ŀ
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
                 if(pwm_right!=0)
	             pulseamount_Right++;          
		}
}