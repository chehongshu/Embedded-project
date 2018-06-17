#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "string.h"
#include "ov7670.h"
#include "timer.h"
#include "exti.h"
#include "usmart.h"
#include "sysvalue.h"
#include "screen.h"
#include "moveMotor.h"


/***********************************************
*����ͷʹ�õı���
************************************************/
extern u8 ov_sta;	//��exit.c�� �涨��
extern u8 ov_frame;	//��timer.c���涨��		 

/**********************************************
*main�ж���ĺ���
***********************************************/
void getXY(int * x, int * y);            //�õ�������XY����

/**************************************************
*�Լ�����ı���
**************************************************/
//���ڷ��ص�����
int uartReceiveData = 0;
//����У׼�����ĵ�ͱ�Ե��
int adjustPoint[2][2];

int temp[2];


//������
 int main(void)
 {
	/*
	 ����ͷʹ���Լ�ϵͳ��ʼ��
	 */
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ 115200
 	usmart_dev.init(72);		//��ʼ��USMART		
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	motorInit();         //�����ʼ��
	TIM2_Int_Init(150, 7200);      //���մ��������ص�����
	TIM3_Int_Init(150, 7200);
 	POINT_COLOR=RED;			//��������Ϊ��ɫ 
	while(OV7670_Init())//��ʼ��OV7670
	{
		LCD_ShowString(30,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	  LCD_Fill(30,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(30,230,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   
	TIM6_Int_Init(10000,7199);			//10Khz����Ƶ��,1�����ж�									  
	EXTI8_Init();						//ʹ�ܶ�ʱ������
	OV7670_Window_Set(12,176,240,320);	//���ô���	  
  OV7670_CS=0;					
	LCD_Clear(BLACK);
	
	//��������Դ
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	
	/*
		�����bug  �����
	*/
	printf("page main");
	stop();
	printf("page main");
	stop();
	printf("page main");
	stop();

	
	/*
		������ģ��
	*/
 	while(1)
	{	
		
		switch (uartReceiveData)
		{
			case REC_ADJUST1: centerAdjustFun(); break;
			case REC_ADJUST2: borderAdjustFun(); break;
			case REC_RECDATA: base3Fun(); break;
			case REC_SHOW: improve1Fun(); break;
			case REC_SLIGHT1:break;
			case REC_SLIGHT2:break;
			case REC_OPENLIGHT: GPIO_SetBits(GPIOA, GPIO_Pin_7); break;
			case REC_CLOSELIGHT: GPIO_ResetBits(GPIOA, GPIO_Pin_7); break;
			case REC_GETTENRING: improve2Fun(); break;
			case REC_GETPOINT: getCurrentPoint(); break;
			case REC_GETFOURRING: improve3Fun(4); break;
			case REC_GETFIVERING: improve3Fun(5); break;
			case REC_GETSIXRING: improve3Fun(6); break;
			case REC_GETSEVENRING: improve3Fun(7); break;
			case REC_GETEIGHTRING: improve3Fun(8); break;
			case REC_GETNINERING: improve3Fun(9); break;
			case REC_GETTENRING2: improve2Fun(); break;
			default: break;
		}
	}	   
}


//�õ�������XY����
void getXY(int * x, int * y)
{
	u16 tempXY[2][2] = {0};   //������ʱ��Ų��񵽵ĺ���x y���� tempXY[0][0] tempXY[1][0]���xy�������Сֵ tempXY[0][1] tempXY[1][1]���xy��������ֵ
	u8 flag = 1;        //���ڱ��ÿ�ε��øĺ���ʱ�Ƿ��ǵ�һ��λtempXY��ֵ
	u32 j, i;
 	u16 color;	 
	if(ov_sta)//��֡�жϸ��£�
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//����ʾ�������õ���Ļ����
		else if(lcddev.id==0X5510||lcddev.id==0X5310)LCD_Set_Window((lcddev.width-320)/2,(lcddev.height-240)/2,320,240);//����ʾ�������õ���Ļ����
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK_H;
		for(i=0;i<240;i++)
		{
			for (j=0; j<320; j++)
			{
				OV7670_RCK_L;
				color=GPIOC->IDR&0XFF;	//������
				OV7670_RCK_H; 
				color<<=8;  
				OV7670_RCK_L;
				color|=GPIOC->IDR&0XFF;	//������
				OV7670_RCK_H;
				
				//����Ƿ��Ǻ��
				if ( color>RED-2500 && color<RED+2500 )
				{
					color = WHITE; //�Ǻ�����ʾ��ɫ
					
					//��ȡ�������ĸ��������ֵ
					if ( flag )  //��һ�μ�⵽�׵�
					{
						tempXY[0][0] = i;       
						tempXY[0][1] = i;
						tempXY[1][0] = j;
						tempXY[1][1] = j;
						flag = 0;
					}
					else 
					{
						//��ȡx�������ֵ
						if ( i>tempXY[0][1] )
						{
							tempXY[0][1] = i;
						}
						
						//��ȡy�������ֵ
						if ( j<tempXY[1][0])
						{
							tempXY[1][0] = j;
						}
						else if ( j>tempXY[1][1] )
						{
							tempXY[1][1] = j;
						}
					}
				}
				else 
				{
					color = BLACK; //���Ǻ�����ʾ��ɫ
				}
					
				LCD->LCD_RAM=color;    
			}
		}   							  
 		ov_sta=0;					//����֡�жϱ��
		ov_frame++; 
		LCD_Scan_Dir(U2D_L2R);	//�ָ�Ĭ��ɨ�跽�� L2R_U2 DDFT_SCAN_DIR
	} 
	
	//����������Ļ�ϵ���������
	(*x) = (tempXY[0][0] + tempXY[0][1])/2;
	(*y) = (tempXY[1][0] + tempXY[1][1])/2;
}	   











