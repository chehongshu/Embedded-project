#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

//��ʱ��3ͨ��1PWM�����ʼ��
void TIM3CH1_PWM_Init(u16 arr,u16 psc);

//��ʱ��1ͨ��4PWM�����ʼ��
void  TIM1CH4_PWM_Init(u16 arr,u16 psc);

#endif
