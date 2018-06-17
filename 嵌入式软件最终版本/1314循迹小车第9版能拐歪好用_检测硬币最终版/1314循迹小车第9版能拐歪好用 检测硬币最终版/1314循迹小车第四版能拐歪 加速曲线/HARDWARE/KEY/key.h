#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define S13  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) //��ȡ����1��WAKEUP��
#define S14  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����2��TAMPER��
#define S15  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����3��USER1��


 


#define KEY13_PRES 	1	//KEY1����
#define KEY14_PRES	2	//KEY2����
#define KEY15_PRES	3	//KEY3����



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��	


void buzzer_Init() ;
#endif
