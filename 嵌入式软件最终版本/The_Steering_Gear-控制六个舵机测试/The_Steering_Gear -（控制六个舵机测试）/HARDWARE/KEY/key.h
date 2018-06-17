#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 
/*********************************
*  four keys
*  
*******************************/
 
///  ��ȡio��ֵ
#define KEY1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ����0
#define KEY2   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����1
#define KEY3   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����2 
#define KEY4   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//��ȡ����2   δ�õ�

#define KEY1_PRES	   1		  //KEY1  
#define KEY2_PRES	   2	  	//KEY2 
#define KEY3_PRES	   3		  //KEY3
#define KEY4_PRES    4		  //KEY4

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
