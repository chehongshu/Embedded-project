#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "ov7670.h"

//�жϷ�����
u8 ov_sta;
u8 ultra_red = 0;

void EXTI15_10_IRQHandler(void)
{			
	if(EXTI->PR&(1<<15))//��15�ߵ��ж�
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7670_WRST=0;	 	//��λдָ��		  
				OV7670_WRST=1;	
				OV7670_WREN=1;		//����д��FIFO
			}else OV7670_WREN=0;	//��ֹд��FIFO 	 
			
			ov_sta++;
		}
		EXTI->PR=1<<15;     //���LINE15�ϵ��жϱ�־λ	
	}
	
	
	if(EXTI->PR&(1<<13))//��13�ߵ��ж�
	{     
		printf("PC13 is come 1-0\n");
		ultra_red = 1;
		EXTI->PR=1<<13;     //���LINE13�ϵ��жϱ�־λ	
	}
}



//�ⲿ�жϳ�ʼ������
//��ʼ��PA15Ϊ�ж�����.
void EXTI15_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	JTAG_Set(SWD_ENABLE);	//�ر�JTAG  	 
	GPIOA->CRH&=0X0FFFFFFF;	//PA15���ó�����	  
	GPIOA->CRH|=0X80000000; 				   
 	GPIOA->ODR|=1<<15;	   	//PA15����	
	
	GPIOC->CRH&=0XFF0FFFFF;	//PC13���ó�����	  
	GPIOC->CRH|=0X00800000; 				   
 	GPIOC->ODR|=1<<13;	   	//PC13����	
	
	Ex_NVIC_Config(GPIO_A,15,FTIR);//�½��ش���
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);//��ռ2�������ȼ�1����2	

	Ex_NVIC_Config(GPIO_C,13,FTIR);//�½��ش���
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);//��ռ2�������ȼ�1����2		
}














