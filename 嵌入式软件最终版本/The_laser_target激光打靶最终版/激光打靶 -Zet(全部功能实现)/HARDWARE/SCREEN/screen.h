# ifndef __SCREEN_H
# define __SCREEN_H
# include "sys.h"

//�õ���ǰ��������
void getCurrentPoint(void);

//�����3�ﵽ���⻷��
void improve3Fun(u8 target);

//�����2�ص�10��
void improve2Fun(void);

//�����1��ʾ����
void improve1Fun(void);

//�����1��˸hongdian
void slightPoint(u8 dat);

//������3���������
void base3Fun(void);

//�е�����У׼��ť����
void centerAdjustFun(void);

//��Ե����У׼��ť����
void borderAdjustFun(void);

//���ʹ���ָ��ֹͣλ
void stop(void);

# endif
