/***********************************************************
*                                                          *
* Copyright: (C), 2014, HDU-LISIA STA  rights reserved.    *
*                                                          *                                                          
* File name: PID.h                                         *
*                                                          *
* Author: GJane                                            *
*                                                          *
* Version: 1.0                                             *
*                                                          *
* Creation date: 2014/4/5                               	 *
*                                                          *
* Description:                                             *
*                                                          *
*                                                          *
*                                                          *
* Modification History:                                    *
*                                                          *
* <Modifier>      <Date>     <version>     <Modifications> *
*                                                          *
*                                                          *
*                                                          *
*                                                          *
***********************************************************/   

/**
 *  \file  PID.h
 *
 *  \brief
 */

#ifndef	__PID_H__
#define __PID_H__
 
 /*----------------------------------------------------------------------------
 *        �ṹ�嶨����
 *----------------------------------------------------------------------------*/
 typedef struct PID 
{ 
	long SumError;      //����ۼ�
	double Proportion;  //�������� 
	double Integral;    //���ֳ��� 
	double Derivative;  //΢�ֳ��� 
	double LastError;      //Error[-1] 
	double PrevError;      //Error[-2] 
} PID;

 /*----------------------------------------------------------------------------
 *        ����������
 *----------------------------------------------------------------------------*/
extern  PID sPID; 
extern  PID *sptr;

 /*----------------------------------------------------------------------------
 *        ����������
 *----------------------------------------------------------------------------*/
void IncPID_Init(void); 
double IncPID_Calc(double SetPoint, double NextPoint);

#endif
