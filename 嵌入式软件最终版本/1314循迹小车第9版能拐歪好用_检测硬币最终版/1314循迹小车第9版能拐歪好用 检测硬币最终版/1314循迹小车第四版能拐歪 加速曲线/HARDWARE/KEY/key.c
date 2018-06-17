#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//////**********************       ����   PB13    PB14   PB15 

/////***********************            ������   PC12

void KEY_Init(void) //    ����  ��  io     ��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//IO��ʹ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//   S1   S2   S3  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA0,8


}
void buzzer_Init() //   ������       ��ʼ��
{    
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //IO��ʹ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PB.12 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.8
        
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);						 //PB.12 �����

}

    
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY1����
//2��KEY2����
//3��KEY3���� 
//4��KEY4���� 
//ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3>KEY4!!
 u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(S13==0||S14==0||S15==0) )
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(S13==0)return KEY13_PRES;
		else if(S14==0)return KEY14_PRES;
		else if(S15==0)return KEY15_PRES;
		
	}else if(S13==1&&S14==1&&S15==1)key_up=1; 	    
 	return 0;// �ް�������
}


