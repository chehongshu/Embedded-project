#include "details_func.h"
#include "Hair_dryer.h"
#include "steppermotor.h"
#include "Photoelectric_door.h"
#include "function.h"


/***********************************************************************************************************
*������
*���ܣ�  ���½ṹ �ջ�����һֱɨ����
*������      ��
*���أ�      ��
*************************************************************************************************************/
int      shangxia_closedLoop_scan_flag = 0;
int      i_closedLoop;
int      closed_Loop_bushu_sum;

void shangxia_closedLoop_scan()
{
						
		         shangxia_go_X(100); //  turn  down   100
	
						if(shangxia_PDoor == 1)
						{
								
									   shangxia_closedLoop_scan_flag = 1;
							
						}
						
						if(	shangxia_closedLoop_scan_flag == 1)
						{
											for(i_closedLoop=0;i_closedLoop<2;i_closedLoop++)//2
											{
												
												        	shangxia_go_S(400); //   ����    400
											
											}
										
									    shangxia_closedLoop_scan_flag = 0;
											
						}

	        



}




int   HD_zuoyou_delaytime; //  ���ҵ� Ƶ��
int   i_HD1;
/***********************************************************************************************************
*������
*���ܣ�   ���������
*��������
*���أ���
*************************************************************************************************************/
int  hair_dry_flag = 0;  //  ���������ƶ���

int  HD_rotating_bushu = 1000  ;//   ��תһ���ߵ�  ����                       *��Ҫ����*
int  HD_ratating_zuoyou_bushu = 2000;//  ����������ߵĲ���							  *��Ҫ����*
int  HD_rotating_bushu_sum   ; //  ��������

//  for
int   hair_dry_i  ;
int   hair_dry_j  ;
void function_Hair_Dry()
{
			    switch(hair_dry_flag)
					{
						case 0:    
																			HD_zuoyou_go_R(100);	//  run   right 
																							break;
						
						case 1:								
																					//  ��λ  							
																					for(hair_dry_i = 0;hair_dry_i<30000;hair_dry_i++)
																						{
																								 if( hair_dry_flag  == 1)
																								 {
																									HD_rotating_go_L(100);
																								 }
																									 if(HD_rotating_PDoor == 1){
																										 
																											 hair_dry_flag = 2;
																											 break;
																								 }
																						}
																						
																				
																
						case 2:		      	
							
																		for(hair_dry_i = 0;hair_dry_i<HD_rotating_bushu;hair_dry_i++)
																		{
																							  HD_rotating_go_R(205);
																			
																							for(hair_dry_j =0;hair_dry_j<2;hair_dry_j++)
																							{
																										HD_zuoyou_go_L(150);
																							}
																		}
																	
															  
																			break;
																	
						case 3:								              
																	
																			for(hair_dry_i = 0;hair_dry_i<HD_rotating_bushu;hair_dry_i++)
																			{
																								 HD_rotating_go_L(195);
																								for(hair_dry_j = 0;hair_dry_j < 2;hair_dry_j++)
																								{
																								 HD_zuoyou_go_R(150);	
																								}
																						
																			 } 
																					break;
						
                 }
}

/***********************************************************************************************************
*������
*���ܣ�    ��ˮ����
*��������
*���أ���
*************************************************************************************************************/
// about main func
extern int reset;

//     flag
int Water_spray_flag = 0;
int quit_flag = 0;
extern int reset_flag;

//      for
int water_i;
void Water_spray_func()
{
	      		//  �����ж���  ����  ��λλ��  �ڸ�λλ���� ����   ֱ�� ������һ������
								if(  reset_flag ==1 )
								{
											//  �պ� ��ԭ��λ�ò���Ҫ��
											// ��ǰ��һ��
														 //  ��ǰ��һ��       
																								if(quit_flag == 0)
																								{		
																									                    for(water_i=0;water_i<2000;water_i++)
																																				{
																																								shangxia_go_S(400); //   ����  
																																				 }
																																				
																																			for( water_i=0;water_i<1000;water_i++)
																																			{
																																								qianhou_go_Q(200);		  //   ��ǰ��һ��
																																			}
																																		
																																			
																																	quit_flag = 1;  //  �˳��������
																																	
																								 }
																								
																																  zuoyou_go_R(80);
																																 if(Water_spray_flag == 1)
																																 {
																																	 
																																	 
																																	      //  ����ת   ת���м�
																																					for(water_i=0;water_i<20000;water_i++)
																																					{
																																								 zuoyou_go_L(80);
																																					}
																																			
																																					
																																					
																																					 	 for(water_i=0;water_i<100000;water_i++) 
																																						{
																																												HD_zuoyou_go_R(100);
																																											if(HD_zuoyou_PDoor_R == 1)
																																											{
																																															break;
																																											}
																																						 }
																																							 for(water_i=0;water_i<200;water_i++) 
																																						{
																																												HD_zuoyou_go_L(100);
																																									
																																						 }
																																							for(water_i = 0;water_i<30000;water_i++)
																																									{
																																											 
																																												HD_rotating_go_L(100);
																																											 
																																												 if(HD_rotating_PDoor == 1){
																																													 
																																														 break;
																																											 }
																																									}
																																								for(water_i = 0;water_i<4000;water_i++)
																																									{
																																											 
																																												HD_rotating_go_R(100);
																																											 
																																									
																																									}
																																													reset = 1;

																																								 }
																												 
										}else{
																																						//  ����   һ��λ��
																																						qianhou_go_H(200);
																																						//   һֱ������1ʱ����
										
														}
}
// main func
extern int second_qianhou_flag;

// for
int water_i2;

int  water_pwm  =  200 ;  //  ��ǰ��ǰ��� �ٶ�

void Water_spray_func_another()
{
	              relay_H;
	       	     	if( second_qianhou_flag  ==  0) 
								{
									           
																	// ��  ǰ
																qianhou_go_Q(water_pwm);
									
								}else if(second_qianhou_flag == 1)
								{	
																	// ��  ��
																qianhou_go_H(water_pwm);
									
								}
								if( second_qianhou_flag == 2)
								{
									
																for(water_i2=0 ; water_i2<100 ; water_i2++)
																{						
																				// ��  ǰ
																			qianhou_go_Q(water_pwm);
																	
																}
																reset  = 3;
													
								}
}
