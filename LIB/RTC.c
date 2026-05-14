#include "RTC.h"

bit B_1S = 0;
bit B_1M = 0;
bit B_1H = 0;

// void RTC_Config()
// {
//     X32KCR = 0xc0;  // Enable external 32.768 kHz crystal
//     while (!(X32KCR & 0x01))
//     {
//         RTCCFG &= ~(0x01 << 1);  // Set RTC clock source to external 32.768
//         kHz
//     }
//     RTCIF = 0x00;  // Clear RTC interrupt request flag
//     // RTCIEN = 0x78;  // Enable RTC interrupts for y, m, d, h, min, s
//     RTCIEN = 0x08;  // Enable RTC second interrupt only
//     RTCCR = 0x01;   // Enable RTC
// }

void RTC_Config(const void* timeIn)
{
    RTC_InitTypeDef RTC_InitStructure;
    RTC_InitStructure.RTC_Clock  = RTC_X32KCR; // RTC OSC selection, RTC_IRC32KCR, RTC_X32KCR
    RTC_InitStructure.RTC_Enable = ENABLE;     // RTC interrupt enable,   ENABLE, DISABLE
    if(timeIn != NULL)
    {
        RTC_InitStructure.RTC_Year    = 0;  // RTC y, 00~99, based on 2000
        RTC_InitStructure.RTC_Month   = 1;  // RTC m, 01~12
        RTC_InitStructure.RTC_Day     = 1;  // RTC d, 01~31
        RTC_InitStructure.RTC_Hour    = 17; // RTC h, 00~23
        RTC_InitStructure.RTC_Min     = 30; // RTC m, 00~59
        RTC_InitStructure.RTC_Sec     = 0;  // RTC s, 00~59
        RTC_InitStructure.RTC_ALAHour = 00; // RTC alarm, 00~23
        RTC_InitStructure.RTC_ALAMin  = 00; // RTC alarm, 00~59
        RTC_InitStructure.RTC_ALASec  = 00; // RTC alarm, 00~59
        RTC_InitStructure.RTC_ALASsec = 00; // RTC alarm 1/128 second, 00~127
    }
    else
    {
        RTC_InitStructure.RTC_Year    = 00; // RTC y, 00~99, based on 2000
        RTC_InitStructure.RTC_Month   = 4;  // RTC m, 01~12
        RTC_InitStructure.RTC_Day     = 15; // RTC d, 01~31
        RTC_InitStructure.RTC_Hour    = 5;  // RTC h, 00~23
        RTC_InitStructure.RTC_Min     = 30; // RTC m, 00~59
        RTC_InitStructure.RTC_Sec     = 00; // RTC s, 00~59
        RTC_InitStructure.RTC_ALAHour = 00; // RTC alarm, 00~23
        RTC_InitStructure.RTC_ALAMin  = 00; // RTC alarm, 00~59
        RTC_InitStructure.RTC_ALASec  = 00; // RTC alarm, 00~59
        RTC_InitStructure.RTC_ALASsec = 00; // RTC alarm 1/128 second, 00~127
    }
    RTC_InitStructure.RTC_Ssec = 00;
    RTC_Inilize(&RTC_InitStructure);
    RTCIEN = 0x18; // Enable RTC second and min interrupt
    NVIC_RTC_Init(RTC_SEC_INT | RTC_MIN_INT | RTC_HOUR_INT, Priority_0);
    // RTC_ALARM_INT/RTC_DAY_INT/RTC_HOUR_INT/RTC_MIN_INT/RTC_SEC_INT/RTC_SEC2_INT/RTC_SEC8_INT/RTC_SEC32_INT/DISABLE;
}

void RTC_SetTime(const RTC_Time_t* time)
{
    INIHOUR = time->hour;
    INIMIN  = time->minute;
    // INISEC  = time->second;
    INISSEC = 0;    // Not setting sub-second, default to 0
    RTCCFG |= 0x01; // Trigger mcu copy INI time registers to Real Time registers
}

void RTC_GetTime(RTC_Time_t* time)
{
    time->hour   = (u8)HOUR;
    time->minute = (u8)MIN;
    // time->second = SEC;
}

bit RTC_INT_1S()
{
    if(B_1S)
    {
        B_1S = FALSE;
        return TRUE;
    }
    return FALSE;
}

bit RTC_INT_1M()
{
    if(B_1M)
    {
        B_1M = FALSE;
        return TRUE;
    }
    return FALSE;
}

bit RTC_INT_1H()
{
    if(B_1H)
    {
        B_1H = FALSE;
        return TRUE;
    }
    return FALSE;
}

void RTC_On()
{
    RTCCR = 0x01;
    while(RTCCFG & 0x01)
    {
    }
}
void RTC_Off()
{
    RTCCR = 0x00;
}

void RTC_SecISR() interrupt RTC_VECTOR
{
    if(RTCIF & 0x08) // Determine whether it is the second interrupt
    {
        RTCIF &= ~0x08; // clear interrupt flag
        B_1S = TRUE;
        FSM_SetWakeUpSource(WAKE_UP_SOURCE_RTC_1S);
    }
    else if(RTCIF & 0x10)
    {
        RTCIF &= ~0x10; // clear interrupt flag
        B_1M = TRUE;
        FSM_SetWakeUpSource(WAKE_UP_SOURCE_RTC_1M);
    }
    else if(RTCIF & 0x20)
    {
        RTCIF &= ~0x20; // clear interrupt flag
        B_1H = TRUE;
        FSM_SetWakeUpSource(WAKE_UP_SOURCE_RTC_1H);
    }
}