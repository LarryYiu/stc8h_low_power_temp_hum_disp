#include "HR202L.h"

#define __PWM_P__ P60
#define __PWM_N__ P61
#define __PIN_ADC__ P62
#define ADC_CHANNEL 6

void HR_Config()
{
    P6_MODE_IN_HIZ(GPIO_Pin_2);
    ADC_Config(31, 0, 1, ADC_SPEED_2X16T, ADC_RIGHT_JUSTIFIED, ENABLE, -1);
    ADC_CONTR |= 0x06;  // Channel 6
    ADC_CONTR |= 0x0f;  // Channel 15, 1.19V
}

void __InitIO()
{
    P6_MODE_IN_HIZ(GPIO_Pin_2);
    P6_MODE_OUT_PP(GPIO_Pin_0 | GPIO_Pin_1);
    __PWM_N__ = 0;
    __PWM_P__ = 0;
}

float __ReadADC()
{
    u16 adcVal;
    __InitIO();
    __PWM_P__ = 1;
    __PWM_N__ = 0;
    delay_ms(1);
    adcVal = Get_ADCResult(ADC_CHANNEL);
    __PWM_P__ = 0;
    __PWM_N__ = 1;
    delay_ms(1);

    __PWM_N__ = 0;

    return adcVal;
}

float HR_GetResistance()
{
    idata u8 i;
    idata u16 vals[MAX_HUM_NUM];
    idata float avg;
    idata float res;

    ADC_PowerOn(ENABLE);
    __ReadADC();
    for (i = 0; i < MAX_HUM_NUM; i++)
    {
        vals[i] = __ReadADC();
        // printf("ADC Value %bu: %u\n", i, vals[i]);
    }

    ADC_PowerOn(DISABLE);

    avg = ADC_AverageFilter(vals, MAX_HUM_NUM, 1);
    // printf("Average ADC Value: %.2f\n", avg);

    res = 39.0f * (4096L - avg) / avg;
    return ((1000.0f + 0.47f) * res - 470.0f) / (1000.0f - res);
}
// clang-format off
code const u16 __TEMP10X_INDEX__[13] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600};
code const u16 __HUM10X_INDEX__[15] = {200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900};
code const float __RES_HUM_TEMP_LOOKUP__[13][15] =
{
        //20        25          30      35       40     45      50      55      60      65      70      75      80      85      90
/*0*/   {25600,	    12800,		6400,	2900,	1400,	700,	370,	190,	105,	62,		38,		23,		15.5,	10.5,	7.1},
/*5*/   {20000,	    10000,		4600,	2100,	1000,	500,	260,	140,	80,		48,		30,		18,		12,		8.2,	5.3},
/*10*/  {14000,	    7000,		3200,	1500,	750,	380,	200,	110,	62,		37,		24,		15,		10,		6.8,	4.7},
/*15*/  {10000,	    5000,		2300,	1100,	540,	280,	150,	84,		50,		30,		19,		12,		8.0,	5.5,	4.0},
/*20*/  {6700,	    3400,		1750,	850,	420,	210,	115,	64,		39,		24,		15.5,	10,		7.0,	4.8,	3.3},
/*25*/  {5000,	    2600,		1300,	630,	310,	160,	87,		49,		31,		19.5,	13,		8.4,	5.7,	4.0,	2.8},
/*30*/  {3900,	    1900,		970,	460,	235,	125,	69,		39,		25,		16,		10.5,	7.2,	5.0,	3.5,	2.5},
/*35*/  {3000,	    1500,		740,	380,	190,	100,	56,		33,		20,		13,		9.0,	6.2,	4.3,	3.1,	2.2},
/*40*/  {2400,	    1100,		570,	280,	140,	78,		45,		27,		17.5,	11.5,	8.0,	5.6,	3.9,	2.8,	2.0},
/*45*/  {1750,	    880,		420,	210,	110,	64,		38,		24,		15,		10,		7.0,	4.9,	3.4,	2.4,	1.8},
/*50*/  {1450,	    700,		340,	170,	88,		50,		31,		19.5,	13,		8.6,	6.0,	4.2,	3.0,	2.1,	1.55},
/*55*/  {1150,	    560,		270,	150,	70,		41,		25,		17,		11,		7.6,	5.4,	3.8,	2.7,	1.9,	1.4},
/*60*/  {970,	    450,		215,	130,	57,		34,		21,		14,		9.4,	6.8,	4.8,	3.4,	2.5,	1.8,	1.3}
};
// clang-format on

// u16 HR_GetHum(const int16* temperature)
// {
//     float res = HR_GetResistance();
//     // add compensation
//     if (res > 25600 || res < 1.3 || *temperature > 600 || *temperature < 0)
//     {
//         return 0xFFFF;  // out of capable range
//     }
//     else
//     {
//         float xdata humArr[15];
//         u8 i, j;
//         for (i = 0; i < 12; i++)
//         {
//             if (*temperature < __TEMP10X_INDEX__[i])
//                 break;
//         }
//         i--;
//         for (j = 0; j < 15; j++)
//         {
//             humArr[j] =
//                 __RES_HUM_TEMP_LOOKUP__[i][j] +
//                 (__RES_HUM_TEMP_LOOKUP__[i][j] -
//                  __RES_HUM_TEMP_LOOKUP__[i + 1][j]) *
//                     ((float)(*temperature - __TEMP10X_INDEX__[i]) /
//                      (float)(__TEMP10X_INDEX__[i + 1] -
//                      __TEMP10X_INDEX__[i]));
//         }
//         for (i = 0; i < 15; i++)
//         {
//             if (res > humArr[i])
//                 break;
//         }
//         if (i == 0 || i == 15)
//         {
//             return 0xffff;  // out of capable range
//         }
//         i--;
//         return __HUM10X_INDEX__[i] +
//                (u16)((float)(__HUM10X_INDEX__[i + 1] - __HUM10X_INDEX__[i]) *
//                      (humArr[i] - res) / (humArr[i] - humArr[i + 1]));
//     }
// }

u16 HR_GetHum(const int16* temperature)
{
    float idata res = HR_GetResistance();
    // add compensation
    if (res > 25600 || res < 1.3 || *temperature > 600 || *temperature < 0)
    {
        return 0xFFFF;  // out of capable range
    }
    else
    {
        float idata humHigh, humLow;
        u8 i, j;
        for (i = 0; i < 12; i++)
        {
            if (*temperature < __TEMP10X_INDEX__[i])
                break;
        }
        i--;
        for (j = 0; j < 15; j++)
        {
            humLow =
                __RES_HUM_TEMP_LOOKUP__[i][j] +
                (__RES_HUM_TEMP_LOOKUP__[i][j] -
                 __RES_HUM_TEMP_LOOKUP__[i + 1][j]) *
                    ((float)(*temperature - __TEMP10X_INDEX__[i]) /
                     (float)(__TEMP10X_INDEX__[i + 1] - __TEMP10X_INDEX__[i]));

            if (res > humLow)
            {
                break;
            }
            else
            {
                humHigh = humLow;
            }
        }
        if (j == 0 || j == 15)
        {
            return 0xffff;  // out of capable range
        }
        j--;
        return __HUM10X_INDEX__[j] +
               (u16)((float)(__HUM10X_INDEX__[j + 1] - __HUM10X_INDEX__[j]) *
                     (humHigh - res) / (humHigh - humLow));
    }
}