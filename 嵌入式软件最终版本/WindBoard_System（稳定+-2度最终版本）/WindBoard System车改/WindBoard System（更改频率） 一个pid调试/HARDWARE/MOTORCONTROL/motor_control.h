# ifndef __MOTOR_CONTROL_
# define __MOTOR_CONTROL_
# include "sys.h"
# include "pid.h"

//������Ŀ1ģʽ
void base1Mode(void);

//������Ŀ2ģʽ
void base2Mode(void);

//Ӳ�����У׼
int changeData(u8 dat);

//�ж��Ƿ�ﵽĿ��ֵ
u8 isTarget(int dat);


# endif

