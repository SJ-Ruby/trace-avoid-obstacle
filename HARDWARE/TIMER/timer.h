#ifndef __TIMER_H__
#define __TIMER_H__
#include "sys.h"
#define PWM_VAL1 TIM4->CCR1//右轮
#define PWM_VAL2 TIM4->CCR2
void TIM4_PWM_Init(u16 arr,u16 psc);
//void TIM3_Int_Init(u16 arr,u16 psc);
//void TIM3_IRQHandler(void);//定时器3中断服务函数
void TIM2_Cap_Init(u16 arr,u16 psc);
#endif
