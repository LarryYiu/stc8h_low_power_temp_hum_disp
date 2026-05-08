#include <stdio.h>

#include "ADC.h"
#include "AppSetup.h"
#include "Config.h"
#include "HR202L.h"

void OnShortPress(u8 keyIndex) { printf("%bu short\n", keyIndex); }

void OnLongPress(u8 keyIndex) { printf("%bu long\n", keyIndex); }

void main()
{
    App_Init();
    EA = 1;
    printf("System Initialized\r\n");
    while (1)
    {
        // if (TK_Ready)
        // {
        //     TK_Ready = FALSE;
        //     TouchKey_Event(0, TRUE, OnShortPress, OnLongPress);
        //     TouchKey_Event(1, TRUE, OnShortPress, OnLongPress);
        //     // TouchKey_Event(3, TRUE, OnShortPress, OnLongPress);
        //     TouchKey_Event(4, TRUE, OnShortPress, OnLongPress);
        // }

        // touch key testing
        // if (time0IntNum % 1000 == 0)
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
        if (time0IntNum % 1000 == 0)
        {
            // printf("R_ntc: %.2f kOhms\r\n", NTC_GetResistance());
            // printf("T_ntc: %d C\r\n", NTC_GetTemp());
            printf("R_hr: %.2f kOhms\r\n", HR_GetResistance());
        }
    }
}