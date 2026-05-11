#ifndef __BAT_H__
#define __BAT_H__
#include "Config.h"
#include "STC8G_H_ADC.h"

u16 BAT_GetVoltage();

u8 BAT_GetLevel(void* volt);
#endif  // __BAT_H__