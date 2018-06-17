#ifndef __PID_H
#define __PID_H	 

#define P_DATA 2
#define I_DATA 0
#define D_DATA 0

typedef struct PID
{
	int SetPoint;	//�趨Ŀ�� Desired Value
	long SumError;  //����ۼ�
	double Proportion; //�������� Proportional Const
	double Integral; //���ֳ��� Integral Const
	double Derivative; //΢�ֳ��� Derivative Const
	int LastError; //Error[-1]     
	int PrevError; //Error[-2]
}PID;
PID x��
PID* spt=&x�� 

void PIDInit1(PID *sptr,int setpoint);
int LocPIDCalc(PID *sptr,int NextPoint);

#endif
