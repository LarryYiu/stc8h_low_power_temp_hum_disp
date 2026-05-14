#include "ADC.h"
#include "AppSetup.h"
#include "BAT.h"
#include "Config.h"
#include "HR202L.h"
#include "LCD_Seg.h"
#include "RTC.h"
#include "FSM.h"

void OnShortPress(u8 keyIndex)
{
    printf("%bu short\n", keyIndex);
}

void OnLongPress(u8 keyIndex)
{
    printf("%bu long\n", keyIndex);
}

void main()
{
    App_Init();
    EA = 1;
    printf("System Initialized\r\n");
    while(1)
    {
        // if(TK_Ready)
        // {
        //     TK_Ready = FALSE;
        //     TouchKey_Event(0, TRUE, OnShortPress, OnLongPress);
        //     TouchKey_Event(1, TRUE, OnShortPress, OnLongPress);
        //     TouchKey_Event(4, TRUE, OnShortPress, OnLongPress);
        //     TouchKey_Event(3, TRUE, OnShortPress, OnLongPress);
        // }

        // touch key testing
        // if(time0IntNum % 1000 == 0)
        // {
        //     printf("tk0: %du\r\n", TouchKey_GetRawData(0));
        //     printf("tk1: %du\r\n", TouchKey_GetRawData(1));
        //     printf("tk3: %du\r\n", TouchKey_GetRawData(3));
        //     printf("tk4: %du\r\n", TouchKey_GetRawData(4));
        // }

        // int awaken testing
        // printf("Sleep1\r\n");
        // while (!INT1);
        // printf("Sleep2\r\n");
        // PCON |= 0x02;
        // _nop_();
        // _nop_();
        // _nop_();
        // _nop_();
        // _nop_();
        // _nop_();
        // _nop_();
        // _nop_();
        // printf("Awake\r\n");

        // NTC testing
        // if (time0IntNum % 1000 == 0)
        // {
        //     int16 temp;
        //     temp = NTC_GetTemp();
        //     // printf("T_hr: %d C\r\n", temp);
        //     // printf("H_hr: %u %%\r\n", HR_GetHum(&temp));
        //     LCD_SetHumidity(HR_GetHum(&temp));
        //     LCD_SetTemperature(temp);
        // }

        // RTC testing  RTCCR 0 disable, 1 enable
        // if (RTC_INT_1S())
        // {
        //     LCD_FlipTimeColumn();
        // }
        // else if (RTC_INT_1M())
        // {
        //     RTC_GetTime(&currentTime);
        //     printf("%02bu:%02bu\r\n", currentTime.hour, currentTime.minute);
        //     LCD_SetTime(currentTime.hour, currentTime.minute);
        // }

        // bat volt testing
        // if(time0IntNum % 1000 == 0)
        // {
        //     u16 voltage = BAT_GetVoltage();
        //     LCD_SetTemperature(voltage);
        //     LCD_SetBatteryLevel(BAT_GetLevel(&voltage));
        // }
        FSM_RUN();
    }
}