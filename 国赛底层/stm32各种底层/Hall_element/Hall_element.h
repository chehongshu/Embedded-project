#ifndef  __HALL_ELEMENT_H
#define __HALL_ELEMENT_H
#include "sys.h"   

///  ��ȡio��ֵ
#define  HALL_ELEMMENT_First     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//��ȡ��һ������Ԫ��
#define  HALL_ELEMMENT_Second  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//��ȡ�ڶ�����Ԫ��


#endif




