#include "Config.h"
#include "LCD_Seg.h"

void main()
{
    EAXSFR();
    LCD_Config();
    EA = 1;

    while (1)
    {
        // Main loop
    }
}