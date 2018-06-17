#ifndef	__PID_H__
#define __PID_H__
# include "sys.h"
 
 typedef struct PID 
{ 
	long SumError;      //����ۼ�
	double Proportion;  //�������� 
	double Integral;    //���ֳ��� 
	double Derivative;  //΢�ֳ��� 
	double LastError;      //Error[-1] 
	double PrevError;      //Error[-2] 
} PID;

extern  PID sPID; 
extern  PID *sptr;

void leftPid_Init(void); 
double IncPID_Calc(double SetPoint, double actualPoint);
double IncPID_Calc(double SetPoint, double actualPoint) ;
void pidsetKpid(int dat1, int dat2, int dat3);
void baseRun(void);
void promoteRun(void);
//�ұߵ��pid����
double rightMontorCal(double target, double actual);

#endif
