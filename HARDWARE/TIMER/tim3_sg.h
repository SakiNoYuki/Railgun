#ifndef __TIM3_SG_H
#define __TIM3_SG_H
#include "sys.h"


//角度校准 占空比单位us 一个周期20ms
#define Angle_180   2300
#define Angle_135   2000
#define Angle_90    1500
#define Angle_45    1000
#define Angle_0     700

#define Angle_30    833
#define Angle_60    1167
#define Angle_120   1833
#define Angle_150   2166

#define Angle_75    1333

#define SG1 ((SG_Select_TypeDef*)TIM_SetCompare1)
#define SG2 TIM_SetCompare2
#define SG3 TIM_SetCompare3
#define SG4 TIM_SetCompare4

typedef struct{
}SG_Select_TypeDef;


void TIM3_Int_Init(uint16_t arr,uint16_t psc);
void TIM3_PWM_Init(uint16_t arr,uint16_t psc);

void TIM3_Steering_gear_Init(void);
int TIM3_Steering_gear_ON(uint8_t sg_select);
int TIM3_Steering_gear_OFF(uint8_t sg_select);
int TIM3_Steering_gear_Angle_Set(uint8_t sg_select, uint8_t angle);
int TIM3_Steering_gear_Angle_AB(uint8_t sg_select, uint8_t angle_A, uint8_t angle_B);
#endif
