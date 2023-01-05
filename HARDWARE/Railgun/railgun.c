#include "sys.h"
#include "delay.h"
#include "tim3_sg.h"
#include "led.h"
#include "key.h"
#include "railgun.h"

void Railgun_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;				 //����ڿ��� -->PB.10-11 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.10-11
    
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);						 //PB.10 �����
    GPIO_ResetBits(GPIOB,GPIO_Pin_11);						 //PB.11 �����
}


void Railgun_Load(void)
{
    for(uint16_t i=8500;i>6000;i-=100)
    {
        TIM_SetCompare4(TIM3,19999*(500+20*i/180)/20000);
        delay_ms(10);
    }
    delay_ms(500);
}


void Railgun_Unload(void)
{
    TIM_SetCompare4(TIM3,19999*(500+20*13500/180)/20000);
    delay_ms(500);
    TIM_SetCompare4(TIM3,19999*(500+20*8500/180)/20000);
}


void Railgun_Charge(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
    delay_ms(50);
    GPIO_SetBits(GPIOB,GPIO_Pin_10);
}


void Railgun_Stop_Charge(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
    delay_ms(50);
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}


void Railgun_Shoot(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
    delay_ms(50);
    GPIO_SetBits(GPIOB,GPIO_Pin_11);
    delay_ms(50);
    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
    delay_ms(500);
    TIM_SetCompare4(TIM3,19999*(500+20*8500/180)/20000);
}