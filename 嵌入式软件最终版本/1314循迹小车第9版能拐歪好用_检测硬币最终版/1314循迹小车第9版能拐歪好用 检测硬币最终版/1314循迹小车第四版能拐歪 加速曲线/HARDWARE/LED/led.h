#ifndef __LED_H
#define __LED_H	 
#include "sys.h"



#define LED0 PCout(8)	// PC8          ���
#define LED1 PCout(9)	// PC9	        �Ƶ�
#define LED2 PCout(10)	// PC10	        �̵�

//    ���� ��   
//    PC8  ���  
//    PC9  �Ƶ�
//    PC10 �̵�
//


void LED_Init(void);//��ʼ��

		 				    
#endif
