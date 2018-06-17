#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "exti.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "PID.h"
#include "xianshi.h"



int speed=10;
int t_angle=45;
int distance=10;
int page=1;
int arrow=1;
    u8 t=0; 
    u8  key=0;
    u8 lcd_id[12];			//���LCD ID�ַ���

	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;     //������ԭʼ���� 
    short temp;    //�¶�
     
     
     float setroll;             //���õĽǶ�
     double pwmval=0;                  //ÿ�� pid������ĽǶ�
     static double  npwmval=0; //�ۼӵĽǶ�
         //���õ�  roll�Ƕ�   
      int i;
			double DIP=0.0;
void INIT()
{    	
	
	delay_init();	    //��ʱ������ʼ��	 
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    
    IncPID_Init();  //pid��ʼ�� 
    
    usart_init(9600);	 	//���ڳ�ʼ��Ϊ9600  
    
	MPU_Init();   //   �����Ѿ�����  mpu��iic����    
   
  
	 LED_Init();			     //LED�˿ڳ�ʼ��   ������pwm����Ӧ����pwm��ʼ����ǰ��
	
     LCD_Init();
    

      EXTIX_Init();        //�����жϳ�ʼ��

   TIM1_PWM_Init(999,72); //1khz       ��72M/72���ķ�֮һʱ�����999+1λһ���ڵ�ʱ�䷴��������Ƶ��
      POINT_COLOR=RED;

		
}

	
 	
 	
	
 int main(void)
 {	 
     

	 INIT();
	
     sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
   
    while(mpu_dmp_init())
 	{
		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}    


  	while(1) 
	{		 
					if(Usart_State&0x02)
		 {   UsartChangePID(USART_RX_BUF);
			 Usart_State|=0x08;
			 Usart_State&=~0x02;
//			 DIP=sptr->Proportion;
			 USART_Sentstring(USART1,"Proportion: ");
			 USART_Send_NUM(USART1,sptr->Proportion,3);
			 USART_Sentstring(USART1,"   ");
             USART_Sentstring(USART1,"Integral : ");
			 USART_Send_NUM(USART1,sptr->Integral,3);
			 USART_Sentstring(USART1,"   ");
             USART_Sentstring(USART1,"Derivative : ");
			 USART_Send_NUM(USART1,sptr->Derivative,3);
			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"Kp_G : ");
//			 USART_Send_NUM(USART1,Kp_G,3);
//			 USART_Sentstring(USART1,"   ");
//             USART_Sentstring(USART1,"Ki_G : ");
//			 USART_Send_NUM(USART1,Ki_G,3);
//			 USART_Sentstring(USART1,"   ");
//             USART_Sentstring(USART1,"Kd_G : ");
//			 USART_Send_NUM(USART1,Kd_G,3);
//			 fanhang(USART1);
//			 USART_Sentstring(USART1,"Pwm1 : ");
//			 USART_Send_NUM(USART1,Pwm1,3);
//			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"Pwm2 : ");
//			 USART_Send_NUM(USART1,Pwm2,3);
//			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"QbT : ");
//			 USART_Send_NUM(USART1,Qibai_T,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"TDt : ");
//			 USART_Send_NUM(USART1,TDt,3);
//			 USART_Sentstring(USART1,"   ");
//			 fanhang(USART1);

//			 USART_Sentstring(USART1,"SAL : ");
//			 USART_Send_NUM(USART1,SAL,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"SAR : ");
//			 USART_Send_NUM(USART1,SAR,3);
//			 USART_Sentstring(USART1,"   ");
//			 USART_Sentstring(USART1,"DAR : ");
//			 USART_Send_NUM(USART1,DAR,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"DAL : ");
//			 USART_Send_NUM(USART1,DAL,3);
//			 USART_Sentstring(USART1,"   ");
			 fanhang(USART1);
			 

			 
		 }

//        xianshi((long int)npwmval);
		 
		 if(page==1)
		 {
			 mpu_dmp_get_data(&pitch,&roll,&yaw);   //���  �Ƕ�  
			 xianshi(0);
		 
		 }
		 if(page==3||page==4)
		 {
			
		 
    
             
            mpu_dmp_get_data(&pitch,&roll,&yaw);   //��õ�  �Ƕ�
        setroll=(float)t_angle;                 //��ʾ��  ��  �㷨��  ����   �ı��Ŀ��Ƕ�
//               xianshi((long int)npwmval);
          
       
//         if((setroll-(-roll))>=9)
//         { TIM_SetCompare1(TIM1,700);  //Ϊ�����ٿ�һЩ��  �������Լ��������ʱ��   ���������ܻ�ܲ��ȶ�
//           xianshi(700);
//         }
//        else
//           {
            
           pwmval=IncPID_Calc(setroll,(-roll)); //  pid�ñ���
         
           npwmval=npwmval+pwmval;        //�ۼ�      
         if(t_angle<50)
         { 		
                if(npwmval>=800)
                npwmval=800;

            if(npwmval<=0)
                  npwmval=0;
   TIM_SetCompare1(TIM1, (long int)npwmval) ;				//PB5 ���pwm      ���100ռ�ձ� �����60��
		}						
         else
         {
                if(npwmval>=999)
                npwmval=999;

            if(npwmval<=0)
                  npwmval=0;
   TIM_SetCompare1(TIM1, (long int)npwmval) ;
         }
      
                     xianshi((long int)npwmval);                
       
      
      //  }
      }          
		 	 if(page==2)
		 {
			 mpu_dmp_get_data(&pitch,&roll,&yaw);   //���  �Ƕ�
			 switch(speed)
			 {
			   case 0:
					 	TIM_SetCompare1(TIM1, 0) ; 
				 xianshi(0); break;
				 case 1 : 
				 	TIM_SetCompare1(TIM1, 100) ; 
				 xianshi(100); break;
				 case 2 : 
				 	TIM_SetCompare1(TIM1, 200) ;
				 xianshi(200);  break;
				 case 3 : 
				 	TIM_SetCompare1(TIM1, 300) ; 
				 xianshi(300); break;
				 case 4 : 
				 	TIM_SetCompare1(TIM1, 400) ; 
				 xianshi(400); break;
				 case 5 : 
				 	TIM_SetCompare1(TIM1, 500) ;
				 xianshi(500);  break;
				 case 6 : 
				 	TIM_SetCompare1(TIM1, 600) ; 
				 xianshi(600); break;
				 case 7 : 
				 	TIM_SetCompare1(TIM1, 700) ;
				xianshi(700); 	 break;
				 case 8 : 
				 	TIM_SetCompare1(TIM1, 800) ; 
				xianshi(800); 	break;
				 case 9 : 
				 	TIM_SetCompare1(TIM1, 900) ; 
				xianshi(900); 	break;
				 case 10 : 
				 	TIM_SetCompare1(TIM1, 999) ; 
				xianshi(1000); break;
		 }

        }  
			   		 
                            

	}

	} 

