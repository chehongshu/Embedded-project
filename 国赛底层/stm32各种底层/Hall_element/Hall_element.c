#include "Hall_element.h"

/*
/����ԭ��   
/�÷��� ��ȡio�ĵ�ƽ   ��ƽ����  �Ӵ�    ��ƽ��Ϊδ�Ӵ�
*/  
void Hall_element_Init()
{
		 GPIO_InitTypeDef  GPIO_InitStructure;
			
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
			
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;				 //LED1-->PB.3 �˿����� LED2-->PB.5 �˿�����
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.3
		 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //PB.3 �����
		 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����
}

