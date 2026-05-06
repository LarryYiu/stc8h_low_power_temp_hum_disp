#include <stdio.h>

#include "AppSetup.h"
#include "Config.h"

void OnShortPress(u8 keyIndex) { printf("%bu short\n", keyIndex); }

void OnLongPress(u8 keyIndex) { printf("%bu long\n", keyIndex); }

void main()
{
    App_Init();
    EA = 1;
    printf("System Initialized\r\n");

    while (1)
    {
        if (TK_Ready)
        {
            TK_Ready = FALSE;
            TouchKey_Event(0, TRUE, OnShortPress, OnLongPress);
            TouchKey_Event(1, TRUE, OnShortPress, OnLongPress);
            // TouchKey_Event(3, FALSE, OnShortPress, OnLongPress);
            TouchKey_Event(4, TRUE, OnShortPress, OnLongPress);
        }
        // if (time0IntNum % 1000 == 0)
        // {
        //     printf("tk0: %du\r\n", TouchKey_GetRawData(0));
        //     printf("tk1: %du\r\n", TouchKey_GetRawData(1));
        //     printf("tk3: %du\r\n", TouchKey_GetRawData(3));
        //     printf("tk4: %du\r\n", TouchKey_GetRawData(4));
        // }
    }
}