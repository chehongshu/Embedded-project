#ifndef __USART_H
#define __USART_H	
#include "sys.h" 
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"

#define bity0(num) (* ( (char *)(&num)+0 ) )
#define bity1(num) (* ( (char *)(&num)+1 ) )
#define bity2(num) (* ( (char *)(&num)+2 ) )
#define bity3(num) (* ( (char *)(&num)+3 ) )
	
#define USART_REC_LEN  			100  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���
extern u16 length;
extern u8  Start;
extern u8  Usart_State;
/*
Usart_State �Զ���8λ����״̬�Ĵ�������
0x01 ��ʼ������Ч���ݱ�־λ
0x02 ��Ч���ݽ������
0x04 �����������Ч���ݵĳ��ȳ����˴洢���ݵ�����Ĵ�С��
0x08 �����Ƿ񱻶�ȡ
0x10 ���ݴ洢�����Ϊ�� 1 ��Ϊ�� 0 Ϊ��
*/

void fanhang(USART_TypeDef* USART_x);
void usart_init(u32 bound);
void usart2_init(u32 bound);

//void USART_Sentstring(char *str);
void USART_SentChar(USART_TypeDef* USART_x,char data);
void USART_Sentstring(USART_TypeDef* USART_x,char *str);
void USART_Sendnumber(USART_TypeDef* USART_x,double m);
void USART_Sentstring_1(USART_TypeDef* USART_x,char *str,int n);
void USART_Send_NUM(USART_TypeDef* USART_x,double m,int wei);
void USART_Send_u32(USART_TypeDef* USART_x,u32 m);
void USART_Sentstring_MPU(USART_TypeDef* USART_x,char *str);
void USART_Sentstring_1_MPU(USART_TypeDef* USART_x,char *str,int n);
void USART_Send_NUM_MPU(USART_TypeDef* USART_x,double m,int wei);
void Clr_Rx(u8 *p);
void Clr_array(u8 *p,u8 Array_Len);

void usart1_niming_report(u8 fun,float num,u8 len);
void UsartChangePID(u8 *p);

#endif
