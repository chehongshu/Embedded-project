#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 

#define KEY1    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)  //��ȡ����1
#define KEY2    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //��ȡ����2
#define KEY3    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)  //��ȡ����3 
#define KEY4    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)  //��ȡ����4
#define KEY5    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) //��ȡ����5
#define KEY6    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)  //��ȡ����6 
 

#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES 4   //KEY4
#define KEY5_PRES 5   //KEY5
#define	KEY6_PRES 6   //KEY6

void KEY_Init(void);   //IO��ʼ��
u8 KEY_Scan(void);  	 //����ɨ�躯��			
void KEY1_Fun(void);   //����1����ʵ��
void KEY2_Fun(void);   //����2����ʵ��
void KEY3_Fun(void);   //����3����ʵ��
void KEY4_Fun(void);   //����4����ʵ��
void KEY5_Fun(void);   //����5����ʵ��
void KEY6_Fun(void);   //����6����ʵ��
void MenuSureKey_Fun(void);//�˵�ȷ�ϼ�����ʵ��
void changeTargetDataUp(u8 * data); //�ı�Ŀ��ֵ�������ӣ�
void changeTargetDataDown(u8 * data);  //�ı�Ŀ��ֵ����������

#endif
