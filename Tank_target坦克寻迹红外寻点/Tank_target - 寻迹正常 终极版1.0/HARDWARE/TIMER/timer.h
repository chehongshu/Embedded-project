# ifndef __TIMER_H
# define __TIMER_H
# include "sys.h"

# define SPEED_VALUE 1000  //�����ٶ�ֵ

//��ʱ��5�жϳ�ʼ��
void TIM5_Int_Init(u16 arr,u16 psc); 

//��ʱ��6�жϳ�ʼ��
void TIM6_Int_Init(u16 arr,u16 psc);

//��ʱ��7�жϳ�ʼ��
void TIM7_Int_Init(u16 arr,u16 psc);
 
#endif
