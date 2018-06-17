#ifndef __PHOTOELECTRIC_DOOR_H
#define __PHOTOELECTRIC_DOOR_H	 
#include "sys.h"
/***************************************
/  �����  �ĸ�
/    a couple of two
/   one  start  // one  finish

//  zuoyou				start:    PF7      finish:  PE6
//  qianhou  		start:		PG10    finish:  PG14  
//   ��ȡ��ѹֵΪ1ʱ�ж�������
****************************************/

//  ���ҵ�
#define zuoyou_PDoor_L        					  	  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)  
#define zuoyou_PDoor_R        				    	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
//  ǰ���
#define qianhou_PDoor_Q           			   GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10)
#define qianhou_PDoor_H          			   	 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_14)


//  ���µ�
#define shangxia_PDoor            			    GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)


//    ������� ���ҵĹ����
#define  HD_zuoyou_PDoor_L              GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)	
#define  HD_zuoyou_PDoor_R             GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)


#define  HD_rotating_PDoor         		    	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)

void  zuoyou_PDoor_Init(void);

void qianhou_PDoor_Init(void);

void shangxia_PDoor_Init(void);

void HD_zuoyou_PDoor_Init(void);

void HD_rotating_PDoor_Init(void);		    

#endif



