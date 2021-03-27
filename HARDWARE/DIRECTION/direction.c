#include "direction.h"
#include "tb6612.h"
#include "timer.h"
#include "sys.h"
#include "delay.h"

#define ERROR 100

void corotation(void){//正转
	AIN1=BIN1=1;
	AIN2=BIN2=0;
}
void inversion(void){//反转
	AIN1=BIN1=0;
	AIN2=BIN2=1;
}
void forward(u16 arr){
	PWM_VAL1=arr+ERROR;//右轮
	PWM_VAL2=arr;
	corotation();
	//delay_ms(3000);
}
void right(u16 arr,u16 offset){
	PWM_VAL1=arr+ERROR+offset;
	PWM_VAL2=0;
	corotation();
	//delay_ms(1000);
}
void left(u16 arr,u16 offset){
	PWM_VAL1=0;
	PWM_VAL2=arr+offset;
	corotation();
	//delay_ms(1000);
}
void backward(u16 arr){
	PWM_VAL1=arr+ERROR;
	PWM_VAL2=arr;
	inversion();
	//delay_ms(1000);
}
