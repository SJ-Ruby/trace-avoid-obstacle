#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "timer.h"
#include "tb6612.h"
#include "direction.h"
#include "tracking.h"
#include "ultrasonic.h"

extern u8 TIM2CH1_CAPTURE_STA; //���벶��״̬ 
extern u16 TIM2CH1_CAPTURE_VAL;//���벶��ֵ

int main(void)
{	

	uart_init(72,9600);     //���ڳ�ʼ��Ϊ9600
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	delay_init(72);	     	//��ʱ��ʼ��
	LED_Init();		  	 	//��ʼ����LED���ӵ�Ӳ���ӿ�    
	tb6612_Init();          //ģ���ʼ��
	TIM4_PWM_Init(999,0);   //900PWMƵ��=72000/1000=72khz
	Tracking_Init();
	Ultrasonic_Init();

	while(1)
	{	
		//Ultrasonic();
		Tracking();

	}
}
























