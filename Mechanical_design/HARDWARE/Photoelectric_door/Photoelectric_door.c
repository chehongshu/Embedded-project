#include "Photoelectric_door.h"

/***************************************
/    �����  �ĸ�
/    a couple of two
/    one  start  // one  finish

//    zuoyou				start:    PE6      finish:  PF7
//    qianhou  		start:		PG10    finish:  PG14  
****************************************/

//start:    PE6      finish:  PF7
void  zuoyou_PDoor_Init()
{
			 GPIO_InitTypeDef  GPIO_InitStructure;//  ����ṹ��
	
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF, ENABLE);	 //  ʹ��ʱ��
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOE, &GPIO_InitStructure);
	

			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    
			 GPIO_Init(GPIOF, &GPIO_InitStructure);	 
	
	
}
//  second  	qian:		PG10    hou:  PG14  
void qianhou_PDoor_Init()
{
		   GPIO_InitTypeDef  GPIO_InitStructure;//  ����ṹ��
	
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //  ʹ��ʱ��
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_14;				
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	// ��������	 
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOG, &GPIO_InitStructure);					

}
//  shangxia:	    PF3  
void shangxia_PDoor_Init()
{
	    GPIO_InitTypeDef  GPIO_InitStructure;//  ����ṹ��
	
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //  ʹ��ʱ��
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	// ��������	 
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOF, &GPIO_InitStructure);					
}

void HD_zuoyou_PDoor_Init()
{
	
	     GPIO_InitTypeDef  GPIO_InitStructure;//  ����ṹ��
	
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //  ʹ��ʱ��
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	// ��������	 
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	     GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}


//  ��ת   ��   �����   
void HD_rotating_PDoor_Init()
{
	     GPIO_InitTypeDef  GPIO_InitStructure;//  ����ṹ��
	
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //  ʹ��ʱ��
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	// ��������	 
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}
