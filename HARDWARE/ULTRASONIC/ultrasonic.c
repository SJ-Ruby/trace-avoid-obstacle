#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "ultrasonic.h"
#include "delay.h"
#include "direction.h"
#include "pid.h"
extern u8 TIM2CH1_CAPTURE_STA;//输入捕获状态 
extern u16 TIM2CH1_CAPTURE_VAL;//输入捕获值

void Ultrasonic_Init(void){
	Trig_Init();
	Echo_Init();
	TIM2_Cap_Init(0xffff,72-1);
	uart_init(72, 9600);
}

double Distance(void){
	double temp=0;
	double rate;
	PID pid;
	temp=TIM2CH1_CAPTURE_STA&0X3F;
	temp*=65536; //溢出时间总和
	temp+=TIM2CH1_CAPTURE_VAL; //得到总的高电平时间
	TIM2CH1_CAPTURE_STA=0; //开启下一次捕获
	
	Pid_Init(&pid,0.6,0,0);
	temp*=Sound_Velocity/2;
	printf("distance:%f cm\r\n",temp);
	
	rate=Pid_Position(temp-15,&pid);
	printf("rate:%f \r\n",rate);
	return rate;
}

void Ultrasonic(void){
	double rate;
	Trig=1;
	delay_us(15);
	Trig=0;
	if(TIM2CH1_CAPTURE_STA&0x80){
		rate=Distance();
		if(rate<0) {
			backward(700*rate/-10.0);
		} else if(rate>0) {
			forward(700*rate/10.0);
		} else {
			forward(0);
		}

		TIM2CH1_CAPTURE_STA=0;
	}
	
}


void Trig_Init(void){
	RCC->APB2ENR |= 1<<4;//使能时钟C
	GPIOC->CRH &= 0xfffff0ff;//pc10
	GPIOC->CRH |= 0x00000300;//推挽输出
	Trig=0;	
}

void Echo_Init(void){
	RCC->APB2ENR |= 1<<2;//pa0
	GPIOA->CRL&=0xfffffff0;
	GPIOA->CRL|=0x00000008;
	GPIOA->ODR &=~1;//配置下拉 检测电平变化
	//PAin(0)=0;//下拉
}




