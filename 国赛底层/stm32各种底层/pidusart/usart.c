#include "usart.h"
#include "PID.h"
u8 USART_RX_BUF[USART_REC_LEN]={'\0'};//���ջ���
u16 USART_RX_STA=0;            //����״̬���
/***************************
��������usart_init(u32 bound)
���ܣ���ʼ��UART1
����ֵ����
****************************/
void usart2_init(u32 bound)
{
	  GPIO_InitTypeDef GPIO;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��  zhuying 
 	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	  USART_DeInit(USART2);  //��λ����1
	  
	  GPIO.GPIO_Pin=GPIO_Pin_2;
	  GPIO.GPIO_Mode=GPIO_Mode_AF_PP;//����������� �ο� �����Ĳο��ֲ� V10�� P110 �ı�� 8.1.11 ����� GPIO ���á���
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	  GPIO.GPIO_Pin=GPIO_Pin_3;
	  GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;//�������� �ο� �����Ĳο��ֲ� V10�� P110 �ı�� 8.1.11 ����� GPIO ���á���
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	   //Usart1 NVIC ���� �ж����ȼ� 
      NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//ͨ��
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	  //NVIC_Configuration();
	  
	  //���ò���
	  USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	  USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

      USART_Init(USART2, &USART_InitStructure); //��ʼ������//��ʼ��UART1
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ���ж� �����ж� ���ձ�־RXNE
	  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
}
void usart_init(u32 bound)
{
	  GPIO_InitTypeDef GPIO;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��  zhuying 
 	  USART_DeInit(USART1);  //��λ����1
	  
	  GPIO.GPIO_Pin=GPIO_Pin_9;
	  GPIO.GPIO_Mode=GPIO_Mode_AF_PP;//����������� �ο� �����Ĳο��ֲ� V10�� P110 �ı�� 8.1.11 ����� GPIO ���á���
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	  GPIO.GPIO_Pin=GPIO_Pin_10;
	  GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;//�������� �ο� �����Ĳο��ֲ� V10�� P110 �ı�� 8.1.11 ����� GPIO ���á���
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	   //Usart1 NVIC ���� �ж����ȼ� 
      NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//ͨ��
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	  //NVIC_Configuration();
	  
	  //���ò���
	  USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	  USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

      USART_Init(USART1, &USART_InitStructure); //��ʼ������//��ʼ��UART1
	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ���ж� �����ж� ���ձ�־RXNE
	  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���
void _ttywrch(int ch)  
 { 
     while((USART1->SR&0X40)==0);//ѭ������,ֱ���������    
     USART1->DR = (u8) ch;  
 }
 
struct __FILE 
{ 
	int handle; 

};

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
/************************
���͸���λ���Ĵ��ڹ���
���ֽڽ��� ����Ҫ ��ͷ�ͽ�β���
********************/

/*********************************
��������fanhang()
���ܣ� ʵ�ֻ���
����ֵ����
**********************************/
void fanhang(USART_TypeDef* USART_x)
{
	char *m="\r\n";
	while(*m!='\0')
 {
  USART_SendData(USART_x, *m);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////�ȴ����ͽ�
  m++;
 } 
}
/****************************
��������
���ܣ�
����ֵ��
*****************************/
/****************************
��������void USART_SentChar(USART_TypeDef* USART_x,char data)
���ܣ������ַ�
����ֵ����
*****************************/
void USART_SentChar(USART_TypeDef* USART_x,char data)
{
  USART_SendData(USART_x, data);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////�ȴ����ͽ�
}
/****************************
��������USART_Sentstring(char *str)
���ܣ�����һ���ַ���
����ֵ����
******************************/

void USART_Sentstring(USART_TypeDef* USART_x,char *str)
{
 while(*str!='\0')
 {
  USART_SendData(USART_x, *str);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////�ȴ����ͽ�
  str++;
 }
 //fanhang();//����ʵ������ٺ��ʵĵط����ϻ���
 
}
/****************************
��������void USART_Sentstring_1(char *str,int n)
���ܣ�����һ���ַ���
���� ��������  ר��
����ֵ����
******************************/

void USART_Sentstring_1(USART_TypeDef* USART_x,char *str,int n)
{
	int flag=0;
 while(*str!='\0')
 {
	 if(*str=='.')
	 { flag=1;
	   n+=1;
	 }
    if(flag)
    { if(n==0)
	 break;
	 n--;
     }	  
  USART_SendData(USART_x, *str);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////�ȴ����ͽ�
  str++;
  
 }
 //fanhang(USART_x);//����ʵ������ٺ��ʵĵط����ϻ���
 
}
	
/*******************************
������:USART_Sendnumber(double m)
���ܣ�����һ��double������
����ֵ����
********************************/
void USART_Sendnumber(USART_TypeDef* USART_x,double m)
{  char p[100]={'\0'};
   sprintf(p, "%f", m);
   USART_Sentstring(USART_x,p);
}
/*******************************
������:void USART_Send_NUM(double m,int wei)
���ܣ�����һ��double������
����ֵ����
wei Ҫ������С��λ��
********************************/
void USART_Send_NUM(USART_TypeDef* USART_x,double m,int wei)
{  
   char p[100]={'\0'};
   sprintf(p, "%f", m);
   USART_Sentstring_1(USART_x,p,wei);
}
/*******************************
������:USART_Send_u32(u32 m)
���ܣ�����һ��u32������
����ֵ����
********************************/
void USART_Send_u32(USART_TypeDef* USART_x,u32 m)
{  char p[100]={'\0'};
   sprintf(p, "%d", m);
   USART_Sentstring(USART_x,p);
}

/********************************8
���͸� ��Ƭ��
���ֽڽ��� �ڷ������ݴ��� ��Ҫ�Զ��忪ͷ��βʶ���
***********************************/


/****************************
��������void USART_Sentstring_MPU(char *str)
���ܣ�����һ���ַ���
����ֵ����
******************************/
void USART_Sentstring_MPU(USART_TypeDef* USART_x,char *str)
{
 
 USART_SendData(USART_x,'F');//���ݿ�ʼ��־ F��first��
 while(*str!='\0')
 {
  USART_SendData(USART_x, *str);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET);////�ȴ����ͽ�
  str++;
 }
 USART_SendData(USART_x,'\r');//���ݽ�����־ E��end��
}
/****************************
��������void USART_Sentstring_1(char *str,int n)
���ܣ�����һ���ַ���
���� ��������  ר��
����ֵ����
******************************/

