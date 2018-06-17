# include "steppermotor.h"
# include "sys.h"

extern u16 left_speed;   //�����ٶ�
extern u16 right_speed;  //�����ٶ�

/*
*********************************************************************************************************
*	�� �� ��:     steppermotor_init
*	����˵��:     ���������ʼ��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void steppermotor_init(void)         //  �������    ǰ���� ��  ����  ����io
{
       GPIO_InitTypeDef  GPIO_InitStructure;
       
			//ʹ��GPIOʱ��Դ
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PC
        
			//��ʼ��IO��
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_5;				
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOB, &GPIO_InitStructure);
	
			 GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_7 );  //�����ֵ��ʹ��λ����
			 GPIO_SetBits(GPIOB, GPIO_Pin_6);  //�����ֵ������
}

/*
*********************************************************************************************************
*	�� �� ��:     stop_motor
*	����˵��:     С��ֹͣǰ��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void stop_motor(void)
{    
   TIM_Cmd(TIM3, DISABLE);
	 TIM_Cmd(TIM1, DISABLE);
}


/*
*********************************************************************************************************
*	�� �� ��:     start_motor
*	����˵��:     С����ʼǰ��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void start_motor(void)
{
   TIM_Cmd(TIM3, ENABLE);
	 TIM_Cmd(TIM1, ENABLE);
}

/*
*********************************************************************************************************
*	�� �� ��:     speed_change
*	����˵��:     �ı�С���ٶ�
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void speed_change(void)
{
	 TIM_SetAutoreload(TIM3, left_speed);   //  ���������ٶ� 
   TIM_SetAutoreload(TIM1, right_speed);  //  ���������ٶ�
}


    
