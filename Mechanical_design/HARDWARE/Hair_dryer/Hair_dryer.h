#ifndef __HAIR_DRYER_H
#define __HAIR_DRYER_H	 
#include "sys.h"
/**
*   ���������
*   anchor �� chehongshu
*   date �� 2017/5/13
**/


		/***************** ��һ������������ת�� ��    �紵������************************/
		/***************** EN->PD10     DIR --> PD12     PWM-->PD14************************/
		
#define HD_zuoyou_ENA_CAN    			GPIO_ResetBits(GPIOD,GPIO_Pin_10)       //ʹ��   
#define HD_zuoyou_ENA_NOT     			GPIO_SetBits(GPIOD,GPIO_Pin_10)     //��ʹ��  

#define HD_zuoyou_DIR_positive     GPIO_SetBits(GPIOD,GPIO_Pin_12);      //   ��������    
#define HD_zuoyou_DIR_reverse     GPIO_ResetBits(GPIOD,GPIO_Pin_12);    //   ���ӷ��� 

#define HD_zuoyou_PWM_H    			 GPIO_SetBits(GPIOD,GPIO_Pin_14);      //      
#define HD_zuoyou_PWM_L    			 GPIO_ResetBits(GPIOD,GPIO_Pin_14);    //   


		/***************** �ڶ�����������ҵ��ƶ��� �紵����ת*************************/
		/***************** EN->PB12  DIR --> PB14   PWM-->PD8 *************************/
		
#define HD_rotating_ENA_CAN    GPIO_ResetBits(GPIOB,GPIO_Pin_12)       //ʹ��   
#define HD_rotating_ENA_NOT     GPIO_SetBits(GPIOB,GPIO_Pin_12)     //��ʹ��  

#define HD_rotating_DIR_positive     GPIO_SetBits(GPIOB,GPIO_Pin_14);      //   ��������    
#define HD_rotating_DIR_reverse     GPIO_ResetBits(GPIOB,GPIO_Pin_14);    //   ���ӷ��� 

#define HD_rotating_PWM_H     GPIO_SetBits(GPIOD,GPIO_Pin_8);      
#define HD_rotating_PWM_L     GPIO_ResetBits(GPIOD,GPIO_Pin_8);    

#define   relay_H      GPIO_SetBits(GPIOC,GPIO_Pin_11);          //  �̵��� ����
#define   relay_L      GPIO_ResetBits(GPIOC,GPIO_Pin_11);        // �̵�������


void   A_hair_dryer_init(void);

void  relay_Init(void);

void   HD_zuoyou_go_R(int delaytime);

void   HD_zuoyou_go_L(int delaytime);

void   HD_rotating_go_L(int delaytime);

void   HD_rotating_go_R(int delaytime);

void   stop_rotating(void);


#endif
