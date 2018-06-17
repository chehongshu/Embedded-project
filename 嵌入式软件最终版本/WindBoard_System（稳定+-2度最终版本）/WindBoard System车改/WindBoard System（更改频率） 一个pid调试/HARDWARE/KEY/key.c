# include "key.h"
# include "delay.h"
# include "sysvalue.h"
# include "screen.h"
# include "led.h"

extern u8 sysCurrentStyle;
extern u8 selectBtn;
extern u8 numLocate;
extern u8 targetData1;
extern u8 targetData2[2];
 	    
//������ʼ������ 
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	
} 

//����ɨ��
u8 KEY_Scan(void)
{	 
	static u8 key_up = 1;  		  
	if(key_up&&(KEY1==1 || KEY2==1 || KEY3==1 || KEY4==1 || KEY5==1 || KEY6==1))
	{
		delay_ms(10);
		key_up=0;
		if(KEY1==0)
		{
			return KEY1_PRES;
		}
		else if( KEY2==0 )
		{
			return KEY2_PRES;
		}	
		else if( KEY3==0 )
		{
			return KEY3_PRES; 
		}
		else if ( KEY4==0 )
		{
			return 	KEY4_PRES;
		}
		else if ( KEY5==0 )
		{
			return KEY5_PRES;
		}
		else if ( KEY6==0 )
		{
			return KEY6_PRES;
		}
	}else if( KEY1==1 && KEY2==1 && KEY3==1 && KEY4==1 && KEY5==1 && KEY6==1 )
	{
		key_up=1;
	} 	     
	return 0;
}

