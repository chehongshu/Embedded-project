#include "Dc_motor.h"
#include "sys.h" 
#include "delay.h"

/***********************************
*L298N    ֱ�����
*  EN   PWM    speed 
*		L_EN  PB1     E_EN   PB2
*   IN1  PA1      IN2    PA2         ����
*   IN3  PA3      IN4      PA4       ����
************************************/

//�����ʼ������
void Dc_motor_Init(void) //IO��ʼ��
{ 
		GPIO_InitTypeDef 			GPIO_InitStructure;
		//��ʼ��IN1-->GPIOA.0,IN2-->GPIOA.11 �������
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ�� ( ��Ҫ����)

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOB0  B1
	
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB0,B1

		       L_IN_1 = 0;
	         L_IN_2 = 0;
	
					 R_IN_1 = 0;
	         R_IN_2 = 1;
	
}


/******************Left    motor******************/
void L_motor_forward(void)	   //   ˳ʱ��
{	 
           L_IN_1 = 0;
	         L_IN_2 = 1;
	
}
void L_motor_backward(void)	   //   ��ʱ��
{	 
           L_IN_1 = 1;
	         L_IN_2 = 0;
}


/******************Right   motor******************/
void R_motor_forward(void)	   //   ˳ʱ��
{	 
           R_IN_1 = 0;
	         R_IN_2 = 1;
}
void R_motor_backward(void)	   //   ��ʱ��
{	 
           R_IN_1 = 1;
	         R_IN_2 = 0;
}


