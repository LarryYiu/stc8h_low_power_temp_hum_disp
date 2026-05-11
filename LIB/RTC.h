#ifndef __RTC_H__
#define __RTC_H__

#include "Config.h"
#include "STC8G_H_NVIC.h"
#include "STC8H.h"
#include "STC8H_RTC.h"

#define RTC_BASE_YEAR 2000

extern bit B_1S;
extern bit B_1M;

typedef struct
{
    u8 hour;    // 0-23
    u8 minute;  // 0-59
    u8 second;  // 0-59
} RTC_Time_t;

void RTC_Config(const void* timeIn);

/**
 * @brief Set the RTC time, be aware that the year is represented as a two-digit
 * value (0-99) corresponding to the last two digits of the year (e.g., 23 for
 * 2023). This function does not extend the register access.
 *
 * @param time Pointer to an RTC_Time_t structure containing the time to set
 */
void RTC_SetTime(const RTC_Time_t* time);

void RTC_GetTime(RTC_Time_t* time);

#endif  // __RTC_H__