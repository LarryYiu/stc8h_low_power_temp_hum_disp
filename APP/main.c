#include <stdio.h>

#include "AppSetup.h"
#include "Config.h"
#include "NTC.h"

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
            printf("c time: %lu\r\n", __Charge(TRUE));

            // printf("Timer3 Count: %lu\r\n", time3IntNum);
            // time3IntNum = 0;
        }
    }
}