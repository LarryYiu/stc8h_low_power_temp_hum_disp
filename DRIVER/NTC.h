#ifndef __NTC_H__
#define __NTC_H__

#include "Config.h"
#include "ExtInt.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_Exti.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_Timer.h"
#include "STC8H.h"

extern u32 xdata time3IntNum;

void NTC_Config();

float NTC_GetResistance();

u32 __Charge(bit isNTC);

#endif  // __NTC_H__