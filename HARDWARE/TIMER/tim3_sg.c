#include "tim3_sg.h"
#include "led.h"
#include "usart.h"


//////////////////////////////////////////////////////////////////////////////////	 
//  TIM定时器 驱动代码
//  180度舵机 PWM频率=50Hz
//  使用 TIM3 定时器 CH3 CH4 通道
//  TIM3 CH3 -> PB.0
//  TIM3 CH4 -> PB.1
//********************************************************************************
//V1.0 50Hz PWM驱动									  
//////////////////////////////////////////////////////////////////////////////////  

   
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(uint16_t arr,uint16_t psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设					 
}


//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
        {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
        }
}


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	 
   //设置该引脚为复用输出功能,输出TIM3 CH3 CH4的PWM脉冲波形	GPIOB.0 GPIOB.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
    
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
    
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}


/*
//舵机PWM初始化
//PWM=50Hz
void TIM3_Steering_gear_Init(void)
{
    TIM3_PWM_Init(19999,71);	 //72分频。PWM频率=72000000/72/20000=50hz
}


int TIM3_Steering_gear_ON(uint8_t sg_select)
{
}


int TIM3_Steering_gear_OFF(uint8_t sg_select)
{
}


//舵机角度设置
//优先使用校准过的角度
int TIM3_Steering_gear_Angle_Set(uint8_t sg_select, uint8_t angle)
{
    if ((angle<0)|(angle>180)) return 1;
    if ((sg_select<0)|(sg_select>4)) return 1;
    
    switch(sg_select)
    {
        case 1:  ;break;
        case 2:  ;break;
        case 3:  ;break;
        case 4:  ;break;
    }
    switch(angle)
    {
        case 180:   sg_select(TIM3,19999* Angle_180 /20000); break;
        case 135:   sg_select(TIM3,19999* Angle_135 /20000); break;
        case 90:    sg_select(TIM3,19999* Angle_90 /20000);  break;
        case 45:    sg_select(TIM3,19999* Angle_45 /20000);  break;
        case 0:     sg_select(TIM3,19999* Angle_0 /20000);   break;
        default :   sg_select(TIM3,19999* (Angle_0 + (Angle_180 - Angle_0)*angle) /20000);   break;
    }
}


//舵机角度A到角度B循环
//速度恒定
int TIM3_Steering_gear_Angle_AB(uint8_t sg_select, uint8_t angle_A, uint8_t angle_B)
{
    if ((angle_A<0)|(angle_A>180)|(angle_B<0)|(angle_B>180)) return 1;
}

*/