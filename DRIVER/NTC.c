#include "NTC.h"

#define __NTC__ P66
#define __INT__ P32
#define __CAP__ P65
#define __CAL__ P64

#define NTC_RES 10.0f
#define NTC_SAMPLE_NUM 5.0f

u32 xdata time3IntNum = 0;
idata GPIO_InitTypeDef GPIO_InitStructure;

#define ModeNTC(mode) \
    GPIO_FrqConfig(GPIO_P6, GPIO_Pin_6, mode, &GPIO_InitStructure);
#define ModeINT(mode) \
    GPIO_FrqConfig(GPIO_P3, GPIO_Pin_2, mode, &GPIO_InitStructure);
#define ModeCAP(mode) \
    GPIO_FrqConfig(GPIO_P6, GPIO_Pin_5, mode, &GPIO_InitStructure);
#define ModeCAL(mode) \
    GPIO_FrqConfig(GPIO_P6, GPIO_Pin_4, mode, &GPIO_InitStructure);

void NTC_Config()
{
    ExtInt_Config(EXT_INT0, EXT_MODE_Fall, Priority_0);
    ModeCAL(GPIO_HighZ);
    ModeCAP(GPIO_OUT_PP);
    ModeNTC(GPIO_HighZ);
    ModeINT(GPIO_HighZ);
    __NTC__ = 0;
    __INT__ = 0;
    __CAP__ = 0;
    __CAL__ = 0;
}

void __ALL_HiZ()
{
    ModeNTC(GPIO_HighZ);
    ModeCAL(GPIO_HighZ);
    ModeINT(GPIO_HighZ);
    // ModeCAP(GPIO_HighZ);
}

void __Discharge()
{
    ModeCAL(GPIO_OUT_PP);
    ModeNTC(GPIO_OUT_PP);
    ModeCAP(GPIO_OUT_PP);
    ModeINT(GPIO_OUT_PP);
    __NTC__ = 0;
    __INT__ = 0;
    __CAP__ = 0;
    __CAL__ = 0;

    delay_ms(10);
}

u32 __Charge(bit isNTC)
{
    u32 time = 0;
    __ALL_HiZ();
    // while (__CAP__ != 0);  // wait for the capacitor to be fully discharged
    if (isNTC)
    {
        ModeNTC(GPIO_OUT_PP);
        __NTC__ = 1;
    }
    else
    {
        ModeCAL(GPIO_OUT_PP);
        __CAL__ = 1;
    }

    Timer3_Run(1);
    while (!INT0);
    Timer3_Run(0);
    time = (time3IntNum * 65536) + ((u32)T3H * 256) + (u32)T3L;
    T3H = 0;
    T3L = 0;
    time3IntNum = 0;

    __Discharge();
    return time;
}

float NTC_GetResistance()
{
    u8 i;
    float resSum = 0.0f;

    __Charge(FALSE);

    for (i = 0; i < NTC_SAMPLE_NUM; i++)
    {
        resSum += NTC_RES * (float)__Charge(TRUE) / (float)__Charge(FALSE);
    }

    return (float)(resSum / NTC_SAMPLE_NUM);
}

void INT0_ISR_Handler(void) interrupt INT0_VECTOR { Timer3_Run(0); }