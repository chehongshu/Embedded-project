#include "pid.h"   
 //  λ��ʽpid
  
void PIDInit1(PID *sptr,int setpoint) 
{  
	sptr->SumError = 0; 
	sptr->LastError = 0; //Error[-1]  
	sptr->PrevError = 0; //Error[-2]
	
	 
	sptr->Proportion = P_DATA; //�������� Proportional Const  
	sptr->Integral = I_DATA ;//���ֳ���Integral Const  
	sptr->Derivative = D_DATA; //΢�ֳ��� Derivative Const  

	sptr->SetPoint = setpoint;
}

int LocPIDCalc(PID *sptr,int NextPoint)
{   
	int iError,dError;
	iError = sptr->SetPoint - NextPoint; //ƫ��
	sptr->SumError += iError;   //����
	/*if(sptr->Integral * sptr->SumError>300)
	{
		sptr->SumError=(int)(300.0/sptr->Integral);
	}
	if(sptr->Integral * sptr->SumError<-300)
	{
		sptr->SumError=(int)(-300.0/sptr->Integral);
	}*/

	dError = iError - sptr->LastError; //΢��
	sptr->LastError = iError;
	return((int)(sptr->Proportion * iError) //������		
		+ (int)(sptr->Integral * sptr->SumError) //������ 
		+ (int)(sptr->Derivative * dError)); //΢���� 
} 
