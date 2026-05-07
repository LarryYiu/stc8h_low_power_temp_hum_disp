#ifndef __NTC_H__
#define __NTC_H__

#include "AppConfig.h"
#include "Config.h"
#include "ExtInt.h"
#include "GPIO.h"
#include "Misc.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_Exti.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_Timer.h"
#include "STC8H.h"

#ifndef NTC_RES
#define NTC_RES 10.0f
#endif  // NTC_RES in kOhms

#ifndef NTC_SAMPLE_NUM
#define NTC_SAMPLE_NUM 5.0f
#endif  // NTC_SAMPLE_NUM

#ifndef NTC_TABLE_SIZE
#define NTC_TABLE_SIZE 181
#endif  // NTC_TABLE_SIZE

extern u32 xdata time3IntNum;

void NTC_Config();

float NTC_GetResistance();

int16 NTC_GetTemp();

#endif  // __NTC_H__