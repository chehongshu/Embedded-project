#ifndef _HC_SR04_H
#define _HC_SR04_H
#define module_interval 25    //���峬����ģ����շ���˼��(��λ��mm)
#define object_distance 100.0   //�������ľ���

void NVIC_Configuration(void);
void TIM_Configuration(void);
void GPIO_Configuration(void);
void RCC_Configuration(void);
float Sensor_using(void);
void _delay(void);

#endif

