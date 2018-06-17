#include "timer.h"
#include "led.h"


void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef    T;
	NVIC_InitTypeDef           N;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//��ͨ��ʱ������APB1
	T.TIM_Period=arr;//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	T.TIM_Prescaler=psc;//Ԥ��Ƶֵ
	T.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ��Դ��Ƶ
	T.TIM_CounterMode=TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5,&T);//��ʼ��TIm3
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//ʹ��TIM3�����жϣ��������� �Ƚ�ֵ��
   N.NVIC_IRQChannel=TIM5_IRQn;
	N.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�
	N.NVIC_IRQChannelSubPriority=2;//��Ӧ���ȼ�
	N.NVIC_IRQChannelCmd=ENABLE;//ʹ���ж�2����
	NVIC_Init(&N);//��ʼ���жϷ���
    TIM_Cmd(TIM5,ENABLE);//ʹ������
}



/*********************         �жϲ���                  **********************/

extern u32 second; 

extern u16 duty_left;
extern u16 duty_right;
extern u16 set_duty_left;
extern u16 set_duty_right; 



void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	         second++;
		}
}
void TIM5_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 

        if(duty_left>set_duty_left)
              duty_left  -=  10;
        if(duty_left<set_duty_left)
                duty_left  += 10;
        
        if(duty_left==set_duty_left)
            duty_left=set_duty_left;
        
        if(duty_right>set_duty_right)
                duty_right -= 10;
        if(duty_right<set_duty_right)
                duty_right += 10 ;
         
        if(duty_right==set_duty_right)
           duty_right=set_duty_right;
       
		}
}