void USART_Sentstring_1_MPU(USART_TypeDef* USART_x,char *str,int n)
{
	int flag=0;
	USART_SendData(USART_x,'F');//���ݿ�ʼ��־ F��first��
    while(*str!='\0')
    {
	 if(*str=='.')
	 { flag=1;
	   n+=1;
	 }
    if(flag)
    { if(n==0)
	 break;
	 n--;
     }	  
    USART_SendData(USART_x, *str);
    while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////�ȴ����ͽ�
    str++;
  
   }
 USART_SendData(USART_x,'\r');//���ݽ�����־ E��end��
}
	
/*******************************
������:void USART_Send_NUM(double m,int wei)
���ܣ�����һ��double������
����ֵ����
wei Ҫ������С��λ��
********************************/
void USART_Send_NUM_MPU(USART_TypeDef* USART_x,double m,int wei)
{  
   char p[100]={'\0'};
   sprintf(p, "%f", m);
   USART_Sentstring_1_MPU(USART_x,p,wei);
}







  /***********************************8
����pid�ĵ���ģ�鹦�ܺ���      start
  *********************************888*/

//���ֽڽ��� 
u16 length=0;
u8  Start=0;
u8  Usart_State=0x00;
            /*
            Usart_State  ����
            0x01 ��ʼ������Ч���ݱ�־λ
            0x02 ��Ч���ݽ������
            0x04 �����������Ч���ݵĳ��ȳ����˴洢���ݵ�����Ĵ�С��
            0x08 �����Ƿ񱻶�ȡ
            0x10 ���ݴ洢�����Ϊ�� 1 ��Ϊ�� 0 Ϊ��
            0x20 ���յ���Ч����
            */

