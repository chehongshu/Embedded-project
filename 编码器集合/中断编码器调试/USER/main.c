#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "encoder.h"

volatile s16 encoder_num;

 int main(void)
 { 

			delay_init();	    	 //��ʱ������ʼ��	  
			//uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
			//LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
			//LCD_Init();
			//	POINT_COLOR=RED; 
			 Encoder_Init();
	 
			while(1) 
			{		 
				
			      encoder_num = update_angle();
			     	//	LCD_ShowNum(20,100,encoder_num,3,16);						//��ʾһ������
			} 
			
}
