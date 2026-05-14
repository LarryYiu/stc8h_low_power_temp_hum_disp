#include "AppSetup.h"

void App_Init()
{
    RTC_Time_t time;
    u16 voltage;
    int16 temp;
    EAXSFR();

    P0_MODE_IN_HIZ(GPIO_Pin_All);
    P1_MODE_IN_HIZ(GPIO_Pin_All);
    P2_MODE_IN_HIZ(GPIO_Pin_All);
    P3_MODE_IN_HIZ(GPIO_Pin_All);
    P4_MODE_IN_HIZ(GPIO_Pin_All);
    P5_MODE_IN_HIZ(GPIO_Pin_All);
    P6_MODE_IN_HIZ(GPIO_Pin_All);
    P7_MODE_IN_HIZ(GPIO_Pin_All);

    // Timer_Config_t0_1ms();
    Timer_Config(Timer1, TIM_16BitAutoReload, TIM_CLOCK_1T, DISABLE, 1000UL, ENABLE, 0, Priority_0);
    Timer_Config_t3_1us();
    NTC_Config();
    UART_Config_Common();
    Key_Config();
    RTC_Config(NULL);
    LCD_Config();
    TouchKey_Config();

    // initial display

    RTC_GetTime(&time);
    LCD_SetTime(time.hour, time.minute);
    EA      = 1;
    voltage = BAT_GetVoltage();
    temp    = NTC_GetTemp();
    LCD_SetHumidity(HR_GetHum(&temp));
    LCD_SetTemperature(temp);

    TouchKey_Event(0, TRUE, NULL, NULL);
    TouchKey_Event(1, TRUE, NULL, NULL);
    TouchKey_Event(3, TRUE, NULL, NULL);
    TouchKey_Event(4, TRUE, NULL, NULL);

    EA = 0;
    LCD_SetBatteryLevel(voltage);
    LCD_SetState(LCD_STATE_ON);
}