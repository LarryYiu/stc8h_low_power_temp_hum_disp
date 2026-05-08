#ifndef __HR202L_H__
#define __HR202L_H__

#include "ADC.h"
#include "Config.h"
#include "STC8G_H_ADC.h"
#include "STC8G_H_Delay.h"
#include "STC8H.h"

#ifndef MAX_HUM_NUM
#define MAX_HUM_NUM 7
#endif

void HR_Config();

float HR_GetResistance();

u16 HR_GetHum(const int16* temperature);

#endif  // __HR202L_H__