#include "timer.h"
#include "led.h"
#include "Photoelectric_door.h"
#include "details_func.h"
#include "steppermotor.h"

extern int zuozhuan_flag;
extern int youzhuan_flag;
extern int change_direction_flag;


extern char  second_qianhou_flag;
extern char  second_xiang_flag;


extern char second;

extern char reset_flag ;

extern int hair_dry_flag;

extern int Water_spray_flag;


//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
			if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
				{
						TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
								
							
														if(zuoyou_PDoor_L==1)//  ������ߵĹ����
														{
		
																		second_xiang_flag = 1; 
															
															
															
															      zuozhuan_flag  = 0;
														       	youzhuan_flag = 0;
															   
														}
														
														 if(zuoyou_PDoor_R==1)// �����ұߵĹ����
														{							
																			second_xiang_flag = 2;
																			second = 1;
																			Water_spray_flag = 1;
															
                                      zuozhuan_flag  = 1;
															        youzhuan_flag  = 1;
														}
														
														if(qianhou_PDoor_Q == 1)// ����ǰ���
														{
						
																  	second_qianhou_flag  = 1;
														}
														
														if(qianhou_PDoor_H == 1)  //  ��������Ĺ����
														{
						
																	 second_qianhou_flag  = 2;
															
																   reset_flag = 1;  
															
															
															
															     change_direction_flag  = 2;
																	
														}
													
														
													//	 hair dry �Ĺ����													
													if( HD_zuoyou_PDoor_L == 1)
													 {
															   hair_dry_flag = 3 ;
													 }	
													
													if(HD_zuoyou_PDoor_R == 1)
													 {
															   hair_dry_flag = 1 ;
														}											
						
					
				}
}


//����ʹ�õ��Ƕ�ʱ��4
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
extern int reset;

void TIM4_IRQHandler(void)   //TIM3�ж�
{
						if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
							{
								
											TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
										
																					if((reset>=3)&&(reset<7))
																					{
																			
																									shangxia_closedLoop_scan();
																	}
																				
					    }
				
}











