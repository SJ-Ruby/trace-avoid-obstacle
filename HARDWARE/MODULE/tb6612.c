#include "sys.h"
#include "tb6612.h"
//配置引脚为输出
void tb6612_Init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   	  	 
	GPIOB->CRL&=0X00FFFFFF;//清零
	GPIOB->CRH&=0XFFFF0000; 
	
	GPIOB->CRL|=0x33000000;
	
	GPIOB->CRH|=0X00003333;//PB6 7 8 9 10 11 复用推挽输出   	 
    
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
	
}
