#ifndef __SORTSOF_WAYS_H
#define __SORTSOF_WAYS_H	 
#include "sys.h"
/**
*   ��������Ĺ���
*   ���ܵĻ���
*   anchor �� chehongshu
*   date �� 2017/5/13
**/


/**
*     ����    ����    ǰ���    io��ת�� ��ʱ   �� 
*      Ӱ���Զ���   io   ��ת��ռ�ձ�
*/
#define     shangxia_dalay    100

#define     qianhou_delay       200

#define     zuoyou_delay        200

/*
*     ���岽��
*     ��Ҫ����
*/

#define   qianhou_walkMount      3000     //  �����ǰһС���Ĳ�����
#define   zuozhuan_walkMount      55000   //   ���� �ص��м�Ĳ���
#define   shangxia_walkMount     70000    //  �������µĲ���



 /*******************************************
*   ��־λ����
******************************************/
void  clear_flag(void);


/*******************************************
*
*      �ָ���ԭλ
******************************************/
void ReSet_Location(void);
 /*******************************************
*      ����ͷ��
*       ���������  ��� ��Ӧ�� �˶�  ����
******************************************/
void Dry_Hair(void);



void wish_first_wish_hair(void);

void wish_another_wish_hair(void);


#endif
