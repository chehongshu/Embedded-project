#include "led.h"

//   ������   
//  PC8 ���  
//  PC9 �Ƶ�
// PC10  �̵�
//
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
    
    
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PC.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.8
 GPIO_ResetBits(GPIOC,GPIO_Pin_8);						 //PC.8 �����

    
    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 //LED1-->PC.9 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOC,GPIO_Pin_9);                               //PC.9 ����� 
    

    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //LED2-->PC.10 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOC,GPIO_Pin_10); 						 //PC.10 ����� 
}
 
