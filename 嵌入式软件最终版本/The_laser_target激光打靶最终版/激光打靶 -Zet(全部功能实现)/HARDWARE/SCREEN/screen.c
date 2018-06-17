# include "screen.h"
# include "sysvalue.h"
# include "usart.h"
# include "led.h"
# include "math.h"
# include "moveMotor.h"
# include "delay.h"

//���ڷ��ص�����
extern int uartReceiveData;
//�õ�������XY����
extern void getXY(int * x, int * y);
//����У׼�����ĵ�ͱ�Ե��
extern int adjustPoint[2][2];
//��ǰ��������
int currentPoint[2] = {0}; 
//��ʱ�����˸��������
int tempSlightPoint[2] = {0};
 //���ĵĺͱ�Ե��ľ���
double adjustPointDis = 0;
//��ǰ����е�ľ���
double currentDisToPoint = 0;
//����Դ����ʱ���ʱ��־λ
int cntFlag = 0;

//�����3�ﵽ���⻷��
void improve3Fun(u8 target)
{
	int i=0;
	int currentDisX = 0;
	int currentDisY = 0;
	
	//��������ͷ���񵽵����ĵ�ͱ�Ե������Ļ�ϵľ���
	adjustPointDis = sqrt( (double)adjustPoint[1][0]*(double)adjustPoint[1][0] + (double)adjustPoint[1][1]*(double)adjustPoint[1][1]);
	
	//���㵱ǰ������赽��Ŀ�껷����x��y�������
	switch ( target)
	{
		case 4: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*7- (adjustPointDis/16.0))); break;
		case 5: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*6- (adjustPointDis/16.0))); break;
		case 6: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*5- (adjustPointDis/16.0))); break;
		case 7: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*4- (adjustPointDis/16.0))); break;
		case 8: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*3- (adjustPointDis/16.0))); break;
		case 9: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*2- (adjustPointDis/16.0))); break;
		default: break;
	}
	
	//x���긴λ
	if (currentDisX<0)
	{
		for (i=0; i<(int)(1.75*(double)(fabs)(currentDisX)); i++)
		{
			moveX(0);
		}
	}
	else if ( currentDisX>0 )
	{
		for (i=0; i<(int)(1.75*(double)(currentDisX)); i++)
		{
			moveX(1);
		}
	} 
	
	//y���긴λ
	if ( currentDisY<0 )
	{
		for (i=0; i<(int)(0.85*(double)(fabs)(currentDisY)); i++)
		{
			moveY(1);
		}
	}
	else if ( currentDisY>0 )
	{
		for (i=0; i<(int)(0.85*(double)(currentDisY)); i++)
		{
			moveY(0);
		}
	}
	
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	cntFlag = 1;
	uartReceiveData = 0;
}
	
//�����2�ص�10��
void improve2Fun(void)
{
	int i=0;
	
	//x���긴λ
	if (currentPoint[0]<0)
	{
		for (i=0; i<(int)(1.75*(double)(fabs)(currentPoint[0])); i++)
		{
			moveX(0);
			//delay_ms(10);
		}
	}
	else if ( currentPoint[0]>0 )
	{
		for (i=0; i<(int)(1.75*(double)(currentPoint[0])); i++)
		{
			moveX(1);
		}
	} 
	
	//y���긴λ
	if (currentPoint[1]<0)
	{
		for (i=0; i<(int)(0.85*(double)(fabs)(currentPoint[1])); i++)
		{
			moveY(1);
		}
	}
	else if ( currentPoint[1]>0 )
	{
		for (i=0; i<(int)(0.85*(double)(currentPoint[1])); i++)
		{
			moveY(0);
		}
	}
	
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	cntFlag = 1;
	uartReceiveData = 0;
}

