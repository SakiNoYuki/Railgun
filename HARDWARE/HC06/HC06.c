#include "sys.h"
#include "HC06.h"
#include "delay.h"

#include "tim3_sg.h"

extern uint16_t shootDis;

#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
 
 /************
    橙色---G
    黄色---3.3
    棕色---A9
    红色---A10
***************/
//////////////////////////////////////////////////////////////////  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	 


/////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t GP;
uint8_t Get;
int32_t T;

float set_angle;
extern uint8_t shoottimes;
extern uint8_t loadtimes;
extern uint8_t unloadtimes;


void uart_init(u32 bound){
  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


int USART1_IRQHandler(void)                	//串口1中断服务程序
	{
//	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif

    Get=USART_ReceiveData(USART1);
//	  if(Get=='1')GP=1;
//		if(Get=='2')GP=2;
//		if(Get=='3')GP=3;
//		if(Get=='4')GP=4;
 
		 switch(Get)
		 {
             case 'A':shoottimes=1;break;
             case 'Y':loadtimes=1;break;
             case 'Z':unloadtimes=1;break;
             case '0':
             {
                 TIM_SetCompare3(TIM3,19999*Angle_90/20000);
                 TIM_SetCompare4(TIM3,19999*(500+20*8500/180)/20000);
             };break;
             case 'S':TIM_SetCompare3(TIM3,19999*Angle_90/20000);break;
             case 'C':TIM_SetCompare4(TIM3,19999*Angle_90/20000);break;
             case '2':TIM_SetCompare4(TIM3,19999*Angle_135/20000);break;
             case '4':TIM_SetCompare3(TIM3,19999*Angle_135/20000);break;
             case '6':TIM_SetCompare3(TIM3,19999*Angle_45/20000);break;
             case '8':TIM_SetCompare4(TIM3,19999*Angle_45/20000);break;
             case 'K':shootDis=270;break;
             case 'k':shootDis=200;break;             
		 }
	

#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	
