#include "sys.h"
#include "delay.h"
//#include "usart.h"
#include "tim3_sg.h"
#include "led.h"
#include "key.h"
#include "railgun.h"
#include "hc06.h"
 
/************************************************
曲射电磁炮控制  

*板子前缘开始算距离*

************************************************/

uint8_t shoottimes=0;
uint8_t loadtimes=0;
uint8_t unloadtimes=0;
uint16_t shootDis=270;

int main(void)
{
	uint16_t sgpwmval=Angle_60;
	uint8_t dir=1;

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	// LED_Init();			     //LED端口初始化
	TIM3_PWM_Init(19999,71);	 //72分频。PWM频率=72000000/72/20000=50hz
	Railgun_Init();
    
    TIM_SetCompare3(TIM3,19999*Angle_90/20000);
    
    while(1)
    {
        delay_ms(2000);
        TIM_SetCompare3(TIM3,19999*Angle_45/20000);
        delay_ms(2000);
        TIM_SetCompare3(TIM3,19999*Angle_135/20000);
    }

}
