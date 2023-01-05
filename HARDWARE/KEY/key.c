#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"


//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
                                   GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.1-7
}


//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//注意此函数有响应优先级,KEY_RESET优先级最高!
uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//按键按松开标志
	if(mode) key_up=1;  //支持连按
	if(key_up&&(KEY_RESET == 0||KEY_UP == 0||KEY_DOWN == 0||KEY_LEFT == 0||
                KEY_RIGHT == 0||KEY_MID == 0||KEY_SET == 0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY_RESET == 0)return KEY_RESET_PRES;
		else if(KEY_UP == 0)return KEY_UP_PRES;
		else if(KEY_DOWN == 0)return KEY_DOWN_PRES;
        else if(KEY_LEFT == 0)return KEY_LEFT_PRES;
        else if(KEY_RIGHT == 0)return KEY_RIGHT_PRES;
        else if(KEY_MID == 0)return KEY_MID_PRES;
        else if(KEY_SET == 0)return KEY_SET_PRES;
	}else if(KEY_RESET == 1||KEY_UP == 1||KEY_DOWN == 1||KEY_LEFT == 1||
             KEY_RIGHT == 1||KEY_MID == 1||KEY_SET == 1) key_up=1; 	    
 	return 0;// 无按键按下
}
