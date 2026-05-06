#include "AppSetup.h"

void App_Init()
{
    EAXSFR();
    Timer_Config_t0_1ms();
    UART_Config_Common();
    LCD_Config();
    TouchKey_Config();
}