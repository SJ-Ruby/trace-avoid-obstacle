#include "sys.h"
#include "led.h"
#include "timer.h"

u8 TIM2CH1_CAPTURE_STA=0;//输入捕获状态 
u16 TIM2CH1_CAPTURE_VAL;//输入捕获值

void TIM4_PWM_Init(u16 arr,u16 psc){
	RCC->APB1ENR|=1<<2;//TIM4时钟使能
	GPIOB->CRL&=0x00FFFFFF;//PB6 PB7 左 清除之前的设置
	GPIOB->CRL|=0xBB000000;//复用推挽
	TIM4->ARR=arr;//设定计数器的自动重装值
	TIM4->PSC=psc;//预分频器设置
	
	TIM4->CCMR1|=6<<4;//TIM4 CH1 PWM模式1 向上计数 
	TIM4->CCMR1|=1<<3;//CH1 预装载使能
	
	TIM4->CCMR1|=6<<12;//TIM4 CH2 
	TIM4->CCMR1|=1<<11;//CH2 预装载使能
	
	TIM4->CCER|=1;//OC1输出使能
	TIM4->CCER|=1<<4;
	
	TIM4->CR1=0x0080;//ARPE使能
	TIM4->CR1|=1;//使能计数器
}

void TIM2_Cap_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0; //TIM2 时钟使能ch1
	RCC->APB2ENR|=1<<2; //使能 PORTA 时钟 
	GPIOA->CRL&=0XFFFFFFF0; //PA0 清除之前设置 
	GPIOA->CRL|=0X00000004; //PA0 输入 
	GPIOA->ODR|=0<<0; //PA0 下拉
	TIM2->ARR=arr; //设定计数器自动重装值 
	TIM2->PSC=psc; //预分频器
	
	TIM2->CCMR1|=1; //CC1S=01 选择输入端 IC1 映射到 TI1 上
	//TIM2->CCMR1&=0; //无滤波器
	//TIM2->CCMR1&=~(0x3<<10); //IC2PS=00 配置输入分频,不分频
	
	//TIM2->CCER|=0<<1; //CC1P=0 上升沿捕获
	TIM2->CCER|=1<<0; //CC1E=1 允许捕获计数器的值到捕获寄存器中
	
	TIM2->DIER|=1<<1; //允许捕获中断
	TIM2->DIER|=1; //允许更新中断
	TIM2->CR1|=1; //使能定时器 2
	MY_NVIC_Init(2,0,TIM2_IRQn,2);//抢占 2，子优先级 0，组 2 
}


//定时器 2 中断服务程序
void TIM2_IRQHandler(void)
{ 
	u16 tsr;
	tsr=TIM2->SR;
	if((TIM2CH1_CAPTURE_STA&0X80)==0){//还未成功捕获
		if(tsr&0X01){//溢出
			if(TIM2CH1_CAPTURE_STA&0X40){//已经捕获到高电平了
	
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F){//高电平太长了
					TIM2CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH1_CAPTURE_STA++;
			} 
		}
		if(tsr&0x02){//捕获 1 发生捕获事件
			if(TIM2CH1_CAPTURE_STA&0X40) {//捕获到一个下降沿
				TIM2CH1_CAPTURE_STA|=0X80; //标记成功捕获到一次高电平脉宽
				TIM2CH1_CAPTURE_VAL=TIM2->CCR1;//获取当前的捕获值.
				TIM2->CCER&=~(1<<1); //CC1P=0 设置为上升沿捕获
				}		
			else { //还未开始,第一次捕获上升沿
				TIM2CH1_CAPTURE_VAL=0;
				TIM2CH1_CAPTURE_STA=0X40; //标记捕获到了上升沿
				TIM2->CNT=0; //计数器清空
				TIM2->CCER|=1<<1; //CC1P=1 设置为下降沿捕获
			} 
		} 
	}
	TIM2->SR=0;//清除中断标志位 
}	