/************************************
����1����ʵ�֣�-��
************************************/
void KEY1_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//���ܴ���
	switch ( sysCurrentStyle )
	{
		case SYS_MENU: selectBtn = selectBtn%2+1; showMenu(selectBtn); break;   //�ڲ˵����水�°���1�л�������
		case SYS_BASE1_SET: changeTargetDataDown(&targetData1); allQuestion1Set(numLocate); break;	//������1���ý������������ݼ�
		case SYS_IMPROVE1_SET: changeTargetDataDown(&targetData1); allQuestion1Set(numLocate); break;	//�����1���ý������������ݼ�
		case SYS_BASE2_SET1: changeTargetDataDown(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //������2���ý�������������1��
		case SYS_BASE2_SET2: changeTargetDataDown(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //������2���ý�������������2��
		case SYS_IMPROVE2_SET1: changeTargetDataDown(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //������2���ý�������������1��
		case SYS_IMPROVE2_SET2: changeTargetDataDown(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //������2���ý�������������2��
		default: break;
	}
}

/************************************
����2����ʵ�֣�+��
************************************/
void KEY2_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//���ܴ���
	switch( sysCurrentStyle )
	{
		case SYS_MENU: selectBtn = selectBtn%2+3; showMenu(selectBtn); break;   //�ڲ˵����水�°���2�л������
		case SYS_BASE1_SET: changeTargetDataUp(&targetData1); allQuestion1Set(numLocate); break;	 //������1���ý������������ݼ�
		case SYS_IMPROVE1_SET: changeTargetDataUp(&targetData1); allQuestion1Set(numLocate); break;	 //�����1���ý������������ݼ�
		case SYS_BASE2_SET1: changeTargetDataUp(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //������2���ý�������������1��
		case SYS_BASE2_SET2: changeTargetDataUp(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //������2���ý�������������2��
		case SYS_IMPROVE2_SET1: changeTargetDataUp(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //�����2���ý�������������1��
		case SYS_IMPROVE2_SET2: changeTargetDataUp(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //�����2���ý�������������2��
		default: break;
	}
}

/************************************
����3����ʵ�֣�ȷ�ϣ�
*************************************/
void KEY3_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//���ܴ���
	switch ( sysCurrentStyle )
	{
		case SYS_MENU: MenuSureKey_Fun(); break;  //ѡ��С���
		case SYS_BASE1_SET:sysCurrentStyle = SYS_BASE1_START; allQuestion1Start(1); break;//������1������ɿ�ʼ����
		case SYS_IMPROVE1_SET:sysCurrentStyle = SYS_IMPROVE1_START; allQuestion1Start(2); break;//�����1������ɿ�ʼ����
		case SYS_BASE2_SET1:sysCurrentStyle = SYS_BASE2_SET2; numLocate=1; allQuestion2Set(numLocate, 1); break;//������2����1������ɿ�ʼ���ò���2
		case SYS_BASE2_SET2:sysCurrentStyle = SYS_BASE2_START; allQuestion2Start(1); break; //������2����������Ͽ�ʼ����
		case SYS_IMPROVE2_SET1:sysCurrentStyle =SYS_IMPROVE2_SET2; numLocate=1; allQuestion2Set(numLocate, 1); break;//������2����1������ɿ�ʼ���ò���2
		case SYS_IMPROVE2_SET2:sysCurrentStyle = SYS_IMPROVE2_START;allQuestion2Start(2); break; //�����2����������Ͽ�ʼ����
		default: break;
	}
}

/************************************
����4����ʵ�֣�����λѡ��
************************************/
void KEY4_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//���ܴ���
	switch ( sysCurrentStyle )
	{
		case SYS_BASE1_SET: 
		case SYS_IMPROVE1_SET: numLocate = numLocate%3; numLocate++; allQuestion1Set(numLocate); break;
		case SYS_BASE2_SET1: numLocate = numLocate%3; numLocate++; allQuestion2Set(numLocate, 0); break;
		case SYS_BASE2_SET2: numLocate = numLocate%3; numLocate++; allQuestion2Set(numLocate, 1); break;
		case SYS_IMPROVE2_SET1: numLocate = numLocate%3; numLocate++; allQuestion2Set(numLocate, 0); break;
		
		default: break;
	}
}

/************************************
����5����ʵ�� �����У�
************************************/
void KEY5_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//���ܴ���
	switch ( sysCurrentStyle )
	{
		case SYS_BASE1_START: sysCurrentStyle = SYS_BASE1_RUNING; allQuestion1Runing(1); break;
		case SYS_BASE2_START: sysCurrentStyle = SYS_BASE2_RUNING; allQuestion2Running(1); break;
		case SYS_IMPROVE1_START: sysCurrentStyle = SYS_IMPROVE1_RUNING; allQuestion1Runing(2); break;
		case SYS_IMPROVE2_START: sysCurrentStyle = SYS_IMPROVE2_RUNING; allQuestion2Running(2); break;
		default: break;
	}
}

/************************************
����6����ʵ�� �����������������˵���
*************************************/
void KEY6_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//���ܴ���
	switch ( sysCurrentStyle )
	{
		case SYS_BASE1_START: 
		case SYS_IMPROVE1_START: 
		case SYS_BASE2_START: 
		case SYS_IMPROVE2_START: 
		case SYS_BASE1_RUNING:
		case SYS_BASE2_RUNING:
		case SYS_IMPROVE1_RUNING:
		case SYS_IMPROVE2_RUNING:
		sysCurrentStyle = SYS_MENU; selectBtn=1; numLocate = 1; showMenu(selectBtn); targetData1=0; targetData2[0] = 0; targetData2[1]=0; TIM_SetCompare1(TIM3,0); TIM_SetCompare1(TIM4,0);break; //��С�����н����ص��˵�����
		default: break;
	}
}

/**********************************
�˵�ȷ�ϼ�����ʵ��
**********************************/
void MenuSureKey_Fun(void)
{
	switch ( selectBtn ) //�ж�ѡ�е�Ŀ��
	{
		case BASE1: sysCurrentStyle = SYS_BASE1_SET; allQuestion1Set(numLocate); numLocate = 1; break;
		case BASE2: sysCurrentStyle = SYS_BASE2_SET1; allQuestion2Set(numLocate, 0); break;
		case IMPROVE1: sysCurrentStyle = SYS_IMPROVE1_SET; allQuestion1Set(numLocate); break;
		case IMPROVE2: sysCurrentStyle = SYS_IMPROVE2_SET1; allQuestion2Set(numLocate, 0); break;
		default: break;
	}
}

/************************************
�ı�Ŀ��ֵ�������ӣ�
*************************************/
void changeTargetDataUp(u8 * data)
{
		if ( 1==numLocate ) //���ð�λ
		{
			 if ((*data)<80) (*data)+=100;
		}
		else if ( 2==numLocate ) //����ʮλ
		{
			if ( (1==(*data)/100 && (*data)%100<70 && (*data)%100/10<9) || (0==(*data)/100 && (*data)%100/10<9) )
			{
				*data += 10;
			}
		}
		else if ( 3==numLocate ) //���ø�λ
		{
			if ( (*data)<180 && ((*data)%10)<9)
			{
				(*data)++;
			}
		}
}

/************************************
�ı�Ŀ��ֵ����������
*************************************/
void changeTargetDataDown(u8 * data)
{
		if ( 1==numLocate ) //���ð�λ
		{
			 if ((*data)>100) (*data)-=100;
		}
		else if ( 2==numLocate ) //����ʮλ
		{
			if ( (*data)%100/10>0 )
			{
				*data -= 10;
			}
		}
		else if ( 3==numLocate ) //���ø�λ
		{
			if ( (*data)%10>0 )
			{
				(*data)--;
			}
		}
}






