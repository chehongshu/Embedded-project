# include "beep.h"

//��������ʼ��
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ��ϵͳʱ��Դ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//��ʼ��IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

