# include "screen.h"
# include "12864.h"
# include "sysvalue.h"

extern u8 targetData1;
extern u8 targetData2[2];
extern u8 numLocate;

extern float pitch;
extern double currentPwmData;
extern double currentPwmData2;

//��ʾ�˵�ѡ�����
void showMenu(u8 selectNum)
{
	LCD_Clear_Screen();          //����
	LCD_HZS(1, 25, (u8*)"012345");  //������ϵͳ
	LCD_HZS(4, 20, (u8*)"67");        
	LCD_ASCALL('1'); 									//����1
	LCD_HZS(4, 80, (u8*)"67");        
	LCD_ASCALL('2');									//����2
	LCD_HZS(7, 20, (u8*)"89");        
	LCD_ASCALL('1');  								//���1
	LCD_HZS(7, 80, (u8*)"89");        
	LCD_ASCALL('2'); 									//���2
	
	switch ( selectNum )
	{
		case BASE1: LCD_HZS_OP(4, 20, (u8*)"67"); LCD_ASCALL_OP('1'); break;
		case BASE2: LCD_HZS_OP(4, 80, (u8*)"67"); LCD_ASCALL_OP('2'); break;
		case IMPROVE1: LCD_HZS_OP(7, 20, (u8*)"89"); LCD_ASCALL_OP('1'); break;
		case IMPROVE2: LCD_HZS_OP(7, 80, (u8*)"89"); LCD_ASCALL_OP('2'); break;
		default: break;
	}
}

//��ʾ������1�������1�ĽǶ����ý���
void allQuestion1Set(u8 numLocate)
{
	LCD_Clear_Screen();          //����
	LCD_HZS(1, 35, (u8*)":;<=");  //�Ƕ�����
	LCD_Add_XY(5, 50);
	LCD_int(targetData1/100);
	LCD_int(targetData1%100/10);
	LCD_int(targetData1%10);
	switch (numLocate)
	{
		case 1:	LCD_Clear_Line(4); LCD_Add_XY(4, 50); LCD_ASCALL('!');break;
		case 2:	LCD_Clear_Line(4); LCD_Add_XY(4, 55); LCD_ASCALL('!');break;
		case 3: LCD_Clear_Line(4); LCD_Add_XY(4, 60); LCD_ASCALL('!');break;
		default: break;
	}
}

//��ʾ������1�������1�Ŀ�ʼ����
void allQuestion1Start(u8 queNum)
{
	LCD_Clear_Screen();          //����
	if ( 1==queNum )
	{
		LCD_HZS(2, 35, (u8*)"67");  //����
	}
	else if (2==queNum )
	{
		LCD_HZS(2, 35, (u8*)"89");  //���
	}
	LCD_Add_XY(2, 62);
	LCD_int(1);
	LCD_HZS(2, 70, (u8*)">?");  //��ʼ
	LCD_Add_XY(5, 35);
	LCD_ASCALLS((u8 *)"TARGET DATA");
	LCD_Add_XY(7, 50);
	LCD_int(targetData1);
}

//����2/���2�Ƕ����ý���
void allQuestion2Set(u8 numLocate, u8 num)
{
	LCD_Clear_Screen();          //����
	LCD_HZS(1, 35, (u8*)":;<=");  //�Ƕ�����
	LCD_Add_XY(1, 100);
	LCD_int(num+1);
	LCD_Add_XY(5, 50);
	LCD_int(targetData2[num]/100);
	LCD_int(targetData2[num]%100/10);
	LCD_int(targetData2[num]%10);
	switch (numLocate)
	{
		case 1:	LCD_Clear_Line(4); LCD_Add_XY(4, 50); LCD_ASCALL('!');break;
		case 2:	LCD_Clear_Line(4); LCD_Add_XY(4, 55); LCD_ASCALL('!');break;
		case 3: LCD_Clear_Line(4); LCD_Add_XY(4, 60); LCD_ASCALL('!');break;
		default: break;
	}
}

//����2/���2�Ƕȿ�ʼ����
void allQuestion2Start(u8 num)
{
	LCD_Clear_Screen();          //����
	if ( 1==num )
	{
		LCD_HZS(2, 35, (u8*)"67");  //����
	}
	else if ( 2==num )
	{
		LCD_HZS(2, 35, (u8*)"89");  //���
	}
	LCD_Add_XY(2, 62);
	LCD_int(2);
	LCD_HZS(2, 70, (u8*)">?");  //��ʼ
	LCD_Add_XY(5, 15);
	LCD_ASCALLS((u8 *)"  DATA1     DATA2");
	LCD_Add_XY(7, 35);
	LCD_int(targetData2[0]);
	LCD_Add_XY(7, 90);
	LCD_int(targetData2[1]);
}

//�������1���н���
void allQuestion1Runing(u8 num)
{
	LCD_Clear_Screen();          //����
	if ( 1==num )
	{
		LCD_HZS(2, 35, (u8*)"67");  //����
	}
	else if (2==num )
	{
		LCD_HZS(2, 35, (u8*)"89");  //���
	}
	LCD_Add_XY(2, 62);
	LCD_int(1);
	LCD_Add_XY(2, 70);
	LCD_ASCALLS((u8 *)"RUNNING");

	LCD_Add_XY(5, 35);
	LCD_ASCALLS((u8 *)"TARGET DATA");
	LCD_Add_XY(7, 50);
	LCD_int(targetData1);
}

//����2/���2���н���
void allQuestion2Running(u8 num)
{
	LCD_Clear_Screen();          //����
	if ( 1==num )
	{
		LCD_HZS(1, 35, (u8*)"67");  //����
	}
	else if ( 2==num )
	{
		LCD_HZS(1, 35, (u8*)"89");  //���
	}
	LCD_Add_XY(1, 70);
	LCD_ASCALLS((u8 *)"RUNNING");
	LCD_Add_XY(1, 62);
	LCD_int(2);
	LCD_Add_XY(5, 15);
	LCD_ASCALLS((u8 *)"  DATA1     DATA2");
	LCD_Add_XY(7, 35);
	LCD_int(targetData2[0]);
	LCD_Add_XY(7, 90);
	LCD_int(targetData2[1]);
}

//ʵʱ��ʾ����ˢ��
void freshData(void)
{
	//��ʾʵʱ�Ƕ�
	LCD_Clear_Line(3);
	LCD_Add_XY(3, 50);
	LCD_int(90-pitch);
	
	//��ʾʵʱռ�ձ� ��ߵ��
		LCD_Clear_Line(4);
		LCD_Add_XY(4, 25);
		LCD_int(currentPwmData);
	
  //��ʾʵʱռ�ձ� �ұߵ��
		LCD_Add_XY(4, 65);
		LCD_int(currentPwmData2);
		
}


