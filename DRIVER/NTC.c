#include "NTC.h"

#define __NTC__ P66
#define __INT__ P32
#define __CAP__ P65
#define __CAL__ P64

u32 xdata NTC_Time = 0;
idata GPIO_InitTypeDef GPIO_InitStructure;

#define ModeNTC(mode) GPIO_FrqConfig(GPIO_P6, GPIO_Pin_6, mode, &GPIO_InitStructure);
#define ModeINT(mode) GPIO_FrqConfig(GPIO_P3, GPIO_Pin_2, mode, &GPIO_InitStructure);
#define ModeCAP(mode) GPIO_FrqConfig(GPIO_P6, GPIO_Pin_5, mode, &GPIO_InitStructure);
#define ModeCAL(mode) GPIO_FrqConfig(GPIO_P6, GPIO_Pin_4, mode, &GPIO_InitStructure);

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
    if(isNTC)
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
    while(!INT0)
        ;
    Timer3_Run(0);
    time     = (NTC_Time * 65536) + ((u32)T3H * 256) + (u32)T3L;
    T3H      = 0;
    T3L      = 0;
    NTC_Time = 0;

    __Discharge();
    return time;
}

float NTC_GetResistance()
{
    u8 i;
    float resSum = 0.0f;

    __Charge(FALSE);

    for(i = 0; i < NTC_SAMPLE_NUM; i++)
    {
        resSum += NTC_RES * (float)__Charge(TRUE) / (float)__Charge(FALSE);
    }

    return (float)(resSum / NTC_SAMPLE_NUM);
}

// clang-format off
code const float __RES_TEMP_LOOKUP__[NTC_TABLE_SIZE] =
{	739.500, 705.664, 669.165, 631.466, 593.686, //-55 ~ -51℃
	556.644, 520.911, 486.858, 454.704, 424.553, 396.462, 370.283, 346.049, 323.623, 302.889,//-50 ~ -41℃
	283.730, 266.022, 249.649, 234.498, 220.466, 207.454, 195.372, 184.139, 173.681, 163.931,//-40 ~ -31℃
	154.827, 146.315, 138.347, 130.877, 123.866, 117.280, 111.084, 105.252,  99.756,  94.573,//-30 ~ -21℃
	 89.682,  85.063,  80.699,  76.574,  72.672,  68.982,  65.489,  62.183,  59.052,  56.087,//-20 ~ -11℃
	 53.280,  50.620,  48.100,  45.712,  43.450,  41.306,  39.274,  37.349,  35.524,  33.795,//-10 ~ - 1℃
	 32.116,  30.601,  29.128,  27.732,  26.408,  25.152,  23.962,  22.833,  21.762,  20.746,//  0 ~   9℃
	 19.783,  18.868,  18.000,  17.177,  16.395,  15.652,  15.947,  14.277,  13.641,  13.036,// 10 ~  19℃
	 12.461,  11.915,  11.395,  10.901,  10.431,  10.000,   9.557,   9.151,   8.765,   8.397,// 20 ~  29℃
	  8.047,   7.712,   7.394,   7.090,   6.800,   6.523,   6.259,   6.008,   5.767,   5.537,// 30 ~  39℃
	  5.318,   5.108,   4.907,   4.716,   4.532,   4.357,   4.189,   4.029,   3.875,   3.728,// 40 ~  49℃
	  3.588,   3.453,   3.324,   3.200,   3.081,   2.968,   2.859,   2.754,   2.654,   2.558,// 50 ~  59℃
	  2.466,   2.377,   2.293,   2.211,   2.133,   2.058,   1.986,   1.917,   1.850,   1.786,// 60 ~  69℃
	  1.725,   1.666,   1.610,   1.555,   1.503,   1.452,   1.404,   1.358,   1.313,   1.270,// 70 ~  79℃
	  1.228,   1.189,   1.150,   1.113,   1.078,   1.044,   1.011,   0.979,   0.949,   0.919,// 80 ~  89℃
	  0.890,   0.864,   0.837,   0.812,   0.787,   0.763,   0.741,   0.718,   0.697,   0.676,// 90 ~  99℃
	  0.657,   0.637,   0.619,   0.601,   0.583,   0.566,   0.550,   0.534,   0.519,   0.505,//100 ~ 109℃
	  0.491,   0.478,   0.463,   0.450,   0.438,   0.426,   0.414,   0.403,   0.392,   0.381,//110 ~ 119℃
	  0.371,   0.361,   0.351,   0.341,   0.332,   0.324,	 //120 ~ 125℃
};
// clang-format on

int16 NTC_GetTemp()
{
    idata u8 i;
    idata float resSum = 0.0f;
    idata float res    = 0.0f;
    __Charge(FALSE);

    for(i = 0; i < NTC_SAMPLE_NUM; i++)
    {
        resSum += NTC_RES * (float)__Charge(TRUE) / (float)__Charge(FALSE);
    }

    res = (float)(resSum / NTC_SAMPLE_NUM);
    i   = BinarySearch(__RES_TEMP_LOOKUP__, NTC_TABLE_SIZE, res);

    // clang-format off
    if (i != 0xff)
    {
        // Linear interpolation

        // temp = tempLow + (res - resLow) * (tempHigh - tempLow) / (resHigh -resLow)
        return (int16)((((float)i - 55.0f) 
        + (__RES_TEMP_LOOKUP__[i] - res) 
        / (__RES_TEMP_LOOKUP__[i] - __RES_TEMP_LOOKUP__[i + 1])) 
        * 10.0f);
    } // clang-format on
    else
    {
        return 1260; // out of range, return max temp
    }
}

void INT0_ISR_Handler(void) interrupt INT0_VECTOR
{
    Timer3_Run(0);
}

void NTC_IncrementTimer()
{
    NTC_Time++;
}