#include "Infr_recei.h"
#include "sys.h"
#include "delay.h"
#include "blue_tooth.h"

////����������ĳ�ʼ����  �õ���adֵ
/************************************************
////  �ֵ�
/ ����ߵ�ioΪ PA5			   ADC��5ͨ��   ���ұߵ�PA0   ADC ��0ͨ��
 �ۺ����ioΪ    PA4   ADC��4ͨ��
 ��ǰ ��1��ƫ����� �ģ�   PC2      ADC��12ͨ�� ��  ǰ��2  ��ƫ�����ĵģ� PC1     ADC��11ͨ��
 ��ǰ ��1��ƫ����� �ģ�   PB0      ADC��8ͨ��  ��   ǰ��2  ��ƫ�����ĵģ�  PC0    ADC��10ͨ��
 �������뼤���غϵ�ioΪ    PC4      ADC��14ͨ��
 
 /////΢��
 ���� PC5 Ϊ ADC��15ͨ��   ��10��. ��PC3 Ϊ ADC��13ͨ��
 
/
**********************************************/
int CH_ALLL[]={5,0,4,12,11,8,10,14,15,13};
double  voltage[10];
       u16  adcx;

/*
*********************************************************************************************************
*	�� �� ��:       void  Infr_recei_three_Init(void)    
*	����˵��:            ��  adc1 ��ʮ��ͨ����ʼ��
*	��    �Σ�    										void
*	�� �� ֵ:                			  void
*********************************************************************************************************
*/

		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Infr_recei_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 10;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}		
/*
*********************************************************************************************************
*	�� �� ��:       u16 Get_Adc(u8 ch,int ch_rank)   
*	����˵��:            ���ADCֵ
*	��    �Σ�    						   ch   ͨ��   ch_rank   �����õ�˳��
*	�� �� ֵ:                   ADC ������ֵ
*********************************************************************************************************
*/

u16 Get_Adc(u8 ch,int ch_rank)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, ch_rank, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
/*
*********************************************************************************************************
*	�� �� ��:             u16 Get_Adc_Average(u8 ch,u8 times,int rank)
*	����˵��:                 ��� ĳ��ͨ����ƽ��ֵ
*	��    �Σ�    						   ch   ͨ��   times   ����  rank   �����õ�˳��
*	�� �� ֵ:                   ADC ��ƽ��ֵ  ����׼ȷ
*********************************************************************************************************
*/
u16 Get_Adc_Average(u8 ch,u8 times,int rank)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch,rank);
		delay_ms(5);
	}
	return temp_val/times;
} 
/*
*********************************************************************************************************
*	�� �� ��:                 void Get_ADC_ALL(void )
*	����˵��:                 ��� ʮ��ͨ����  ADC�ĵ�ѹת��ֵ
*	��    �Σ�    						  void
*	�� �� ֵ:                   ȫ�ֱ���   voltage[i]����ADCת����ADC��ֵ
*********************************************************************************************************
*/
void Get_ADC_ALL(void )
{
	
	int i=0;
	for(i=0;i<10;i++){
				adcx=Get_Adc_Average(CH_ALLL[i],5,1);// ƽ��ֵ
				voltage[i]=(double)adcx*(3.3/4096);	//  ��ѹ
	}
}
void Get_ADCZ(void)
{
				adcx=Get_Adc_Average(CH_ALLL[7],5,1);// ƽ��ֵ
				voltage[7]=(double)adcx*(3.3/4096);	//  ��ѹ
}
///��  ��ʱ�����ϵ�ɨ��
//// �õ��⼸��ADֵ


void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	
	TIM_Cmd(TIM2, ENABLE); 	 
}
extern int j;
void TIM2_IRQHandler(void)   
{	
			if ( RESET!=TIM_GetITStatus(TIM2, TIM_IT_Update) )
			{
										Get_ADCZ();
										Blue_tooth_number(USART2,voltage[7]);
										Blue_tooth_number(USART2,j); 
				
								TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
				
		}
}



