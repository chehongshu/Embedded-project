#include "steppermotor.h"
#include "sys.h"

//long double qcsl;//����Ȧ��
//long double qcsr;//����Ȧ��
extern u16 set_duty_left;
extern u16 set_duty_right;


void steppermotor_init()         //  �������    ǰ���� ��  ����  ����io
{
       GPIO_InitTypeDef  GPIO_InitStructure;
        
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PC
        
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
       GPIO_Init(GPIOA, &GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
    
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
    
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void start_motor()
{    
   ENA_Left_L   ;
   ENA_Right_L  ;        
   DIR_Left_L   ;
   DIR_Right_L  ;
}

void stop_motor()
{
   ENA_Left_H   ;
   ENA_Right_H  ;
    


}