# ifndef __SCREEN_H
# define __SCREEN_H
# include "sys.h"

//��ʾ�˵�����
void showMenu(u8 selectNum);

//��ʾ������1�������1�ĽǶ����ý���
void allQuestion1Set(u8 num);

//��ʾ������1�������1�Ŀ�ʼ����
void allQuestion1Start(u8 queNum);

//����2/���2�Ƕ����ý���
void allQuestion2Set(u8 numLocate, u8 num);

//����2/���2�Ƕȿ�ʼ����
void allQuestion2Start(u8 num);

//����2/���2���н���
void allQuestion2Running(u8 num);

//�������1���н���
void allQuestion1Runing(u8 num);

//ʵʱ��ʾ������ˢ��
void freshData(void);

# endif



