#include "Hair_dryer.h"
#include "delay.h"

void A_hair_dryer_init(void)
{
				GPIO_InitTypeDef  GPIO_InitStructure;
				//ʹ��GPIOʱ��Դ
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ�� PC   PD  ʱ��
			   //��ʼ��IO
				/***************** ��һ������������ת�� ��    �紵������************************/
				/***************** EN->PD10 DIR --> PD12  PWM-->PD14************************/
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_14;				
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOD, &GPIO_InitStructure);
				/***************** �ڶ�����������ҵ��ƶ��� �紵����ת*************************/
				/***************** EN->PB12  DIR --> PB14   PWM-->PD8 *************************/
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;			
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOB, &GPIO_InitStructure);
	
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		
	     GPIO_Init(GPIOD, &GPIO_InitStructure);
			 
			 HD_zuoyou_ENA_NOT;
			 HD_rotating_ENA_NOT;
			

}

//PC11     �̵���
void  relay_Init()
{
	      GPIO_InitTypeDef  GPIO_InitStructure;//  ����ṹ��
	
				 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //  ʹ��ʱ��
					
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	// ��������	 
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
				 GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	       relay_L;
	
}

/***********************************************************************************************************
*������
*���ܣ�  ���ҽṹ����ת
*��������
*���أ���
*************************************************************************************************************/

void HD_zuoyou_go_R(int delaytime)
{
	
						HD_zuoyou_ENA_CAN;
	          HD_zuoyou_DIR_positive;
					
						
						HD_zuoyou_PWM_H;
						delay_us(delaytime);
						
	          HD_zuoyou_PWM_L;
					
						delay_us(delaytime);
}
/*
**���ҽṹ����ת
*/
void HD_zuoyou_go_L(int delaytime)
{
	
						HD_zuoyou_ENA_CAN;
						HD_zuoyou_DIR_reverse;
						
						HD_zuoyou_PWM_H;
						delay_us(delaytime);
						
						HD_zuoyou_PWM_L;
						delay_us(delaytime);
}


/***********************************************************************************************************
*������
*���ܣ�  ����� ��ת����
*��������
*���أ���
*************************************************************************************************************/
void   HD_rotating_go_L(int delaytime)
{
						HD_rotating_ENA_CAN;
						HD_rotating_DIR_positive;//  ǰת
						
						HD_rotating_PWM_H;
						delay_us(delaytime);
						HD_rotating_PWM_L;
					
						delay_us(delaytime);
}
/***********************************************************************************************************
*������
*���ܣ�   ����� ��ת����
*��������
*���أ���
*************************************************************************************************************/
void HD_rotating_go_R(int delaytime)
{
						HD_rotating_ENA_CAN;
						HD_rotating_DIR_reverse;//  ��ת
						
						HD_rotating_PWM_H;
						delay_us(delaytime);
						HD_rotating_PWM_L;
					
						delay_us(delaytime);
}
/***********************************************************************************************************
*������
*���ܣ�   �����  ���ܹ� ��ת
*��������
*���أ���
*************************************************************************************************************/

void stop_rotating()
{
						HD_rotating_ENA_NOT;
						HD_zuoyou_ENA_NOT;
}
