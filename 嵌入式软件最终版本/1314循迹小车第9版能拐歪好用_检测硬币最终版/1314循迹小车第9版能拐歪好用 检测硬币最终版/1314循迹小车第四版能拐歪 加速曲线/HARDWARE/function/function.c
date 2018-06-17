#include "function.h"
#include "JLX_12864.h"
#include "key.h"
#include "steppermotor.h"
#include "LDC1314.h"
#include "math.h"
#include "led.h"
#include "delay.h"

extern char a[10]; 
extern char b[10];
extern char c[10];

extern u32 second;   //��
extern double distance;  // �ߵľ���
extern double speed;    //  �ߵ��ٶ�


extern u32 passageway1;
extern u32 passageway2;
extern u32 passageway3;
extern u32 passageway4;

extern s32 passageway1_init;
extern s32 passageway2_init;
extern s32 passageway3_init;
extern s32 passageway4_init;


extern u16 set_duty_left;
extern u16 set_duty_right;

 
extern u16 duty_left;
extern u16 duty_right;

extern s32 buzhi1;
extern s32 buzhi2;

extern  int flag;


/*
*********************************************************************************************************
*	�� �� ��:    void Display()
*	����˵��:       ��Ļ��ʾ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Display(void)
{
    
         J12864_led_ASCALLS(3,20,a);
         J12864_led_int(3,70,second);  
         J12864_led_ASCALLS(4,20,b);
         J12864_led_double1(4,70,distance,1); 
         J12864_led_ASCALLS(5,20,c);
         J12864_led_double1(5,70,speed,1); 
         
    
}
/*
*********************************************************************************************************
*	�� �� ��:           Through_distance( int pulseamount_Left, int pulseamount_Right)
*	����˵��:               �����  �ߵ���Ӧ�ľ���
*	��    �Σ�      int pulseamount_Left, int pulseamount_Right   
*	�� �� ֵ:                      ����
*********************************************************************************************************
*/
double   Through_distance( int pulseamount_Left, int pulseamount_Right) 
{
    double  Distance_Left;
    double  Distance_Right;
    double  Distance;
    
    
    Distance_Left  =  ((double)pulseamount_Left*(1.8)*21.5)/(8*360)  ;      //   16 ϸ��
    Distance_Right =  ((double)pulseamount_Right*(1.8)*21.5)/(8*360) ;
    
    Distance = ( Distance_Left + Distance_Right )/2;
    
    return Distance;
}
/*
*********************************************************************************************************
*	�� �� ��:              gain_speed( int second,double distance )   
*	����˵��:                   ���  С���� �ٶ�
*	��    �Σ�                 second   distance
*	�� �� ֵ:                       speed
*********************************************************************************************************
*/
double gain_speed( int second,double distance )    
{
       double speed ;
       speed= distance/second;
       return speed;    
}
 /*
*********************************************************************************************************
*	�� �� ��:              gain_speed( int second,double distance )   
*	����˵��:                   ���  С���� �ٶ�
*	��    �Σ�                 second   distance
*	�� �� ֵ:                       speed
*********************************************************************************************************
*/
void  sound_light_alarm(int coin)  
{
    if(coin==1)
           GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����      ��������
    if(coin==0)
          GPIO_ResetBits(GPIOB,GPIO_Pin_12);					 //PB.12 �����      ����������
     
}

  /*
*********************************************************************************************************
*	�� �� ��:            search_path(int sign_left1,int sign_left2,int sign_right1,int sign_right2)
*	����˵��:                  Ѱ��
*	��    �Σ�               
*	�� �� ֵ:          
*********************************************************************************************************
*/
void  search_path1(int sign_left2,int sign_left1,int sign_right1,int sign_right2)
{
         
    
      if(((sign_right1-sign_left1-buzhi1) > 2)&& ((sign_right1-sign_left1-buzhi1)< (-2)))
      {   
             set_duty_right = 1000;
             
             set_duty_left  = 1000;
             
          TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
     
          TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���       ����
          
      }          
      
      
      
      
      
      
      
      
   
         if( ((sign_right1-sign_left1-buzhi1)<2)&&((sign_right1-sign_left1-buzhi1)>(-2))  )     //   ()
         {
             set_duty_right = 1000;
             
             set_duty_left  = 1000;
             
          TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
     
          TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���       ����      
             
             flag=0;
                
             
         }                                          
               if((sign_right1-sign_left1-buzhi1) >13)   //   ���� 
              {        
              }
              else
              {
                             if(((sign_right1-sign_left1-buzhi1) >2 )&& (sign_right1-sign_left1-buzhi1) < 13)           //   1600     600         
                              {
                    //             set_duty_right = 5000;
                                 
                                 set_duty_left  = 800;   
                                  
                                   
                     
                                 TIM_SetCompare2(TIM2,0); 
                                  
                                      flag=1;
                                  
                              
                              TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
                         
                              TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���       ����
                                
                              }
                }               
         if((sign_right1-sign_left1-buzhi1) <-13)                //����
              {    
//                  LED1=1;
//               GPIO_SetBits(GPIOC,GPIO_Pin_12);	
//                  delay_ms(100);
              }
            else
            {              
                                        if( ( (sign_right1-sign_left1-buzhi1)< -2)&&((sign_right1-sign_left1-buzhi1) > -13 ))        //  
                                 {   
                                     
                               set_duty_right = 800;
                                     
                        //             set_duty_left  = 5000;

                                        
                                     
                                     TIM_SetCompare1(TIM4,0);      
                                     
                                     TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
                               
                                     TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���      ����
                                   
                                     flag=1;
                                     
                                      
                                  }
             }                    
         
    
//         if((abs( sign_right2-passageway4_init))>1)      //   (sign_right2-sign_left2-buzhi2) < 0       �ҹ�
//         {
//                
//             
//             
//             set_duty_left  = 600;

//               TIM_SetAutoreload(TIM2,duty_right);   //�����Ҫ    400          ����                300   12000
////             
//               TIM_SetAutoreload(TIM4,duty_left);   //    duty_left      1300          ����
//             
//           TIM_SetCompare2(TIM2,0);  //      ����
//            
//             
//         }                  

//         
//         if((abs( sign_left2-passageway1_init))>1)           //    ���                                                       //     (sign_right2-sign_left2-buzhi2)
//         {                                                        


//           TIM_SetCompare1(TIM4,0);  //      ����     
//              set_duty_right = 600;
//                                
//             TIM_SetAutoreload(TIM4,duty_left);    //         400            ����
////                               ��
//             TIM_SetAutoreload(TIM2,duty_right);    //     duty_right    1300           ����9
//           
//             
//         }
         
}       
void  search_path2(int sign_left2,int sign_left1,int sign_right1,int sign_right2)
{
         
    
      if(((sign_right1-sign_left1-buzhi1) > 2)&& ((sign_right1-sign_left1-buzhi1)< (-2)))
      {   
             set_duty_right = 1000;
             
             set_duty_left  = 1000;
             
          TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
     
          TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���       ����
          
      }          
      
      
      
      
      
      
      
      
      
    if( ((sign_right1-sign_left1-buzhi1)<2)&&((sign_right1-sign_left1-buzhi1)>(-2))  )     //   ()
         {
             set_duty_right = 1000;
             
             set_duty_left  = 1000;
             
          TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
     
          TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���       ����      
             
             flag=0;
                
             
         }                                          
               if((sign_right1-sign_left1-buzhi1) >15)   //   ���� 
              {         LED1=1;
                    GPIO_SetBits(GPIOC,GPIO_Pin_12);	
                  delay_ms(100);
              }
              else
              {
                             if(((sign_right1-sign_left1-buzhi1) >2 )&& (sign_right1-sign_left1-buzhi1) < 15)           //   1600     600         
                              {
                    //             set_duty_right = 5000;
                                 
                                    set_duty_left  = 900;   
                                  
                                   
                     
                                 TIM_SetCompare2(TIM2,0);

                                                             
                                  
                                      flag=1;
                                  
                              
                              TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
                         
                              TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���       ����
                                   delay_ms(300);    
                              }
                }               
         if((sign_right1-sign_left1-buzhi1) <-13)                //����
              {    
                  LED1=1;
               GPIO_SetBits(GPIOC,GPIO_Pin_12);	
                  delay_ms(100);
              }
            else
            {              
                                        if( ( (sign_right1-sign_left1-buzhi1)< -2)&&((sign_right1-sign_left1-buzhi1) > -13 ))        //  
                                     {   
                                     
                                    set_duty_right = 900;
                                     
                        //             set_duty_left  = 5000;

                                        
                                     
                                     TIM_SetCompare1(TIM4,0);      
                                     
                                     TIM_SetAutoreload(TIM4,duty_left);  //   ֱ�Ӹ����ں���       ����
                               
                                     TIM_SetAutoreload(TIM2,duty_right);  //   ֱ�Ӹ����ں���      ����
                                   
                                     flag=1;
                                         
                                           delay_ms(300);   
                                     
                                      
                                     }
             }                    
         
    
         if((abs( sign_right2-passageway4_init))>1)      //   (sign_right2-sign_left2-buzhi2) < 0       �ҹ�
         {
                
             
             
             set_duty_left  = 600;

               TIM_SetAutoreload(TIM2,duty_right);   //�����Ҫ    400          ����                300   12000
//             
               TIM_SetAutoreload(TIM4,duty_left);   //    duty_left      1300          ����
             
           TIM_SetCompare2(TIM2,0);  //      ����
            
             
         }                  

         
         if((abs( sign_left2-passageway1_init))>1)           //    ���                                                       //     (sign_right2-sign_left2-buzhi2)
         {                                                        


           TIM_SetCompare1(TIM4,0);  //      ����     
              set_duty_right = 600;
                                
             TIM_SetAutoreload(TIM4,duty_left);    //         400            ����
//                               ��
             TIM_SetAutoreload(TIM2,duty_right);    //     duty_right    1300           ����9
           
             
         }
         
}                  
  /*
*********************************************************************************************************
*	�� �� ��:      gain_sign()     
*	����˵��:      �õ�  �ĸ�ͨ��ֵ           
*	��    �Σ�               
*	�� �� ֵ:          
*********************************************************************************************************
*/
void gain_sign()
{
       passageway1= LDC_Read_Reg(0X00);
       passageway2=LDC_Read_Reg(0X02);      
       passageway3=LDC_Read_Reg(0X04);
       passageway4=LDC_Read_Reg(0X06); 
}

