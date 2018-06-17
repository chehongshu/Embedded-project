# include "sys.h"
# include "delay.h"
# include "malloc.h"
# include "cJSON.h"
# include "usart.h"

int code;

struct result_data
{
    u32 cID;
    char *pName;
    char *datetime;
    u8 cStatus;
};

struct result_data resultData;

/* Parse text to JSON, then render back to text, and print! */
void doit(char * jsonText)
{
	cJSON * root;
	cJSON * result;
	
	//��json����ת��Ϊjson�ṹ��
  root = cJSON_Parse(jsonText);
	
	if ( root )   //json����װ���ɽṹ��ɹ�
	{
		 code = cJSON_GetObjectItem(root, "code")->valueint;
		
		 if ( 200==code )   //���ݽ�����ȷ
		 {
			 result = cJSON_GetObjectItem(root, "result");
			 
			 if ( result )  //��ȡ�������ݳɹ�
			 {
				 resultData.cID = cJSON_GetObjectItem(result, "id")->valueint;
				 resultData.pName = cJSON_GetObjectItem(result, "name")->valuestring;
				 resultData.cStatus = cJSON_GetObjectItem(result, "status")->valueint;
				 resultData.datetime = cJSON_GetObjectItem(result, "datetime")->valuestring;
				 cJSON_Delete(result);
			 }
		 }
	}
	else   //json����ת��ʧ��
	{
		
	}
	 cJSON_Delete(root);
}


 int main(void)
 {
	char receiveData[1000];
	u8 jsonFlag = 0;   //json������־λ 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);
	 
	mem_init();
	 
	while(1)
	{
		  int16_t len = 0;
		  int i = 0;
		
			//���յ����͹���������
			if(USART_RX_STA&0x8000 && 0==jsonFlag )
			{
				len=USART_RX_STA&0x3fff; //�õ����ݽ��յĳ���
				
				//���json���ݽ�������
				for (i=0; i<1000; i++)
				{
					receiveData[i] = 0;
				}
				
				//���½��ܻ�������
				for (i=0; i<len; i++)
				{
					receiveData[i] = USART_RX_BUF[i];
				}
				jsonFlag = 1;
				USART_RX_STA = 0;
			}
			
			//�������յ���json����
			if ( jsonFlag )
			{
				doit(receiveData);
				jsonFlag = 0;
			}
	}
 }
