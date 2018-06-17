#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "Photoelectric_door.h"
#include "steppermotor.h"
#include "function.h"
#include "timer.h"
#include "sortsOf_ways.h"
#include "Hair_dryer.h"
#include "details_func.h"


extern char reset;     //     �ı� ��ǰ���ܵ�˳�������

u8  HMI_receive; // ���� �ź� 0x01
u8 HMI_receive_BUF;
extern u8 Rx; //  �����ź�



int i_mian; //  ����
int flagmian;//  ����

int  fflag1=1;


/************************************************
 ALIENTEKս��STM32   ZET6
***********************************************/
extern int zuozhuan_flag;
extern int youzhuan_flag;

int main(void)
{
			 
							delay_init();	    //��ʱ������ʼ��	  
							LED_Init();                              
							KEY_Init();
							steppermotor_init(); 
							LED1_L;
							LED2_L;
	
							//  ����ŵĳ�ʼ�� 
							zuoyou_PDoor_Init();
							qianhou_PDoor_Init();
							shangxia_PDoor_Init();
	
							HD_zuoyou_PDoor_Init();
              HD_rotating_PDoor_Init();
        
	
								A_hair_dryer_init();
                relay_Init();
								TIM3_Int_Init(9999,71);//1ms     ɨ��
	
	               TIM4_Int_Init(4999,71);//100ms     scan
							
						  // ��ʼ�� Uart  ���� HMI ����������

							  usart2_init(9600);  //  HMI ��  ������  Ϊ9600  PA2  PA3
	              delay_ms(300);  //  aim to dianya pingwen

	
				while(1)
		  	{

					HMI_receive_BUF = HMI_receive;
								//	0x01  ��ʼ  0x02  ����    0x03 ��ͣ     0x04  ֹͣ
					HMI_receive  =  Rx;// ����HMI ����������

					if(HMI_receive_BUF   !=  HMI_receive )
					{
						   fflag1 = 1;
									 
									qianhou_ENA_NOT;
									zuoyou_ENA_NOT;
									shangxia_ENA_NOT;
								 HD_zuoyou_ENA_NOT;
			           HD_rotating_ENA_NOT; 
						
					}
					/**
					* HMI_receive    
					 0x01   -->  ����  ��һ��ϴͷ��ʽ
					 0x02   -->  ���� �ڶ���ϴͷ��ʽ
					 0x03   -->    �����ڶ���ϴͷ��ʽ�� �����汾
					 0x04   -->  ��ͣ
  					**/
					switch(HMI_receive)
					{

					
									case 0x01: 
//																				 if(fflag1)
//																					 {
//																																			 clear_flag();    
//																																				fflag1 = 0; 
//																																				reset = 0;
//																																	
//																						 }
																		 switch(reset)
																		 {
																			 
																					 case 0:            Water_spray_func(); break;
																					 case 1:
																																			//  ��־λ  ����
																																				clear_flag();
																																				 reset = 2;
																																					break;
																					 case 2:       			 Water_spray_func_another();  //  ��־λ  ����
																																					break;
																					 case 3:        	//  ��־λ  ����
																																					clear_flag();
																																					 reset = 4;
																																						break;
																					 case 4:      				   ReSet_Location();   break;  
																																											
																					 case 5:         				clear_flag();
																																				reset = 6; 
																																				HD_zuoyou_ENA_NOT;
																																				HD_rotating_ENA_NOT;
																																				 break;
																					 
																					 case 6:      						wish_first_wish_hair();   
																																		 //   wish_another_wish_hair();
																																						break;
																					 
																					 
																					 case 7:       				    clear_flag();
																																					reset = 8; break;
																					 
																					 case 8:        			      function_Hair_Dry();  break;
																			 
																		 }

																		 
																		 
																		 break;
																		 
							case  0x02:   // ����
								                           if(fflag1)
																						 {
																														 clear_flag();    
                																						  fflag1 = 0; 
																												      reset = 0;
																						 }
								                           switch(reset)
																	    	 {
																			 
																					 case 0:            Water_spray_func(); break;
																					 case 1:
																																	
																																				clear_flag();
																																				 reset = 2;
																																					break;
																					 case 2:       		//	 Water_spray_func_another();  //  ��־λ  ����
																						                              reset = 3;
																																					break;
																					 case 3:        	//  ��־λ  ����
																																					clear_flag();
																																					 reset = 4;
																																						break;
																					 case 4:      				  //           ReSet_Location();
                                       																			reset = 5;			
                                     																					 break;  
																																											
																					 case 5:         			 	clear_flag();
																																				reset = 6; 
																																				HD_zuoyou_ENA_NOT;
																																				HD_rotating_ENA_NOT;
																																				 break;
																					 
																					 case 6:      						//wish_first_wish_hair();   
																																		     // wish_another_wish_hair();
																					                                reset = 7;
																																						break;
																					 
																					 
																					 case 7:       				      clear_flag();
																																					reset = 8; break;
																					 
																					 case 8:        			             relay_L;
																						                                  function_Hair_Dry();  break;
																			 
																		 }
																																	break;
																						 
							case 0x03:                                relay_L;
																																 stop_motor();  //  ��ͣ
																																		break;
							
				      case 0x04:         
								                           if(fflag1)
																						 {
																														 clear_flag();   
                                                              relay_L;																							 
                																						  fflag1 = 0; 
																												      reset = 0;
																						 }
								                           switch(reset)
																	    	 {
																			 
																					 case 0:            Water_spray_func(); break;
																					 case 1:
																																	
																																				clear_flag();
																																				 reset = 2;
																																					break;
																					 case 2:       		//	 Water_spray_func_another();  //  ��־λ  ����
																						                              reset = 3;
																																					break;
																					 case 3:        	//  ��־λ  ����
																																					clear_flag();
																																					 reset = 4;
																																						break;
																					 case 4:      				reset = 5;
                       																	    //				 ReSet_Location();  
                                 																					 break;  
																																											
																					 case 5:         			 	clear_flag();
																																				reset = 6; 
																																				HD_zuoyou_ENA_NOT;
																																				HD_rotating_ENA_NOT;
																																				 break;
																					 
																					 case 6:      						//wish_first_wish_hair();   
																																		 //   wish_another_wish_hair();
																					                                reset = 7;
																																						break;
																					 
																					 
																					 case 7:       				      clear_flag();
								                                      
																																	             break;
																					 case 8:                   stop_motor();break;
																					 break;

 		                        		}
			}
					
    
////				        wish_another_wish_hair();


//											if(zuozhuan_flag == 1)
//											{
//												zuoyou_go_L(100);
//											}
//											if(youzhuan_flag == 0)
//											{
//												zuoyou_go_R(100);
//											}			
//								
//								
//											// shangxia_closedLoop_scan();
//										 
  							
							
			}
  
				
}
          
