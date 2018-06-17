# include "sys.h"
# include "delay.h"
# include "usart.h"
# include "key.h"
# include "led.h"
# include "pwm.h"
# include "timer.h"
# include "beep.h"
# include "sysvalue.h"
# include "screen.h"
# include "12864.h"
# include "pid.h"
# include "mpu6050.h"
# include "mpuiic.h"
# include "usmart.h"
# include "motor_control.h"

//��ʼ��ϵͳ״̬Ϊ�˵�ѡ��״̬
u8 sysCurrentStyle = SYS_MENU;
//�˵���ѡ�еİ���
u8 selectBtn = BASE1;
//���õ�Ŀ��Ƕ�ֵ
u8 targetData1 = 70;
u8 targetData2[2] = {0};
//�趨��ֵʱ�ĸ�ʮ��λѡ��
u8 numLocate = 1;
//ŷ����
float pitch = 0, roll = 0, yaw = 0; 	

//����Ŀ��Ƕ�
double targetData = 60;
extern double currentPwmData;
double kp_temp;
extern u8 USART_RX_BUF[USART_REC_LEN];
int receive; 

void angle_set(u8 sta)
{
	targetData = sta;
}

//���ϵͳ����ĳ�ʼ��
void InitAll()
{

	//��ʱ������ʼ��	 	 
	delay_init();	    
	
  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	uart_init(9600);//===    UART 
	
		//====  1. USMART ��ֲ   2.USMART ��ʼ��    3. ��TIMER��ʱ��(USMART�е�)  4.ע�usmart_config 
		//====   5. ��ʼ��uart 7. д����    8.��������ֱ�ӵ��� 
	
	usmart_dev.init(72);//===    ��Ƭ��   ����Ƶ  72M  
	
	//����ɨ���ʼ��
	KEY_Init();  
	//LED��ʼ��
	LED_Init();
	//��������ʼ��
	BEEP_Init();
	//��ʱ���жϳ�ʼ��
	//TIM2_INT_Init(500, 7200);
	//��ʼ��12864
	LCD_Init();
	//mpu6050��ʼ��
	MPU_Init();

	//���ҵ��pid��ʼ��
	leftPid_Init();
}

 int main(void)
 {
					  //�����ʼ��
					  InitAll();
					  //�ǶȻ�ȡ��ʼ��
						while( mpu_dmp_init() )
						{
							delay_ms(200);
							LED1 = !LED1;
							LED2 = !LED2;
							LED3 = !LED3;
							delay_ms(200);
						} 
						
						//pwm�����ʼ��
						TIM3_PWM_Init(3000 ,0);	//=== 				 3000         0
						TIM4_PWM_Init(3000 ,0);	//=== 				 3000         0
					
						//��ʾ�˵����棬Ĭ��ѡ�л�����1
						//showMenu(selectBtn);
			
						delay_ms(1000);
						delay_ms(1000);
						delay_ms(1000);
				while(1)
				{

											mpu_dmp_get_data(&pitch,&roll,&yaw);   //��ýǶ� 	
											kp_temp = 90-pitch;
											//targetData1 = changeData(targetData1);
//											if ( targetData1>=110 && targetData1<=140 )
//											{
//												pidsetKpid(3010, 8, 3900);
//											}
//											else if ( targetData1<110 && targetData1>=45 )
//											{
//												pidsetKpid(700, 8, 4000);
//											}
																base1Mode();
									
											 /*switch ( sysCurrentStyle )
												{
													case SYS_BASE1_RUNING: 
																//targetData1 = changeData(targetData1);
																base1Mode(); break;
													case SYS_BASE2_RUNING:
																base2Mode(); break;
													default: break;
												}*/
					}
 }
 
 
 
 
