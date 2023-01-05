#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
// F103C8T6 ���İ�
// LED GPIO PC.13 ��ʼ��								  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PC13Ϊ�����.��ʹ������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.13
    
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PC.13 �����
    GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 �����
}
 
