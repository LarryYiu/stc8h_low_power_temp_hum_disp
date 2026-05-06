#include "AppSetup.h"

void App_Init()
{
    EAXSFR();
    Timer_Config_t0_1ms();
    Timer_Config(Timer1, TIM_16BitAutoReload, TIM_CLOCK_1T, DISABLE, 1000UL,
                 DISABLE, 0, Priority_0);
    NTC_Config();
    UART_Config_Common();
    Key_Config();
    LCD_Config();
    TouchKey_Config();
}