#include "control.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
u8 Flag_Target;

int TIM1_UP_IRQHandler(void)  
{    
	if(TIM1->SR&0X0001)//5ms��ʱ�ж�
	{   
		  TIM1->SR&=~(1<<0);                                       //===�����ʱ��1�жϱ�־λ		 
			Encoder_Left=Read_Encoder(2);                         
	}       	
	 return 0;	  
} 
