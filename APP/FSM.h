#ifndef __FSM_H__
#define __FSM_H__
#include "Config.h"
#include "TouchKey.h"

#include "ADC.h"
#include "BAT.h"
#include "HR202L.h"
#include "LCD_Seg.h"
#include "RTC.h"
#include "STC8G_H_Timer.h"
#include "NTC.h"
#include "Timer.h"
#include "UART.h"

typedef enum
{
    WAKE_UP_SOURCE_NONE = 0,
    WAKE_UP_SOURCE_RTC_1S, // just flip time column
    WAKE_UP_SOURCE_RTC_1M, // update time, hum, temp
    WAKE_UP_SOURCE_RTC_1H, // update battery lvl
    WAKE_UP_SOURCE_INT,    // enter ON mode
} FSM_WAKE_UP_SOURCE_t;

typedef void (*StateFunc_t)(void);

typedef struct
{
    StateFunc_t current;
} FSM_t;

void FSM_RUN();
void FSM_UpdateTempHum();
void FSM_FlipFlagDisplayTime();
void FSM_SetWakeUpSource(FSM_WAKE_UP_SOURCE_t source);

#endif // __FSM_H__