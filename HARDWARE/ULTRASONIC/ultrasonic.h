/********************************************************************************************************

HC-SR04超声波测距模块的基本使用方法：
	(1)采用IO口TRIG触发测距，给至少10us的高电平信号
	(2)模块自动发送8个40KHz的方波，自动检测是否有信号返回
	(3)有信号返回，通过IO口ECHO输出一个高电平，高电平持续的时间就是超声波从发射到返回的时间
	(4)测试距离=(高电平时间*声速(340m/s))/2
	
********************************************************************************************************/



#ifndef __ULTRASONIC_H_
#define __ULTRASONIC_H_

#include "sys.h"

#define Trig PCout(10)
#define Echo //输入捕获 Tim2_ch1

#define Sound_Velocity 0.034				//声速，0.034 cm/us
#define Limit_Distance 20					//限制距离，单位厘米(cm)

double Distance(void);
void Ultrasonic_Init(void);
void Ultrasonic(void);
void Echo_Init(void);
void Trig_Init(void);
#endif
