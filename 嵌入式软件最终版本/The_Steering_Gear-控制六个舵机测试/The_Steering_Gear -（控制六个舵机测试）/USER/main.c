#include  "sys.h"
#include  "delay.h"
#include  "usart.h"
#include  "pwm.h"
#include  "key.h"
#include  "timer.h"
#include  "usmart.h"



int KEYMODE;						//=== ����
int Change_Speed;		//===  �ı���ٶ�

//int Servo_PWMS[6][6]={};
	
int 	First_Servo_Target = 1500;
int 	Second_Servo_Target = 1500;
int  Third_Servo_Target = 2400;
int  Forth_Servo_Target = 2500;
int  Fifth_Servo_Target = 1500;
int  Sixth_Servo_Target = 1200;

int  First_ServoPWM  = 1500;
int  Second_ServoPWM =1500;
int  Third_ServoPWM  = 2400;
int  Forth_ServoPWM = 2500 ;
int  Fifth_ServoPWM  = 1500;
int  Sixth_ServoPWM = 1200;	
int main(void)
{		
	 
								delay_init();	    	 //��ʱ������ʼ��	  
								NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
								uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
								usmart_dev.init(72);           //===    ��Ƭ��   ����Ƶ  72M    USMART ������
								/*
								 0.5ms--------------0
								 1.0ms------------45
								 1.5ms------------90
								 2.0ms-----------135
								 2.5ms-----------180*/
								TIM3_PWM_Init(2505,71);  //   2.5ms
								TIM4_PWM_Init(2505,71);  //   2.5ms 
								Timer5_Init(10000-1,7200-1);//1ms
	              
							  KEY_Init();
	
	              set_Change_Speed(40);
					      	while(1){

										
										
//																	KEYMODE   = 		  KEY_Scan(1);
//																	switch(KEYMODE)
//																	{
//																		case KEY1_PRES: 
//																						 servo_number++;
//																						     	break;
//																		case KEY2_PRES: break;
//																		case KEY3_PRES: break;

																	
																	        TIM_SetCompare3(TIM3,First_ServoPWM);
																	   
                       					    	  	TIM_SetCompare4(TIM3,Second_ServoPWM);
      															
                                        	TIM_SetCompare1(TIM4,Third_ServoPWM);
																	
          													      TIM_SetCompare2(TIM4,Forth_ServoPWM);
//														
      															      TIM_SetCompare3(TIM4,Fifth_ServoPWM);
//   
                                        	TIM_SetCompare4(TIM4,Sixth_ServoPWM);
																			
    																	
															}		


}									
																	
																  

	
				
 