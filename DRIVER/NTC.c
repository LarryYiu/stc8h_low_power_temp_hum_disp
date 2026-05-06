#include "NTC.h"

#define __NTC__ P66
#define __INT__ P32
#define __CAP__ P65
#define __CAL__ P64

#define NTC_RES 10.0f
#define NTC_SAMPLE_NUM 5.0f

u16 xdata time1IntNum = 0;
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
    // ModeCAL(GPIO_HighZ);
    ModeCAP(GPIO_OUT_PP);
    // ModeNTC(GPIO_HighZ);
    // ModeINT(GPIO_HighZ);
    // __NTC__ = 0;
    // __INT__ = 0;
    // __CAP__ = 0;
    // __CAL__ = 0;
}

void __ALL_HiZ()
{
    ModeNTC(GPIO_HighZ);
    ModeCAL(GPIO_HighZ);
    ModeINT(GPIO_HighZ);
}

void __Discharge()
{
    ModeCAL(GPIO_OUT_PP);
    ModeNTC(GPIO_OUT_PP);
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
    if (isNTC)
    {
        ModeNTC(GPIO_OUT_PP);
        ModeCAL(GPIO_HighZ);
        __NTC__ = 1;
    }
    else
    {
        ModeCAL(GPIO_OUT_PP);
        ModeNTC(GPIO_HighZ);
        __CAL__ = 1;
    }
    ModeINT(GPIO_HighZ);

    time1IntNum = 0;
    TR1 = 1;
    printf("await int0\r\n");
    while (!INT0);
    printf("int0 triggered\r\n");
    TR1 = 0;
    // printf("time1IntNum: %u\r\n", time1IntNum);
    time = ((u32)time1IntNum * 65536) + ((u32)TH1 * 256) + (u32)TL1;
    TH1 = 0;
    TL1 = 0;
    time1IntNum = 0;

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

void INT0_ISR_Handler(void) interrupt INT0_VECTOR
{
    printf("time1IntNum: %u\r\n", time1IntNum);
}