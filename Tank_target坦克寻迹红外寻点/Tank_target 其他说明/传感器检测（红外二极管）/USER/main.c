#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "blue_tooth.h"
#include "adc.h"
#include "Under_SMotor.h"
//   ���� �������ͽ��� �� ���ӳ���
	 double  zuo2,you2,zhong;
int main(void)
 {	
		u8 t;
		u8 len;	
		u16 times=0;        
    int i=0;

 
		delay_init();	    	 //��ʱ������ʼ��	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
		usart2_init(9600);	 //���ڳ�ʼ��Ϊ9600
     Adc_Init();
     Under_SMotor_init();
	   TIM4_Init(999,35);//2k
	   delay_ms(1000);
  	    delay_ms(1000);
	    delay_ms(1000);
	while(1)
	{
		
		 Under_ENA_NOT;
			zuo2=(double)Get_Adc_Average(10,10)*(3.3/4096);
			you2=(double)Get_Adc_Average(11,10)*(3.3/4096);
			zhong=(double)Get_Adc_Average(14,10)*(3.3/4096);
		   if(zuo2>you2)
			 {
			//	 Under_DIR_Left;
			Under_DIR_Right;
				 Under_ENA;
			 }else if(zuo2<you2)
			 {
	//			 Under_DIR_Right;
				 Under_DIR_Left;
				 Under_ENA;
			 }
			 if(zhong>2.45)
			 {
				 Under_ENA_NOT;
			 }
		
		
		    Blue_tooth_String(USART2,"����Ĵ����� ");
	    	Blue_tooth_number(USART2,zuo2);
				Blue_tooth_String(USART2,"�ұߵĴ����� ");
		    Blue_tooth_number(USART2,you2);
      	Blue_tooth_String(USART2,"�м�Ĵ����� ");
				Blue_tooth_number(USART2,		zhong);
		
		
		
    }
}
