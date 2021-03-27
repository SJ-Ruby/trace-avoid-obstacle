#include "tracking.h"
#include "sys.h"
#include "direction.h"
void Tracking_Init(void){
	RCC->APB2ENR|=1<<3;    //使能PORTB-时钟	   	 
   	 
	GPIOB->CRH&=0X0000FFFF; 
	GPIOB->CRH|=0X88880000;//PA12 13 上拉输入

}
//0是碰到黑线
void Tracking(void){
	if(D_L==0)
		left(500,0);
	if(D_R==0)
		right(500,0);
	
	
}


