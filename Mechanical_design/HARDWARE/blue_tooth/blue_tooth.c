#include "delay.h"
#include "sys.h"
#include "usart.h"

//   ���� �������ͽ��� �� ���ӳ���

// sprintf(sendbuf,"n0.val=%d",aaa);

//        
//         /*************************
//                ���ܽ׶�
//         *************************/
//        
//                  if(USART_RX_STA&0x8000)  //   �жϽ��������  ��if����ȥ
//		        {					   
//			len=USART_RX_STA&0x3fff;      //�õ��˴ν��յ������ݳ���    ����λΪ0��ʵ����ȥ��0x0a �� 0x0b  ���Ծ������յ��ַ���������
//			printf("\r\n�����͵���ϢΪ:\r\n");          //  ֱ�ӷ����ڵ�  ��sprintfΪ���Դ���Ҳ��  Һ����Ҳֱ�ӷ�  ��������
//			    for(t=0;t<len;t++)
//			    {
//				USART1->DR=USART_RX_BUF[t];     //  ���յ������ݷ���
//				while((USART1->SR&0X40)==0);   //�ȴ����ͽ���
//			     }
//			printf("\r\n\r\n");  //  ���뻻��
//			USART_RX_STA=0;   /// ��־λ����
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
void  PC_senddata_HMI(int number)
{
        sprintf( sendbuf,"n0.val=%d", number); //  ��number��ֵ���뵽n0��
            i=0;
            while(sendbuf[i]!='\0')
           {
                USART_GetFlagStatus(USART1, USART_FLAG_TC);
                USART_SendData(USART1,sendbuf[i]);                               //��������
                while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};   //    �ж�    ����  �Ƿ�  ���
             i++;
             }
              //  ����������FF FF FF
                    USART_SendData(USART1,0xff);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){}; 
                    USART_SendData(USART1,0xff);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){}; 
                     USART_SendData(USART1,0xff);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){}; 
         
                  
}    