//�õ���ǰ��������
void getCurrentPoint(void)
{
	//�õ�����
	getXY(&currentPoint[0], &currentPoint[1]);
	
	//����Ļ����ת��Ϊ������Ϊԭ�������ֵ
	currentPoint[0] = currentPoint[0] - adjustPoint[0][0];
	currentPoint[1] = adjustPoint[0][1] - currentPoint[1];
	
	printf("t2.txt=\"%d,%d\"", currentPoint[0], currentPoint[1]); stop(); 
	printf("t2.txt=\"%d,%d\"", currentPoint[0], currentPoint[1]); stop(); 
	printf("t2.txt=\"%d,%d\"", currentPoint[0], currentPoint[1]); stop(); 
	
	uartReceiveData=0;
}

//�����1��ʾ����
void improve1Fun(void)
{
	
	//��ȡ��ǰ��������
	getXY(&currentPoint[0], &currentPoint[1]); 
	
	//����Ļ����ת��Ϊ������Ϊԭ�������ֵ
	currentPoint[0] = currentPoint[0] - adjustPoint[0][0];
	currentPoint[1] = adjustPoint[0][1] - currentPoint[1];
	
	//������ʾ�ڴ�����Ļ�ϵ�����
	currentPoint[0] = (int)(169+( (double)94*(double)currentPoint[0] ) / (double)adjustPointDis);
	currentPoint[1] = (int)(102-( (double)94*(double)currentPoint[1] ) / (double)adjustPointDis);
	
	tempSlightPoint[0] = currentPoint[0];
	tempSlightPoint[1] = currentPoint[1];
	
	//����
		printf("page improve1");
		stop();
		printf("page improve1");
		stop();
	
	//�ڴ���������ʾ���
	printf("pic %d,%d,9", tempSlightPoint[0], tempSlightPoint[1]); stop();
	printf("pic %d,%d,9", tempSlightPoint[0], tempSlightPoint[1]); stop();
	printf("pic %d,%d,9", tempSlightPoint[0], tempSlightPoint[1]); stop();
	
	uartReceiveData = 0;
}

//�����1��˸hongdian
void slightPoint(u8 dat)
{
	if (dat==1)
	{
		printf("page improve1");
		stop();
		printf("page improve1");
		stop();
		printf("page improve1");
		stop();
	}
	else if (dat==2)
	{
		//�ڴ���������ʾ���
		printf("pic %d,%d,9", currentPoint[0], currentPoint[1]); stop();
		printf("pic %d,%d,9", currentPoint[0], currentPoint[1]); stop();
		printf("pic %d,%d,9", currentPoint[0], currentPoint[1]); stop();
	}
	
	uartReceiveData = 0;
}

