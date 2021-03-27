#include "sys.h"
#include "led.h"
#include "timer.h"

u8 TIM2CH1_CAPTURE_STA=0;//���벶��״̬ 
u16 TIM2CH1_CAPTURE_VAL;//���벶��ֵ

void TIM4_PWM_Init(u16 arr,u16 psc){
	RCC->APB1ENR|=1<<2;//TIM4ʱ��ʹ��
	GPIOB->CRL&=0x00FFFFFF;//PB6 PB7 �� ���֮ǰ������
	GPIOB->CRL|=0xBB000000;//��������
	TIM4->ARR=arr;//�趨���������Զ���װֵ
	TIM4->PSC=psc;//Ԥ��Ƶ������
	
	TIM4->CCMR1|=6<<4;//TIM4 CH1 PWMģʽ1 ���ϼ��� 
	TIM4->CCMR1|=1<<3;//CH1 Ԥװ��ʹ��
	
	TIM4->CCMR1|=6<<12;//TIM4 CH2 
	TIM4->CCMR1|=1<<11;//CH2 Ԥװ��ʹ��
	
	TIM4->CCER|=1;//OC1���ʹ��
	TIM4->CCER|=1<<4;
	
	TIM4->CR1=0x0080;//ARPEʹ��
	TIM4->CR1|=1;//ʹ�ܼ�����
}

void TIM2_Cap_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0; //TIM2 ʱ��ʹ��ch1
	RCC->APB2ENR|=1<<2; //ʹ�� PORTA ʱ�� 
	GPIOA->CRL&=0XFFFFFFF0; //PA0 ���֮ǰ���� 
	GPIOA->CRL|=0X00000004; //PA0 ���� 
	GPIOA->ODR|=0<<0; //PA0 ����
	TIM2->ARR=arr; //�趨�������Զ���װֵ 
	TIM2->PSC=psc; //Ԥ��Ƶ��
	
	TIM2->CCMR1|=1; //CC1S=01 ѡ������� IC1 ӳ�䵽 TI1 ��
	//TIM2->CCMR1&=0; //���˲���
	//TIM2->CCMR1&=~(0x3<<10); //IC2PS=00 ���������Ƶ,����Ƶ
	
	//TIM2->CCER|=0<<1; //CC1P=0 �����ز���
	TIM2->CCER|=1<<0; //CC1E=1 ���������������ֵ������Ĵ�����
	
	TIM2->DIER|=1<<1; //���������ж�
	TIM2->DIER|=1; //���������ж�
	TIM2->CR1|=1; //ʹ�ܶ�ʱ�� 2
	MY_NVIC_Init(2,0,TIM2_IRQn,2);//��ռ 2�������ȼ� 0���� 2 
}


//��ʱ�� 2 �жϷ������
void TIM2_IRQHandler(void)
{ 
	u16 tsr;
	tsr=TIM2->SR;
	if((TIM2CH1_CAPTURE_STA&0X80)==0){//��δ�ɹ�����
		if(tsr&0X01){//���
			if(TIM2CH1_CAPTURE_STA&0X40){//�Ѿ����񵽸ߵ�ƽ��
	
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F){//�ߵ�ƽ̫����
					TIM2CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH1_CAPTURE_STA++;
			} 
		}
		if(tsr&0x02){//���� 1 ���������¼�
			if(TIM2CH1_CAPTURE_STA&0X40) {//����һ���½���
				TIM2CH1_CAPTURE_STA|=0X80; //��ǳɹ�����һ�θߵ�ƽ����
				TIM2CH1_CAPTURE_VAL=TIM2->CCR1;//��ȡ��ǰ�Ĳ���ֵ.
				TIM2->CCER&=~(1<<1); //CC1P=0 ����Ϊ�����ز���
				}		
			else { //��δ��ʼ,��һ�β���������
				TIM2CH1_CAPTURE_VAL=0;
				TIM2CH1_CAPTURE_STA=0X40; //��ǲ�����������
				TIM2->CNT=0; //���������
				TIM2->CCER|=1<<1; //CC1P=1 ����Ϊ�½��ز���
			} 
		} 
	}
	TIM2->SR=0;//����жϱ�־λ 
}	