void Clr_Rx(u8 *p)       //���  ����
	{
		int i=0;
		for(i=0;i<=(USART_REC_LEN-1);i++)
		{
			p[i]='\0';
		}
		length=0;	
	}
void Clr_array(u8 *p,u8 Array_Len)  //�������   ����  �ַ������Ⱥ� ָ��
	{
		int i=0;
		for(i=0;i<=(Array_Len-1);i++)
		{
			p[i]='\0';
		}
	}
    
    
    
    /////*       UARTʹ��        *//////
//1.�ڽ����ж�һ���ַ����Ͳ�Ҫ��ӷ��͵ȴ����Ա�֤�����������ܡ�2���ڷǽ����жϺ������������ַ�������ӷ��͵ȴ�����ȷ���������ݡ�
void USART1_IRQHandler(void)    //UART  �жϺ���
	{    
		u8 Rx;
		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{    
			Rx=USART_ReceiveData(USART1);
            if(Usart_State&0X01)
			{
				if(Rx=='E')
				{
					length=0;
					Usart_State&=~0x01;
					Usart_State|=0x02;
					Usart_State|=0X10;
					
					
				}
				else
				{
					if(length<=(USART_REC_LEN-1))
					{
						USART_RX_BUF[length]=Rx;
						length++;
					}
					else
					{  
						Usart_State|=0x04;
						return ;
					}					
				}					
			}
             else
			 {
				 if(Rx =='S')
			     {
				   if(Usart_State&0X10)//���ݵĴ洢���Ƿ�Ϊ�� ��Ϊ�� ��������ݴ洢��
			        {
				        Clr_Rx(USART_RX_BUF);
					       Usart_State&=~0X10;//�������ݴ洢��
			         }
				   Usart_State|=0x01;
				   Usart_State&=~0x02;
				   
			     }
             }				 
	    }
 }
/*************ESP8266 ���ݽ���***************/
 void USART2_IRQHandler(void)
	{    
		u8 Rx;
		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{  
				Rx=USART_ReceiveData(USART2);
			    // Recieve_data(Rx);//dui
//					if(length<=(USART_REC_LEN-1))
//					{
//						USART_RX_BUF[length]=Rx;
//						length++;
//					}
//					else
//					{
//						length=0;
//						USART_RX_BUF[length]=Rx;
//						
//					}
			
		}
 }
/*
void USART1_IRQHandler(void)
	{
	   u8 Res;
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			  {
				if(Res!=0x0a)
					USART_RX_STA=0;//���մ���,���¿�ʼ
				else 
					USART_RX_STA|=0x8000;	//��������� 
			  }
			else
			   {	
				if(Res==0x0d)
					USART_RX_STA|=0x4000;
				else
				  {
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
					  USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				  }		 
			   }
			 }   		 
     } 
 }

*/
         //  u8: unsigned char    u16:unsigned short int     u32:unsigned int
          /*  #include "stdlib.h"  //  atof atoi��ͷ�ļ�
              #include "string.h"  //�����   strcmp������  ͷ�ļ�    */
