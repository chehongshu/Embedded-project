#ifndef __MOVEXY_H
#define __MOVEXY_H
#include "sys.h" 

extern s32 aC,bC;
extern s32 aT,bT; //Ŀ��AB����
extern double stepnum;  // ������
extern s32 aE,bE; //AB����λ��ʸ��

void moveTo(double xT,double yT);
double upRand(double xT, double x0, double y0, double RandR);
double downRand(double xT, double x0, double y0, double RandR);
void DrawRand(double x0, double y0, double RandR);
#endif
