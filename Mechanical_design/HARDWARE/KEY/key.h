#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)     //��ȡ����  �͵�ƽ�򱻰���



void KEY_Init(void);//IO��ʼ��

#endif
