#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY_UP      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define KEY_DOWN    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define KEY_LEFT    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define KEY_RIGHT   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define KEY_MID     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define KEY_SET     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define KEY_RESET   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)

#define KEY_UP_PRES     1
#define KEY_DOWN_PRES   2
#define KEY_LEFT_PRES   3
#define KEY_RIGHT_PRES  4
#define KEY_MID_PRES    5
#define KEY_SET_PRES    6
#define KEY_RESET_PRES  7


void KEY_Init(void);//IO初始化
uint8_t KEY_Scan(uint8_t);  	//按键扫描函数					    
#endif
