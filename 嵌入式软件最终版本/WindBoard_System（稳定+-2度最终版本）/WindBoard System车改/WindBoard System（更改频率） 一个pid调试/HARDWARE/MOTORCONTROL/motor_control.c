# include "motor_control.h"
# include "screen.h"
# include "led.h"
# include "sysvalue.h"
# include "beep.h"

extern float pitch;
extern u8 targetData1;
extern u8 sysCurrentStyle;
//����Ŀ��Ƕ�
extern double targetData;

//������Ŀ1ģʽ
void base1Mode(void)
{
					static int cnt = 0;  //��ʱ5s
					static int flag = 0; //�Ƿ񵽴�Ŀ��ֵ��־λ
					static int flag2 = 0;  //�����Ƿ񵽴��յ��־λ
					baseRun();//=== �����㷨
	      //  promoteRun();//=== ����㷨
					freshData();//=== ˢ12864
					
//					if ( 0==flag )
//					{
//						flag = isTarget(targetData1);
//					}
//					else if ( 1==flag )  //����Ŀ��㷢�����ⱨ��
//					{
//								cnt++;
//								LED1 = !LED1;
//								LED2 = !LED2;
//								LED3 = !LED2;
//								BEEP = 1;
//									if ( cnt>=1300 )  //���¼�ʱһ��ʱ��
//									{
//												//targetData1 = 150;  //Ŀ��ֵ��Ϊ150ʹ���ͣ���յ�
//												TIM_SetCompare1(TIM4, 0);
//												cnt = 0;
//												flag2 = 1;  
//									}
//					}
//					
//					if ( 1==flag2 )
//					{
//						if ( (90-pitch)>120 )
//						{
//							//ֹͣ���ת��
//							TIM_SetCompare1(TIM3, 0);
//							TIM_SetCompare1(TIM4, 0);
//							sysCurrentStyle = SYS_MENU;  //�������ز˵�����
//							flag = 0;
//							flag2 = 0;
//							BEEP = 0;
//						}
//					}
}

//������Ŀ2
void base2Mode(void)
{
	baseRun();
	freshData();
	
	//if ( (90-pitch)>)
}

//�ж��Ƿ�ﵽĿ��ֵ
u8 isTarget(int dat)
{
	static int cnt = 1;
	int sum = 0;
	static float data[5] = {0};
  u8 i = 0;
	cnt ++;
	if ( 0==cnt%200 )
	{
		sum = 0;
		cnt = 0;
		
		//��ȡ���5�ε�����
		for (i=0; i<4; i++)
		{
			data[i] = data[i+1];
		}
		data[i] = 90-pitch;
		
		//���
		for (i=0; i<5; i++)
		{
			sum += data[i];
		}
		
		//�������ƽ��ֵ������5�ȷ�Χ�����ʾ����Ŀ���
		if ( (sum/5)>=dat-5 && (sum/5)<dat+5)
		{
			return 1;
		}
	}
	return 0;
}

//Ӳ�����У׼
int changeData(u8 dat)
{
	if ( dat<=60 && dat>45 )   //�����Ŀ��������40-60֮��
	{
		return dat-5;
	}
	else if ( dat>60 && dat<=80 )
	{
		return dat;
	}
	else if ( dat>=100 && dat<105 )
	{
		return dat;
	}
	
	return 0;  //���ݴ��󷵻�0
}


