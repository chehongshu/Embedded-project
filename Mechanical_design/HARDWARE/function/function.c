#include "function.h"
#include "steppermotor.h"
#include "delay.h"
#include "Photoelectric_door.h"
 #include "led.h"


/***********************************************************************************************************
*������
*���ܣ�  ���ҽṹ����ת
*��������
*���أ���
*************************************************************************************************************/
int count = 0;
void zuoyou_go_R(int delaytime)
{
						count ++;
						zuoyou_ENA_CAN;
						zuoyou_DIR_reverse;//  ��ת
						
						zuoyou_PWM_H;
						delay_us(delaytime);
						zuoyou_PWM_L;
					
						delay_us(delaytime);
}
/*
**���ҽṹ����ת
*/
void zuoyou_go_L(int delaytime)
{
	
						zuoyou_ENA_CAN;
						zuoyou_DIR_positive;
						
						zuoyou_PWM_H;
						delay_us(delaytime);
						zuoyou_PWM_L;
					
						delay_us(delaytime);
}


/***********************************************************************************************************
*������
*���ܣ�  ǰ��ṹ��ǰ
*��������
*���أ���
*************************************************************************************************************/
void qianhou_go_Q(int delaytime)
{
						qianhou_ENA_CAN;
						qianhou_DIR_positive;//  ǰת
						
						qianhou_PWM_H;
						delay_us(delaytime);
						qianhou_PWM_L;
					
						delay_us(delaytime);
}
/***********************************************************************************************************
*������
*���ܣ�  ǰ��ṹ���
*��������
*���أ���
*************************************************************************************************************/

void qianhou_go_H(int delaytime)
{
						qianhou_ENA_CAN;
						qianhou_DIR_reverse;//  ��ת
						
						qianhou_PWM_H;
						delay_us(delaytime);
						qianhou_PWM_L;
					
						delay_us(delaytime);
}


/***********************************************************************************************************
*������
*���ܣ�  ���½ṹ����
*��������
*���أ���
*************************************************************************************************************/

void shangxia_go_S(int delaytime)
{
	          int go_i;
						shangxia_ENA_CAN;
						shangxia_DIR_reverse;
	
						shangxia_PWM_H;
          	delay_us(delaytime);
						//for(go_i=0;go_i<1000;go_i++)  __NOP;
						shangxia_PWM_L;
					  delay_us(delaytime);
						//for(go_i=0;go_i<1000;go_i++)  __NOP;
}

/***********************************************************************************************************
*������
*���ܣ�  ���½ṹ����
*��������
*���أ���
*************************************************************************************************************/

void shangxia_go_X(int delaytime)
{
						int go_i;
						shangxia_ENA_CAN;
					  shangxia_DIR_positive;
						
						shangxia_PWM_H;
						//delay_us(delaytime);
	          for(go_i=0;go_i<1000;go_i++)  __NOP;
						      shangxia_PWM_L;
					
					  for(go_i=0;go_i<1000;go_i++)  __NOP;
}
