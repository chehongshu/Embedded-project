#include "blue_tooth.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

 void Blue_tooth_number(USART_TypeDef* USART_x,double angle)
{
        /**************************
                 ���ͽ׶�
        **************************/ 
	      USART_Sendnumber(USART_x,angle)	;		
        //���յ������ݱ�����0x0d 0x0a��β  ����ÿ�η���һ����Ҫ ����0x0d 0x0a
        USART_SendData(USART_x,0x0d);                                      //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);      //    �ж�    ����  �Ƿ�  ���
        USART_SendData(USART_x,0x0a);                                        //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);       //    �ж�    ����  �Ƿ�  ���
        delay_ms(1000);
}

void Blue_tooth_String(USART_TypeDef* USART_x,char* string)
{
        /**************************
                 ���ͽ׶�
        **************************/ 
	      USART_Sentstring(USART_x,string)	;		
        //���յ������ݱ�����0x0d 0x0a��β  ����ÿ�η���һ����Ҫ ����0x0d 0x0a
        USART_SendData(USART_x,0x0d);                                      //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);      //    �ж�    ����  �Ƿ�  ���
        USART_SendData(USART_x,0x0a);                                        //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);       //    �ж�    ����  �Ƿ�  ���
        delay_ms(1000);
}
