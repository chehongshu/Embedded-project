#include "hc_sr04.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include <math.h>

/**************
*Echo   PB11
*Trigle  PB12
***************/

/*****************
* ʹ�÷�ʽ
* ��  ����	   trig(���ƶ�)  		echo(���ն�)  ��IO  
*  ��ʼ��+ ֱ�Ӷ�ȡ���ݡ�
*****************/
int overflow;   //���ڼ���Ƿ�ʱ���Ѿ����
void RCC_Configuration(void)
{
			/*system clock enable*/
			SystemInit();  //  ϵͳʱ�� ��ʼ��
}
void delay(void)   //   ��ʱ
{ 
			u32 i;
			i=100000;
			while(i--);
}
 // ���ȼ� ����
void NVIC_Configuration(void)   
{
			/*CAN receive interrupt enable*/
			NVIC_InitTypeDef NVIC_InitStructure;
			
			NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
}
// IO  ����  VCC��Դ			trig(���ƶ�)  		echo(���ն�)     GND
void GPIO_Configuration(void)
{
	
			GPIO_InitTypeDef GPIO_InitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			
			/*Echo pin define*/
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //  ��������
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			/*Trigle pin define*/
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  							// �������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
  
 
}
// ʱ������
void TIM_Configuration(void)
{
				TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
				
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

				TIM_DeInit(TIM2);            //   ��λ  TIM2

				TIM_TimeBaseStructure.TIM_Period=5000;
				TIM_TimeBaseStructure.TIM_Prescaler=0;
				TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
				TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
				TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
					
				////  ʹ�� ����
				TIM_PrescalerConfig(TIM2,359,TIM_PSCReloadMode_Immediate);//ʱ��Ƶ��Ϊ72MHz/(359+1)=200000
				TIM_ARRPreloadConfig(TIM2, DISABLE);
				TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //  ����arr��ֵ֮�� ����  �ж�

				TIM_Cmd(TIM2, DISABLE);
}

///  TIM2��  �жϺ���
void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
  {
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    overflow++;
  }
}
/*******************
**  HC SR04��05һ����
** ��ʼ��
********************/
void HC_SR_Init()
{
				/*system clock init*/
			RCC_Configuration();
			
			/*interrupt init*/
			NVIC_Configuration();
			
			/*I\O init*/
			GPIO_Configuration();
			
			/*TIM��ʼ��*/
			TIM_Configuration();
}
/*����ֵΪ���׼�*/
/**
// ���Ծ��� = ���ߵ�ƽʱ��*���٣�340���� /    2
***/
float Sensor_using(void)
{
				float distance=0;
				u16 TIM=0;
			
					//  Trig ��������20us �ߵ�ƽ  ��Ϊ����
				GPIO_SetBits(GPIOB,GPIO_Pin_12);
				delay_ms(20);
				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			
					TIM_Cmd(TIM2, ENABLE); 					//  ����ʱ��
					while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) && overflow==0);  //  �ȴ� B11 ����
					TIM2->CNT=0;// ��� ����  ��0��ʼ����
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) && overflow==0);  // �ȴ�B11����  �����м��¼ΪB11����ʱ��
					TIM_Cmd(TIM2, DISABLE); //  ���� ���
					
					if(overflow!=0)   //���  �е�û������  ��ɶ�ģ�
					{
					overflow=0;
					return 0.0;
					}
					TIM=TIM_GetCounter(TIM2);
					distance=(float)sqrt((TIM/20.0*17)*(TIM/20.0*17)-module_interval*module_interval/4.0)+12.0; //12.0Ϊ����
			
			return(distance);
	
}

