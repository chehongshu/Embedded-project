#ifndef _JINBUDIANJI_H_
#define _JINBUDIANJI_H_

#define ENA_Left_H     GPIO_SetBits(GPIOA,GPIO_Pin_4)       //ʹ��    �� 
#define ENA_Left_L     GPIO_ResetBits(GPIOA,GPIO_Pin_4)     //��ʹ��  ��

#define ENA_Right_H    GPIO_SetBits(GPIOA,GPIO_Pin_6)       //ʹ��    ��
#define ENA_Right_L    GPIO_ResetBits(GPIOA,GPIO_Pin_6)     //��ʹ��  ��

#define DIR_Left_H     GPIO_SetBits(GPIOA,GPIO_Pin_5);      //   ��������  ��  
#define DIR_Left_L     GPIO_ResetBits(GPIOA,GPIO_Pin_5);    //   ���ӷ���  ��

#define DIR_Right_H    GPIO_SetBits(GPIOA,GPIO_Pin_7);      //   ��������   ��
#define DIR_Right_L    GPIO_ResetBits(GPIOA,GPIO_Pin_7);    //   ���ӷ���   ��



void steppermotor_init();

void go_straight();

void stop_motor();

void start_motor();

void  turn_left();

void  turn_right();


#endif