void UsartChangePID(u8 *p)      
{   
	char FloatOrInt=0;
	char pid[10];       //   �ַ����ַ���                         
	char num[10];        //   ��Ӧ�����ָ����ַ���
    int  i=0,j=0;
	char *s1,*s2;                            
	double Vatual=0;
	
	while((j<10)&&(p[i]!='='))        //  �ַ������ָ��        ǰ����   
	{
		pid[j]=p[i];
		i++;
		j++;	
	}
	pid[j]='\0';
	s1=pid;
	j=0;
	if(p[i]=='=')
	{ 
		i++;                                 
	  while((j<10)&&(p[i]!='\0'))      //   ����תΪ�ַ���ָ��        �󲿷�
	  { 
		  if(p[i]=='.')
		  FloatOrInt=1;
			
		   num[j]=p[i];
		i++;
		j++;	
	  }	
	}
	num[j]='\0';
	s2=num;
	if(FloatOrInt)                                     
		Vatual=atof(s2);            //atof    ���ַ���ת��Ϊ    double   ����������� ת��Ϊdouble
	else
	  Vatual=atoi(s2);                      //atoi           ���ַ���ת��Ϊ    int
	
	if(strcmp(s1, "Proportion")==0)         //�Ƚ������ַ����Ƿ�һ����  ���ж����ĸ�  �ַ�Ҳ�����ĸ�����
	{
		sptr->Proportion=(double)Vatual;
	}
	if(strcmp(s1, "Integral")==0)
	{
		sptr->Integral=(double)Vatual;
	}
	if(strcmp(s1, "Derivative")==0)
	{
	sptr->Derivative=(double)Vatual;
	}
    
//	if(strcmp(s1, "Kp_G")==0)
//	{
//		Kp_G=Vatual;
//	}
//	if(strcmp(s1, "Ki_G")==0)
//	{
//		Ki_G=Vatual;                                  
//	}
//	if(strcmp(s1, "Kd_G")==0)
//	{
//		Kd_G=Vatual;
//	}
//	if(strcmp(s1, "Pwm1")==0)
//	{
//		Pwm1=(u8)Vatual;
//	}
//	if(strcmp(s1, "Pwm2")==0)
//	{
//		Pwm2=(u8)Vatual;
//	}
//	if(strcmp(s1, "QbT")==0)
//	{
//		Qibai_T=(u8)Vatual;    
//	}
//	if(strcmp(s1, "TDt")==0)
//	{
//		TDt=(u8)Vatual;
//	}
//	if(strcmp(s1, "SAL")==0)
//	{
//		SAL=(int)Vatual;
//	}
//	if(strcmp(s1, "SAR")==0)
//	{
//		SAR=(int)Vatual;
//	}
//	if(strcmp(s1, "DAR")==0)
//	{
//		DAR=(int)Vatual;
//	}
//	if(strcmp(s1, "DAL")==0)
//	{
//		DAL=(int)Vatual;
//	}
}
/****************************************
main���� �е�  �÷����Ǹ��������ַ�����  ��ʾĿǰ��������ʲô
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
     }

  /***********************************8
����pid�ĵ���ģ�鹦�ܺ���      finish
  *********************************888*/






/***************************
��������
���ܣ���4�ֽڵ�float�Ե�����ת��Ϊ4��char�Ե��ַ�
�Ӹ�λ����λ����
����ֵ��
****************************/
char * FloatChangeChar(float num,char *p)
{   u8 i=0;
	char buf[4];
	for( i=0;i<4;i++)
	{
		buf[i]=(* ( (char *)(&num)+(3-i) ) );
		p[i]=  (* ( (char *)(&num)+(3-i) ) );
	}
	return buf;
}
/***************************
��������
���ܣ���4�ֽڵ�float�Ե�����ת��Ϊ4��char�Ե��ַ�
�Ӹ�λ����λ����
����ֵ��
****************************/
char * IntChangeChar(int num,char *p)
{   u8 i=0;
	char buf[4];
	for( i=0;i<4;i++)
	{
		buf[i]=(* ( (char *)(&num)+(4-i) ) );
		p[i]=  (* ( (char *)(&num)+(4-i) ) );
	}
	return buf;
	
}

