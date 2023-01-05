#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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


void KEY_Init(void);//IO��ʼ��
uint8_t KEY_Scan(uint8_t);  	//����ɨ�躯��					    
#endif
