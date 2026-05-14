#include "AppConfig.h"
#include "STC8G_H_Timer.h"
#include "TouchKey.h"
#include "FSM.h"

u32 xdata time0IntNum = 0;

// disabled since INT0 using
void Timer0_ISR_Handler(void) interrupt TMR0_VECTOR {}

void Timer1_ISR_Handler(void) interrupt TMR1_VECTOR
{
    time0IntNum++;
    if(time0IntNum >= 1999)
    {
        time0IntNum = 0;
        FSM_UpdateTempHum();
    }
    if(time0IntNum % TIMER0_INTERVAL_MS == 0)
    {
        TouchKey_Scan();
    }
    if(time0IntNum % SETTING_MODE_TIME_FLASHING_INTERVAL_MS == 0)
    {
        FSM_FlipFlagDisplayTime();
    }
}

// disabled since uart using this timer for baud rate generation.
void Timer2_ISR_Handler(void) interrupt TMR2_VECTOR {}

void Timer3_ISR_Handler(void) interrupt TMR3_VECTOR
{
    NTC_IncrementTimer();
}

void Timer4_ISR_Handler(void) interrupt TMR4_VECTOR {}
