#ifndef  _STEPPERMOTOR_H_
#define _STEPPERMOTOR_H_
				/***************** ��һ������������ת����57���*************************/
				/***************** EN->PG8 DIR --> PC6   PWM-->PC9*************************/
#define qianhou_ENA_CAN    GPIO_ResetBits(GPIOG,GPIO_Pin_8)       //ʹ��   
#define qianhou_ENA_NOT     GPIO_SetBits(GPIOG,GPIO_Pin_8)     //��ʹ��  

#define qianhou_DIR_positive     GPIO_SetBits(GPIOC,GPIO_Pin_7);      //   ��������    
#define qianhou_DIR_reverse     GPIO_ResetBits(GPIOC,GPIO_Pin_7);    //   ���ӷ��� 

#define qianhou_PWM_H     GPIO_SetBits(GPIOC,GPIO_Pin_9);      //      
#define qianhou_PWM_L     GPIO_ResetBits(GPIOC,GPIO_Pin_9);    //   
			/***************** �ڶ�����������ҵ��ƶ��� ϴͷ��42*************************/
				/***************** EN->PG2  DIR --> PG4   PWM-->PG6 *************************/
#define zuoyou_ENA_CAN    GPIO_ResetBits(GPIOG,GPIO_Pin_2)       //ʹ��    
#define zuoyou_ENA_NOT    GPIO_SetBits(GPIOG,GPIO_Pin_2)     //��ʹ��  

#define zuoyou_DIR_positive    GPIO_SetBits(GPIOG,GPIO_Pin_4);      //   ��������   
#define zuoyou_DIR_reverse    GPIO_ResetBits(GPIOG,GPIO_Pin_4);    //   ���ӷ��� 

#define zuoyou_PWM_H     GPIO_SetBits(GPIOG,GPIO_Pin_6);      //      
#define zuoyou_PWM_L     GPIO_ResetBits(GPIOG,GPIO_Pin_6);    //  
				/***************** ��������������µ��ƶ��� ˿�˻�̨*************************/
				/***************** EN->PD4  DIR --> PD2   PWM-->PD0 *************************/
#define shangxia_ENA_CAN    GPIO_ResetBits(GPIOD,GPIO_Pin_4)       //ʹ��    
#define shangxia_ENA_NOT    GPIO_SetBits(GPIOD,GPIO_Pin_4)     //��ʹ��  

#define shangxia_DIR_positive    GPIO_SetBits(GPIOD,GPIO_Pin_2);      //   ��������   
#define shangxia_DIR_reverse    GPIO_ResetBits(GPIOD,GPIO_Pin_2);    //   ���ӷ��� 

#define shangxia_PWM_H     GPIO_SetBits(GPIOD,GPIO_Pin_0);      //      
#define shangxia_PWM_L     GPIO_ResetBits(GPIOD,GPIO_Pin_0)    //  



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

