#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Encoder.h"

signed int angle = 0;
int k = 0;
int main(void)
{
	 
				delay_init();	    	 //��ʱ������ʼ��	  
				NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
				TIM4_Init();
				 while(1){
					 angle  =  update_angle();
					 delay_ms(50);
					 k++;
				}
				 
}
