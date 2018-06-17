#include "timer.h"


/////        ɨ��ʹ�á�

//ͨ�ö�ʱ���жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��5!
void Timer5_Init(u16 arr,u16 psc)
{
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

				TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
				TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
				TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
				TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
		 
			  	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
					TIM5, //TIM5
					TIM_IT_Update ,
					ENABLE  //ʹ��
					);
					NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
					NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
					NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
					NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

					TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����
									 
}

extern int Change_Speed;

extern int 	First_Servo_Target ;
extern int 	Second_Servo_Target ;
extern int  Third_Servo_Target ;
extern int  Forth_Servo_Target ;
extern int  Fifth_Servo_Target ;
extern int  Sixth_Servo_Target ;

extern int  First_ServoPWM  ;
extern int  Second_ServoPWM ;
extern int  Third_ServoPWM  ;
extern int  Forth_ServoPWM  ;
extern int  Fifth_ServoPWM  ;
extern int  Sixth_ServoPWM  ;	

/******************** TIM5  �ж�    ����*************************/
void TIM5_IRQHandler(void)   
{
					if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
						{
							  
										TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
						          	//===  ������ٶ�
							//====FIRST 
													if(First_ServoPWM >First_Servo_Target)
													{
																 First_ServoPWM  -= Change_Speed;
													}
													if(First_ServoPWM <First_Servo_Target)
													{
																 First_ServoPWM  += Change_Speed;
													}
													if(First_ServoPWM  ==  First_Servo_Target)
													{
																 First_ServoPWM  = First_Servo_Target;
													}
													
								//====SECOND
													if(Second_ServoPWM >Second_Servo_Target)
													{
																 Second_ServoPWM  -= Change_Speed;
													}else if(Second_ServoPWM <Second_Servo_Target)
													{
																 Second_ServoPWM  += Change_Speed;
													}else if(Second_ServoPWM  ==  Second_Servo_Target)
													{
																 Second_ServoPWM  = Second_Servo_Target;
													}					
							       
								//====THIRD
													if(Third_ServoPWM >Third_Servo_Target)
													{
																 Third_ServoPWM  -= Change_Speed;
													}else if(Third_ServoPWM <Third_Servo_Target)
													{
																 Third_ServoPWM  += Change_Speed;
													}else if(Third_ServoPWM  ==  Third_Servo_Target)
													{
																 Third_ServoPWM  = Third_Servo_Target;
													}					
									//====FORTH
													if(Forth_ServoPWM >Forth_Servo_Target)
													{
																 Forth_ServoPWM  -= Change_Speed;
													}else if(Forth_ServoPWM <Forth_Servo_Target)
													{
																 Forth_ServoPWM  += Change_Speed;
													}else if(Forth_ServoPWM  ==  Forth_Servo_Target)
													{
																 Forth_ServoPWM  = Forth_Servo_Target;
													}						
									//====Fifth
													if(Fifth_ServoPWM >Fifth_Servo_Target)
													{
																 Fifth_ServoPWM  -= Change_Speed;
													}else if(Fifth_ServoPWM <Fifth_Servo_Target)	
													{
																 Fifth_ServoPWM  += Change_Speed;
													}else if(Fifth_ServoPWM  ==  Fifth_Servo_Target)
													{	 
																 Fifth_ServoPWM  = Fifth_Servo_Target;
													}																				
											
											//====Sixth
													if(Sixth_ServoPWM >Sixth_Servo_Target)
													{
																 Sixth_ServoPWM  -= Change_Speed;
													}else if(Sixth_ServoPWM <Sixth_Servo_Target)	
													{
																 Sixth_ServoPWM  += Change_Speed;
													}else if(Sixth_ServoPWM  ==  Sixth_Servo_Target)
													{	 
																 Sixth_ServoPWM  = Sixth_Servo_Target;
													}									
						}
}



//==== USMART   ��������
void set_First(int value)
{
	First_Servo_Target = value;
}
void  set_Second(int value)
{
	Second_Servo_Target  = value;
}
void   set_T(int value)
{
	Third_Servo_Target = value;
}
void  set_Forth(int value)
{
	Forth_Servo_Target = value;
}
void  set_Fifth(int value)
{
	Fifth_Servo_Target = value;
}
void  set_six(int value)
{
	Sixth_Servo_Target = value;
}


void set_Change_Speed(int speed)
{
	Change_Speed = speed;
}

