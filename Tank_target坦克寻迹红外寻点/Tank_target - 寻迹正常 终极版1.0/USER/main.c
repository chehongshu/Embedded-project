# include "stm32f10x.h"
# include "delay.h"
# include "sys.h"
# include "pwm.h"
//# include "usart.h"
# include "steppermotor.h"
# include "led.h"
# include "timer.h"
# include "ST_drive.h"

 int main(void)
 {	
	 delay_init();	    	         //��ʱ������ʼ��	 
	 
	 steppermotor_init();          //���������ʼ��
	 
	 TIM3CH1_PWM_Init(1000, 25);   // 72000/(899+1) = 80KHz;  ����
	 TIM1CH4_PWM_Init(1000, 25);   //����
	 TIM7_Int_Init(10, 7200-1);    //����
	 TIM5_Int_Init(10, 7200-1);    //Ѱ��
	 ST_drive_Init();              //st188��ʼ��        
	 
	 start_motor();                //С����ʼ��
	 buzzer_Init();                //��������ʼ��
   LED_Init();                   //LED��ʼ��
   TIM6_Int_Init(5000, 7200);
	 LED0 = 0;
	 while(1)
	 {
		 //Warning();
	 }
		
 }
