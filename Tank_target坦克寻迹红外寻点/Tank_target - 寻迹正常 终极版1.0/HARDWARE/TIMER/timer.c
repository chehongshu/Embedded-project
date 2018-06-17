# include "timer.h"
# include "ST_drive.h"
# include "steppermotor.h"
# include "led.h"

u8 second = 0;   //�����С����ʼ��������ʱ��
u8 counter = 0;  //�����������ĸ���

/*
*********************************************************************************************************
*	�� �� ��:     TIM5_Int_Init
*	����˵��:     ��ʱ��5�жϳ�ʼ�� 
*	��    �Σ�    arr װ��ֵ  psc Ԥ��Ƶ (1ms��һ���ж�)
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM5_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//��ʱ��ʱ��Դʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 

	//��ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
 
	//�ж�ʹ��
	TIM_ITConfig(TIM5, TIM_IT_Update ,ENABLE);
	
	//�����ж���������
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	//������ʱ��
	TIM_Cmd(TIM5, ENABLE); 	 
}

/*
*********************************************************************************************************
*	�� �� ��:     TIM6_Int_Init
*	����˵��:     ��ʱ��6�жϳ�ʼ��
*	��    �Σ�    arr װ��ֵ  psc Ԥ��Ƶ (1s��һ���ж�)
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//��ʱ��ʱ��Դʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 

	//��ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
 
	//�ж�ʹ��
	TIM_ITConfig(TIM6, TIM_IT_Update ,ENABLE);
	
	//�����ж���������
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	//������ʱ��
	TIM_Cmd(TIM6, ENABLE); 	 
}

/*
*********************************************************************************************************
*	�� �� ��:     TIM7_Int_Init
*	����˵��:     ��ʱ��7�жϳ�ʼ��
*	��    �Σ�    arr װ��ֵ  psc Ԥ��Ƶ (1s��һ���ж�)
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//��ʱ��ʱ��Դʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 

	//��ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
 
	//�ж�ʹ��
	TIM_ITConfig(TIM7, TIM_IT_Update ,ENABLE);
	
	//�����ж���������
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	//������ʱ��
	TIM_Cmd(TIM7, ENABLE); 	 
}

u16 left_speed = SPEED_VALUE;     //����װ��ֵ
u16 right_speed = SPEED_VALUE;    //�ҳ���װ��ֵ
u8 RightDir_Flag = 0;             //�ҳ��ַ����־λ
u8 Stop_Flag = 0;                 //�������λ��ֹͣ��־λ
u8 time = 0;                      //�����ʱ
u8 time_flag = 0;                 //�����ʱ�жϱ�־λ

/*
*********************************************************************************************************
*	�� �� ��:     TIM5_IRQHandler
*	����˵��:     ��ʱ��5�жϷ����� ��С��Ѱ��ʵ�֣�
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM5_IRQHandler(void)   
{
	static u16 i = 0;
	//������ʱ������ж�
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) 
		{
			//���ֿ�������
			 if ( 0==ST_Left_First && 1==ST_Left_Second )     
				{
					 left_speed = 2000;                           //���ּ���    
					 right_speed = SPEED_VALUE;                   //�ҳ��ֳ��ٲ���
					 speed_change();                              //������� //  �ı���Ӧ�� Ƶ��
					
												 if ( 1==time_flag )
												 {
													 time_flag = 0;                               //�����־λ����
													 time = 0;                                    //�����ʱ����
													 Warning_Stop();
												 }
				}
				//�ҳ��ֿ�������
				if ( 1==ST_Right_First && 0==ST_Right_Second )  
				{
					 right_speed = 2000;                           //�ҳ��ּ���    
					 left_speed = SPEED_VALUE ;                   //���ֳ��ٲ���
					 speed_change();                              //���ҹ���
					
													 if ( 1==time_flag )
													 {
														 time_flag = 0;                               //�����־λ����
														 time = 0;                                    //�����ʱ����
														 Warning_Stop();
													 }
				}
				
													//�����ж�
													if ( 1==ST_Right_First && 1==ST_Right_Second && 0==time_flag)
													{
														time_flag = 1;																//�����־λ��λ
														time = 0;																			//�����ʱ����
														
													}
				
				//��ת����������
				if ( 0==RightDir_Flag && second>12 )
				{
					if ( 0==ST_Right_First && 1==ST_Right_Second && 1==ST_Left_First && 1==ST_Left_Second)//0111
					{
						LED0 = 1;//   ����
						right_speed = SPEED_VALUE;
						GPIO_ResetBits(GPIOB, GPIO_Pin_6);  //���ַ�ת
						RightDir_Flag = 1;                  //��־����  �� ��־λ ֮�󲻽����if  ֮��  ��־λΪ2  ������ʱ�ͼ�������
					}
			  }
				
			//���������
			if ( ((0==ST_Right_First && ( 0==ST_Right_Second || 0==ST_Left_First)) || (0==ST_Left_Second && (0==ST_Right_Second || 0==ST_Left_First) ) )&& 0==Stop_Flag ) 
			{
				 Stop_Flag = 1;                                //�������λ��ֹͣ��־λ��λ
				 counter ++;
			}
			//  ����ֹͣ
			if ( Stop_Flag  )
			{
				if ( 1==counter ) //���ʱ��ֹͣ��С����ʼǰ��// ��һ��
				{ 
					Stop_Flag = 0;
				}
				else if ( counter>1 && counter<=6 )// ���˵�һ�κ����һ��
				{
					i++;
					if ( 900==i )   //ɨ�赽�ڻ�����ʱ900���ж�����ֹͣС��
					{
					 stop_motor();                                 //С��ֹͣ����
					 Warning_Start();                              //���濪ʼ
					}
					if ( 3000==i && counter!=6 )           //��ͣ3000-900���ж����ں�С����ʼ����  �������ߵ�6�κ�С��ֹͣ
					{
						start_motor();
						Warning_Stop();
						i = 0;
						Stop_Flag = 0;
					}
				}
				
			}
		
		}
    //����жϱ�־λ
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  
}

/*
*********************************************************************************************************
*	�� �� ��:     TIM6_IRQHandler
*	����˵��:     ��ʱ��6�жϷ����� �� 0.5s���ж� ʵ�ּ�ʱ��
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM6_IRQHandler(void)   
{	
	if ( RESET!=TIM_GetITStatus(TIM6, TIM_IT_Update) )
	{
		second ++;  //��ֵ��0.5
		
		if ( 1==time_flag )  //ƫ�����ж�
		{
			time++;
			
			if ( time>=3 )     //ƫ��1.5s��ʼ����
			{
				Warning_Start();
			}
		}
	}
	
	if ( second>240 )      //ȫ�̳��������� ��ʼ����
	{
		Warning_Start();                                  //���󾯸� 
		stop_motor();                                     //ֹͣ����
	}
	
	//����жϱ�־λ
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  
}

/*
*********************************************************************************************************
*	�� �� ��:     TIM7_IRQHandler
*	����˵��:     ��ʱ��7�жϷ�����(���� ���� ����)
*	��    �Σ�    void
*	�� �� ֵ:     void 
*********************************************************************************************************
*/
void TIM7_IRQHandler(void)   
{	
	static u16 i = 0;
	
	if ( RESET != TIM_GetITStatus(TIM7, TIM_IT_Update) )
	{
		if ( 0==Stop_Flag ) //��������ʵ��
		{
			if ( right_speed>SPEED_VALUE )
			{
				right_speed -= 100;//  ���൱�ڼӣ���Ϊ arrԽС Ƶ��Խ��  �ٶ�Խ��
				speed_change();  //
			}
			else 
			{
				right_speed = SPEED_VALUE;
				speed_change();  //
			}
			
			if ( left_speed>SPEED_VALUE )
			{
				left_speed -= 100;
				speed_change();//
			}
			else 
			{
				left_speed = SPEED_VALUE;
				speed_change(); //
			}
	  }
		else if ( 1==Stop_Flag ) //��������ʵ��
		{
			right_speed += 30;
			left_speed += 30;
			speed_change(); //
		}
		
		//��ת���������  ����ʱ�� ����run�ĺ���
		if ( 1==RightDir_Flag && (++i)==220 )   //   220Ϊ������ʱ��  
		{ 
			LED0 = 0;
			GPIO_SetBits(GPIOB, GPIO_Pin_6);//  ��ת  ������   ��ת��
			RightDir_Flag++;//  �Ӵ˲��������������
		}
	}
	
	//����жϱ�־λ
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  
}