/***************************
��������
���ܣ���4�ֽڵ�float�Ե�����ת��Ϊ4��char�Ե��ַ�
�Ӹ�λ����λ����
����ֵ��
****************************/
char * U16ChangeChar(u16 num,char *p)
{   u8 i=0;
	char buf[2];
	for(i=0;i<2;i++)
	{
		buf[i]=(* ( (char *)(&num)+(2-i) ) );
		p[i]=  (* ( (char *)(&num)+(2-i) ) );
	}
	return buf;
	
}
/***************************
��������
���ܣ���4�ֽڵ�float�Ե�����ת��Ϊ4��char�Ե��ַ�
�Ӹ�λ����λ����
����ֵ��
****************************/
char * U32ChangeChar(u32 num,char *p)
{   u8 i=0;
	char buf[4];
	for( i=0;i<4;i++)
	{
		buf[i]=(* ( (char *)(&num)+(4-i) ) );
		p[i]=  (* ( (char *)(&num)+(4-i) ) );
	}
	return buf;
	
}

void usart1_niming_report(u8 fun,float num,u8 len)

{
   static u8 d=0;
	
    u8 send_buf[32];

    u8 i;
	d++;
    if(len>28)return;    //���28�ֽ����� 

    send_buf[len+3]=0;  //У��������

    send_buf[0]=0X88;   //֡ͷ

    send_buf[1]=fun;    //������

    send_buf[2]=len;    //���ݳ���
    send_buf[3]=bity3(num);
    send_buf[4]=bity2(num);
    send_buf[5]=bity1(num);
    send_buf[6]=bity0(num);
    send_buf[7]=d;
    //for(i=0;i<len;i++)send_buf[3+i]=data[i];     //��������
    for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];    //����У��� 

    for(i=0;i<len+4;i++)USART_SentChar(USART1,send_buf[i]);   //�������ݵ�����1 

}
/*
//ͨ������1�ϱ���������̬���ݸ�����

//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ

//gyrox,gyroy,gyroz:x,y,z�������������������ֵ

//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��

//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��

//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��

void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)

{

    u8 tbuf[28]; 

    u8 i;

    for(i=0;i<28;i++)tbuf[i]=0;//��0

    tbuf[0]=(aacx>>8)&0XFF;

    tbuf[1]=aacx&0XFF;

    tbuf[2]=(aacy>>8)&0XFF;

    tbuf[3]=aacy&0XFF;

    tbuf[4]=(aacz>>8)&0XFF;

    tbuf[5]=aacz&0XFF; 

    tbuf[6]=(gyrox>>8)&0XFF;

    tbuf[7]=gyrox&0XFF;

    tbuf[8]=(gyroy>>8)&0XFF;

    tbuf[9]=gyroy&0XFF;

    tbuf[10]=(gyroz>>8)&0XFF;

    tbuf[11]=gyroz&0XFF;    

    tbuf[18]=(roll>>8)&0XFF;

    tbuf[19]=roll&0XFF;

    tbuf[20]=(pitch>>8)&0XFF;

    tbuf[21]=pitch&0XFF;

    tbuf[22]=(yaw>>8)&0XFF;

    tbuf[23]=yaw&0XFF;

    usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF

}
//���ͼ��ٶȴ��������ݺ�����������

//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ

//gyrox,gyroy,gyroz:x,y,z�������������������ֵ

void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)

{

    u8 tbuf[12]; 

    tbuf[0]=(aacx>>8)&0XFF;       //16λ���ݲ��Ϊ�����ִ���

    tbuf[1]=aacx&0XFF;

    tbuf[2]=(aacy>>8)&0XFF;

    tbuf[3]=aacy&0XFF;

    tbuf[4]=(aacz>>8)&0XFF;

    tbuf[5]=aacz&0XFF; 

    tbuf[6]=(gyrox>>8)&0XFF;

    tbuf[7]=gyrox&0XFF;

    tbuf[8]=(gyroy>>8)&0XFF;

    tbuf[9]=gyroy&0XFF;

    tbuf[10]=(gyroz>>8)&0XFF;

    tbuf[11]=gyroz&0XFF;

    usart1_niming_report(0XA1,tbuf,12);//�Զ���֡,0XA1

}
*/