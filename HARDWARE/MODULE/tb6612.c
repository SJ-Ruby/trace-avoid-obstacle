#include "sys.h"
#include "tb6612.h"
//��������Ϊ���
void tb6612_Init(void)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	   	  	 
	GPIOB->CRL&=0X00FFFFFF;//����
	GPIOB->CRH&=0XFFFF0000; 
	
	GPIOB->CRL|=0x33000000;
	
	GPIOB->CRH|=0X00003333;//PB6 7 8 9 10 11 �����������   	 
    
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
	
}