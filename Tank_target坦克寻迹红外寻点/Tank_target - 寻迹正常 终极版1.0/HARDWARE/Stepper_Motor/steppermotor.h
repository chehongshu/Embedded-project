#ifndef _STEPPERMOTOR_H_
#define _STEPPERMOTOR_H_

#define L_ENA_CAN     GPIO_SetBits(GPIOA,GPIO_Pin_4)       //ʹ��    �� 
#define L_ENA_NOT     GPIO_ResetBits(GPIOA,GPIO_Pin_4)     //��ʹ��  ��

#define R_ENA_CAN    GPIO_SetBits(GPIOA,GPIO_Pin_6)       //ʹ��    ��
#define R_ENA_NOT    GPIO_ResetBits(GPIOA,GPIO_Pin_6)     //��ʹ��  ��

#define L_DIR_positive     GPIO_SetBits(GPIOA,GPIO_Pin_5);      //   ��������  ��  
#define L_DIR_reverse     GPIO_ResetBits(GPIOA,GPIO_Pin_5);    //   ���ӷ���  ��

#define R_DIR_positive    GPIO_SetBits(GPIOA,GPIO_Pin_7);      //   ��������   ��
#define R_DIR_reverse    GPIO_ResetBits(GPIOA,GPIO_Pin_7);    //   ���ӷ���   ��

//���������ʼ��
void steppermotor_init(void);

//ֹͣǰ��
void stop_motor(void);

//��ʼǰ��
void start_motor(void);

//�ı�С���ٶ�
void speed_change(void);

void little_speed(void);

////С��ֱ��
//void go_straight(void);

////�����
//void turn_left(void);

////�ҹ���
//void  turn_right(void);


#endif

