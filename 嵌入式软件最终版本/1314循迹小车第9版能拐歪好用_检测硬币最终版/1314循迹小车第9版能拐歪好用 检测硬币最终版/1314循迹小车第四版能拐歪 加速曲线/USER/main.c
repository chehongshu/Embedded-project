#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "JLX_12864.h"
#include "pwm.h"
#include "myiic.h" 
#include "LDC1314.h"
#include "steppermotor.h"
#include "function.h"
#include "key.h"
#include "exti.h"

//  1 ��ʼֵ  ֮���ȥ  ��ʼֵ
//  2  ����    �ᵽ     ����ȥ

char a[10]="now time"; 
char b[10]="distance";
char c[10]="speed";

u32 second;   //��
double distance;  // �ߵľ���
double speed;    //  �ߵ��ٶ�

int zhongduanbiaozhi;

u32  pulseamount_Left ;   //�����������Ŀ
u32  pulseamount_Right ;  //�����������Ŀ

s32 passageway1;
s32 passageway2;
s32 passageway3;
s32 passageway4;

s32 passageway1_init;
s32 passageway2_init;
s32 passageway3_init;
s32 passageway4_init;

s32 different_value1;//  ��ͨ��   ��   ��ͨ����  ��ֵ

s32 different_value2;  //  ��ͨ��  �� һͨ���� ��ֵ

s32 buzhi1;
s32 buzhi2;

u16 duty_left=2000;

u16 duty_right=2000;

u16 set_duty_left=1000;
u16 set_duty_right=1000;

int pwm_left;
int pwm_right;


extern int i;

int flag=0;


int  moshi=1;


int main(void)
{	
    /***************************��ʼ������*****************************************/
    
    
	delay_init();	    	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // �����ж����ȼ�����2
	LED_Init();		  	        //��ʼ����LED���ӵ�Ӳ���ӿ�
    
    
    KEY_Init(); 
                              EXTIX_Init();
    buzzer_Init();             //   ������  ��ʼ��  
  
     /// pwm��ʼ��
    TIM4_PWM_Init(duty_left,36);    //���յ�1k         �� 2000��1000   1ms  ��һ���ж� ��50   ��20��  ֹͣ 
    TIM2_PWM_Init(duty_right,36 );    //���յ�1k    duty_right
         
    TIM5_Int_Init(1000,72);    //1ms  ɨ��һ��     ��������
     //  12864  
    LCD12864_init();
     //  LDC1314  ��
    IIC_Init();
    LDC1314_MultiInit();
    steppermotor_init();
    
     stop_motor();//    ��ֹͣ  
     
//     TIM_SetCompare1(TIM4,0); //       ����
//     TIM_SetCompare2(TIM2,0);  //      ����
    
      delay_ms(1500) ;  //   ��ʱ
     
   
           ///��ʱ���ж�
           
	TIM3_Int_Init(10000,7200); //1s ��һ���ж�
    
   
    
   
    
    
         passageway2_init=LDC_Read_Reg(0X02);    // ��ͨ�� ����    
         passageway3_init=LDC_Read_Reg(0X04);    //��ͨ�� ����
         passageway1_init=LDC_Read_Reg(0X00);    // һͨ�� ����    
         passageway4_init=LDC_Read_Reg(0X06);    //��ͨ�� ����
         buzhi1 = passageway3_init  - passageway2_init;   //
         buzhi2 =  passageway4_init - passageway1_init;    //
   	while(1)
{  
	
	/*
         J12864_led_double1(1,20,passageway1,1); 
         J12864_led_double1(2,20,passageway2,1); 
         
         J12864_led_double1(1,60,passageway3,1); 
         J12864_led_double1(2,60,passageway4,1); 
        
        
        
        
        
                                    passageway2=LDC_Read_Reg(0X02);    // ��ͨ�� ����    
                                    passageway3=LDC_Read_Reg(0X04);    //��ͨ�� ����
                                    
                                    different_value1= passageway3-passageway2-buzhi1 ;
                                    
                                    passageway1=LDC_Read_Reg(0X00);    // һͨ�� ����    
                                    passageway4=LDC_Read_Reg(0X06);    //��ͨ�� ����
                                    
                                    different_value2= passageway4-passageway1-buzhi2;
        
      
        start_motor();          //  ��ʼ��    
                  if(flag==0)
                  {
								
                   pwm_left=500;   
                   pwm_right=500;   
                TIM_SetCompare1(TIM4, pwm_left);  //       ����
                TIM_SetCompare2(TIM2, pwm_right);  //      ����
                   
                  }
         Display();
        
        
         J12864_led_double1(6,20,different_value1,1);  //   �м��
         J12864_led_double1(7,20,different_value2,1);   //  ���ߵ�
                  
                  
              ///////        �����ʱ��
         distance= Through_distance( pulseamount_Left,pulseamount_Right ); 
      
          speed=gain_speed( second , distance ) ;
                  
           
         GPIO_ResetBits(GPIOC,GPIO_Pin_12);	
            LED1=0;       
           

          if (moshi==1)   
          { 
              
              search_path1( passageway1, passageway2, passageway3, passageway4);
                

              if(second>=33)
              {
                  stop_motor();
                  
                  LED1=1;
                GPIO_SetBits(GPIOC,GPIO_Pin_12);
                    pwm_left=0;   
                   pwm_right=0;  
                TIM_SetCompare1(TIM4,pwm_left);  //       ����
                TIM_SetCompare2(TIM2,pwm_right);  //      ����   
                     flag   =  1;                   
              }                  

              
           }                  
          if(moshi==2)
            search_path2( passageway1, passageway2, passageway3, passageway4);    
             */  
	}
}

