#include "steppermotor.h"
#include "sys.h"

/*
*********************************************************************************************************
*	�� �� ��:     steppermotor_init()     �������
*	����˵��:     ���������ʼ��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void steppermotor_init(void)         //  �������    ǰ���� ��  ����  ����io
{
        GPIO_InitTypeDef  GPIO_InitStructure;
				//ʹ��GPIOʱ��Դ
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA
								|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PA  PC  PG  PD  ʱ��
	

					 //��ʼ��IO
					/***************** ��һ������������ת����57���*************************/
					/***************** EN->PG8 DIR --> PC7   PWM-->PC9*************************/
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				 GPIO_Init(GPIOC, &GPIO_InitStructure);
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
				 GPIO_Init(GPIOG, &GPIO_InitStructure);
					/***************** �ڶ�����������ҵ��ƶ��� ϴͷ��42*************************/
					/***************** EN->PG2  DIR --> PG4   PWM-->PG6 *************************/
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				 GPIO_Init(GPIOG, &GPIO_InitStructure);

					/***************** ��������������µ��ƶ��� ˿�˻�̨*************************/
					/***************** EN->PD4  DIR --> PD2   PWM-->PD0 *************************/
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_2|GPIO_Pin_0;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				 GPIO_Init(GPIOD, &GPIO_InitStructure);
				 
				 
				 qianhou_ENA_NOT;
				  zuoyou_ENA_NOT;
					shangxia_ENA_NOT;
}

/*
*********************************************************************************************************
*	�� �� ��:     stop_motor
*	����˵��:   ֹͣ  ���ת��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void stop_motor(void)
{    
    GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_14);
}



    
