#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 

 
///  读取io的值
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
#define KEY3   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
#define KEY4   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 

#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3
#define KEY4_PRES 4		//KEY4

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
