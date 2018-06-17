# ifndef __LED_H
# define __LED_H	 
# include "sys.h"

# define LED0 PCout(8)	// PC8
# define LED1 PCout(9)	// PC9
# define LED2 PCout(10) // PC10


//��ʼ��
void LED_Init(void);

//��������ʼ��
void buzzer_Init(void);

//���濪ʼ(���� ��������)
void Warning_Start(void);

//����ֹͣ
void Warning_Stop(void);

#endif
