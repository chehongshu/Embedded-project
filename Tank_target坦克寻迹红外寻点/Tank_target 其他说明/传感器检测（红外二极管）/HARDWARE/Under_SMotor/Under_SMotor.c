# include "Under_SMotor.h"
# include "adc.h"
#include "sys.h"




//�������ɳ�ʼ��
void Under_SMotor_PWM_Config()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure); 			
	 GPIO_ResetBits(GPIOA,GPIO_Pin_1);			
}

/*
*********************************************************************************************************
*	�� �� ��:           Under_SMotor_ENA_DIR_Config(void)
*	����˵��:          ��������ʹ�ܺͷ���io�ĳ�ʼ����
*	��    �Σ�               void      
*	�� �� ֵ:                void 
*  io������:  		  PB10 DIR      PB9  EN     
*********************************************************************************************************
*/
void  Under_SMotor_ENA_DIR_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	 GPIO_Init(GPIOB, &GPIO_InitStructure); 				
}
/*
*********************************************************************************************************
*	�� �� ��:           The_laser_Config(void)
*	����˵��:          ����ĳ�ʼ��
*	��    �Σ�               void      
*	�� �� ֵ:                void 
*********************************************************************************************************
*/
void  The_laser_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 
}
/*
*********************************************************************************************************
*	�� �� ��:           Under_SMotor_init(void)
*	����˵��:          ������������ĳ�ʼ����
*	��    �Σ�               void      
*	�� �� ֵ:                void 
*********************************************************************************************************
*/
void  Under_SMotor_init(void)
 {
	 
    Under_SMotor_PWM_Config();   
	  Under_SMotor_ENA_DIR_Config();    
	  The_laser_Config();   
 }
 
 /*
*********************************************************************************************************
*	�� �� ��:              		
*	����˵��:         			��ƽ��ת
*	��    �Σ�              
*	�� �� ֵ:                  
*********************************************************************************************************
*/

void TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	TIM_Cmd(TIM4, ENABLE); 
}



					
//  IO ��ת��
void TIM4_IRQHandler(void)
{
	static u8 i = 0;
	if ( RESET!=TIM_GetITStatus(TIM4, TIM_IT_Update) )
	 {
			
					if ( 0==i )
					{
						Voltage = 1;
						i = 1;
					}
					else 
					{
						Voltage = 0;
						i = 0;
					}
					
	  }
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}


