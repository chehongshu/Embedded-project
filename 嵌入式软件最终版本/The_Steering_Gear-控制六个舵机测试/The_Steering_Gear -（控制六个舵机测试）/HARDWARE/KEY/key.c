#include "key.h"
#include "delay.h"

/*********************************
*  four keys
*  PC12   PC11  PC9 PC8
*
*******************************/
 	    
//������ʼ������ 
void KEY_Init(void)
{
	
				GPIO_InitTypeDef GPIO_InitStructure;

				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��

				GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
				
				GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
				GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
				
				GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
				GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5
//			 
				GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
				GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
				
//				GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PC8
//				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
//				GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.0
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==1||KEY4==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==1)return KEY3_PRES; 
		else if(KEY4==0)return KEY4_PRES;
	}else if(KEY1==1&&KEY2==1&&KEY3==0&&KEY4==1)key_up=1; 	     
	return 0;
}