//������3���������
void base3Fun(void)
{
	double currentPointDis = 0;  //��ǰ������ĵ�ľ���
	double ratioOfCurrAdj = 0;   //���ĵ�͵�ǰ��ľ��� �����ĵ�ͱ�Ե�ĵľ���
	int currentRing = 0;         //��ǰ�Ļ���
	char direction[10][8] = {"����", "����", "����", "����", "����", "����", "����", "����", "����", "�Ѱ�"};
	u8 dirDat = 0;  //9�����������
	
	//��ȡ��ǰ��������
	getXY(&currentPoint[0], &currentPoint[1]); 
	
	//����Ļ����ת��Ϊ������Ϊԭ�������ֵ
	currentPoint[0] = currentPoint[0] - adjustPoint[0][0];
	currentPoint[1] = adjustPoint[0][1] - currentPoint[1];
	
	//��������ͷ���񵽵����ĵ�ͱ�Ե������Ļ�ϵľ���
	adjustPointDis = sqrt( (double)adjustPoint[1][0]*(double)adjustPoint[1][0] + (double)adjustPoint[1][1]*(double)adjustPoint[1][1]);
	
	//�������ĵ�͵�ǰ��ľ���
	currentPointDis = sqrt( (double)currentPoint[0]*(double)currentPoint[0] + (double)currentPoint[1]*(double)currentPoint[1]);
	
	//���㵱ǰ��Ļ���
	ratioOfCurrAdj = currentPointDis/adjustPointDis;
	
	if ( ratioOfCurrAdj<=0.143 )
	{
		currentRing = 10;
	}
	else if ( ratioOfCurrAdj>0.143 && ratioOfCurrAdj<=0.286 )
	{
		currentRing = 9;
	}
	else if ( ratioOfCurrAdj>0.286 && ratioOfCurrAdj<=0.429 )
	{
		currentRing = 8;
	}
	else if ( ratioOfCurrAdj>0.429 && ratioOfCurrAdj<=0.572 )
	{
		currentRing = 7;
	}
	else if ( ratioOfCurrAdj>0.572 && ratioOfCurrAdj<=0.715 )
	{
		currentRing = 6;
	}
	else if ( ratioOfCurrAdj>0.715 && ratioOfCurrAdj<=0.857 )
	{
		currentRing = 5;
	}
	else if ( ratioOfCurrAdj>0.857 && ratioOfCurrAdj<=1 )
	{
		currentRing = 4;
	}
	else   //�Ѱ�
	{
		currentRing = 0;
		dirDat = 9;
	}
	
	//���û���ѰУ��жϷ�λ
	if ( currentRing!=0 )
	{
			if ( fabs(currentPoint[0])<5 && fabs(currentPoint[1])<5 )
			{
				dirDat = 0;  //���ĵ�
			}
			else if ( fabs(currentPoint[0])<5 && currentPoint[1]>0 )
			{
				dirDat = 1;  //����
			}
			else if ( fabs(currentPoint[0])<5 && currentPoint[1]<0 )
			{
				dirDat = 2;  //����
			}
			else if ( fabs(currentPoint[1])<7 && currentPoint[0]>0 )
			{
				dirDat = 4;  //����
			}
			else if ( fabs(currentPoint[1])<7 && currentPoint[0]<0 )
			{
				dirDat = 3;  //����
			}
			else if ( currentPoint[0]>0 && currentPoint[1]>0 )
			{
				dirDat = 7;  //����
			}
			else if ( currentPoint[0]<0 && currentPoint[1]>0 )
			{
				dirDat = 5;  //����
			}
			else if ( currentPoint[0]<0 && currentPoint[1]<0 )
			{
				dirDat = 6;  //����
			}
			else if ( currentPoint[0]>0 && currentPoint[1]<0 )
			{
				dirDat = 8;  //����
			}
	}
	printf("t2.txt=\"%d\"", currentRing); stop();
	printf("t2.txt=\"%d\"", currentRing); stop();
	printf("t2.txt=\"%d\"", currentRing); stop();
	printf("t4.txt=\"%s\"", direction[dirDat]); stop();
	printf("t4.txt=\"%s\"", direction[dirDat]); stop();
	printf("t4.txt=\"%s\"", direction[dirDat]); stop();
	
	uartReceiveData = 0; 
}

//�е�����У׼��ť����
void centerAdjustFun(void)
{
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		LED1 = !LED1; 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop(); 
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop(); 
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop(); 
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop();
		uartReceiveData = 0; 
}

//��Ե����У׼��ť����
void borderAdjustFun(void)
{
		//�õ��������Ļ�ϵ�����
		getXY(&adjustPoint[1][0], &adjustPoint[1][1]); 
	
		//����Ļ����ת��Ϊ������Ϊԭ�������ֵ
		adjustPoint[1][0] = adjustPoint[1][0] - adjustPoint[0][0];
	  adjustPoint[1][1] = adjustPoint[0][1] - adjustPoint[1][1];
		
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		uartReceiveData = 0;
	
}

//���ʹ���ָ��ֹͣλ
void stop(void)		       
{		 
	 u8 i;
	 printf("9");
	 for(i=0;i<3;i++)
	 {
			USART_SendData(USART1,0xff);  //����һ���ֽ�
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ����ͽ���
	 } 
} 
