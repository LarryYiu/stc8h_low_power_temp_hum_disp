#include "Bat.h"

u16 BAT_GetVoltage()
{
    u8 i      = 0;
    float res = 0.0f;
    ADC_PowerOn(ENABLE);
    Get_ADCResult(15);
    for(i; i < 5; i++)
    {
        res += 1.19f * 4096 / (float)Get_ADCResult(15);
    }
    res *= 2; // res / 5 * 10, /5 for average, *10 for voltage decimal

    ADC_PowerOn(DISABLE);
    return (u16)res;
}

u8 BAT_GetLevel(void* volt)
{
    if(volt != NULL)
    {
        if(*(u16*)volt >= 30)
            return 4;
        else if(*(u16*)volt >= 28)
            return 3;
        else if(*(u16*)volt >= 26)
            return 2;
        else if(*(u16*)volt >= 24)
            return 1;
        else
            return 0;
    }
    else
    {
        u16 voltage = BAT_GetVoltage();
        if(voltage >= 30)
            return 4;
        else if(voltage >= 28)
            return 3;
        else if(voltage >= 26)
            return 2;
        else if(voltage >= 24)
            return 1;
        else
            return 0;
    }
}