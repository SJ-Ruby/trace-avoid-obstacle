#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "timer.h"
#include "tb6612.h"
#include "direction.h"
#include "tracking.h"
#include "ultrasonic.h"

extern u8 TIM2CH1_CAPTURE_STA; //输入捕获状态 
extern u16 TIM2CH1_CAPTURE_VAL;//输入捕获值

int main(void)
{	

	uart_init(72,9600);     //串口初始化为9600
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	     	//延时初始化
	LED_Init();		  	 	//初始化与LED连接的硬件接口    
	tb6612_Init();          //模块初始化
	TIM4_PWM_Init(999,0);   //900PWM频率=72000/1000=72khz
	Tracking_Init();
	Ultrasonic_Init();

	while(1)
	{	
		//Ultrasonic();
		Tracking();

	}
}

























