/********************************************************************************************************

HC-SR04���������ģ��Ļ���ʹ�÷�����
	(1)����IO��TRIG������࣬������10us�ĸߵ�ƽ�ź�
	(2)ģ���Զ�����8��40KHz�ķ������Զ�����Ƿ����źŷ���
	(3)���źŷ��أ�ͨ��IO��ECHO���һ���ߵ�ƽ���ߵ�ƽ������ʱ����ǳ������ӷ��䵽���ص�ʱ��
	(4)���Ծ���=(�ߵ�ƽʱ��*����(340m/s))/2
	
********************************************************************************************************/



#ifndef __ULTRASONIC_H_
#define __ULTRASONIC_H_

#include "sys.h"

#define Trig PCout(10)
#define Echo //���벶�� Tim2_ch1

#define Sound_Velocity 0.034				//���٣�0.034 cm/us
#define Limit_Distance 20					//���ƾ��룬��λ����(cm)

double Distance(void);
void Ultrasonic_Init(void);
void Ultrasonic(void);
void Echo_Init(void);
void Trig_Init(void);
#endif