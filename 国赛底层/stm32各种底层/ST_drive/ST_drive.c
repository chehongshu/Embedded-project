#include "ST_drive.h"
//st188
/*************************
		  ����ԭ��
			��· ������   
			�Ӵ���ɫ��Ϊ   
			���Ӵ���ɫ��   
	************************/
void ST_drive_Init()
{
	
			GPIO_InitTypeDef  GPIO_InitStructure;
				
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;				 //
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //  ��������
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
			 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.3
			 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //PB.3 �����
			 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����
	
}