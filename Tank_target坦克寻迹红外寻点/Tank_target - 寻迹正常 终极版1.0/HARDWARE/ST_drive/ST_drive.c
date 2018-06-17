# include "ST_drive.h"

/*
*********************************************************************************************************
*	�� �� ��:     ST_drive_Init
*	����˵��:     st188��ʼ��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void ST_drive_Init(void)
{
	
			 GPIO_InitTypeDef  GPIO_InitStructure;
			
			 //ʹ��PB PA�˿�ʱ��
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);	 
       
			 //PC6 PC7��ʼ��
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				
     	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOC, &GPIO_InitStructure);						

			 //PA7 PA12��ʼ��
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_12;
			 GPIO_Init(GPIOA, &GPIO_InitStructure);
}


