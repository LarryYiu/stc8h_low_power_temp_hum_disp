#include "FSM.h"

RTC_Time_t currentTime;
bit flagUpdateTempHum = 0;

FSM_WAKE_UP_SOURCE_t wakeUpSource = WAKE_UP_SOURCE_NONE;

bit flagSettingHour = TRUE;
bit flagDisplayTime = TRUE;
u8 settingHour;
u8 settingMin;

void __StateOn(void);
void __StateSleep(void);
void __StateSetting(void);

void __onSettingShortPress(u8 key);
void __onSettingLongPress(u8 key);
void __onOnShortPress(u8 key);

void __updateTempHum();

void __GPIO_Sleep();
void __GPIO_Awake();

FSM_t fsm = {__StateOn};

void __OnEnterSleep()
{
    // LCD_UseExternalOscillator();
    printf("->Sleep\r\n");
    __GPIO_Sleep();
    ADC_Off();
    UART_Off();
    Timer_Off(1);
    Timer_Off(3);
    TouchKey_Off();
    TouchKey_Clear();
    __updateTempHum();
    LCD_SetState(LCD_STATE_SLEEP);
    wakeUpSource = WAKE_UP_SOURCE_NONE;
    fsm.current  = __StateSleep;
}

void __OnEnterAwake()
{
    // LCD_UseInternalOscillator();
    __GPIO_Awake();
    ADC_On();
    UART_On();
    Timer_On(1);
    Timer_On(3);
    TouchKey_On();
    TouchKey_Clear();
    __updateTempHum();
    LCD_SetBatteryLevel(BAT_GetLevel(NULL));
    LCD_SetState(LCD_STATE_ON);
    printf("->Awake\r\n");
    fsm.current = __StateOn;
    // lcd switch to internal oscillator
}

void __OnEnterSetting()
{
    TouchKey_Clear();
    RTC_GetTime(&currentTime);
    settingHour = currentTime.hour;
    settingMin  = currentTime.minute;
    LCD_SetBatteryLevel(BAT_GetLevel(NULL));
    LCD_TimeColOn();
    RTC_Off();
    LCD_SetState(LCD_STATE_SETTING);
    LCD_SetHumidity(LCD_HUMIDITY_EMPTY);
    LCD_SetTemperature(LCD_TEMPERATURE_EMPTY);
    fsm.current = __StateSetting;
}

void __OnExitSettingSave()
{
    TouchKey_Clear();
    currentTime.hour   = settingHour;
    currentTime.minute = settingMin;
    RTC_SetTime(&currentTime);
    LCD_SetTime(currentTime.hour, currentTime.minute);
    LCD_SetState(LCD_STATE_ON);
    LCD_SetBatteryLevel(BAT_GetLevel(NULL));
    __updateTempHum();
    RTC_On();
    fsm.current = __StateOn;
}

void __OnExitSettingQuit()
{
    TouchKey_Clear();
    LCD_SetState(LCD_STATE_ON);
    LCD_SetTime(currentTime.hour, currentTime.minute);
    LCD_SetBatteryLevel(BAT_GetLevel(NULL));
    __updateTempHum();
    RTC_On();
    fsm.current = __StateOn;
}

void __StateOn(void)
{
    if(TK_Ready)
    {
        TK_Ready = FALSE;
        TouchKey_Event(TK1, TRUE, __onOnShortPress, __onOnShortPress);
        TouchKey_Event(TK2, TRUE, NULL, NULL);
        TouchKey_Event(TK3, TRUE, NULL, NULL);
        TouchKey_Event(TK4, TRUE, __onOnShortPress, __onOnShortPress);
    }

    if(RTC_INT_1S()) // flip time column every second
    {
        LCD_FlipTimeColumn();
        // handle awaken from sleep by RTC 1s interrupt
    }
    else if(RTC_INT_1M()) // update time every minute
    {
        RTC_GetTime(&currentTime);
        // printf("%02bu:%02bu\r\n", currentTime.hour, currentTime.minute);
        LCD_SetTime(currentTime.hour, currentTime.minute);
    }
    else if(RTC_INT_1H()) // update battery level every hour
    {
        LCD_SetBatteryLevel(BAT_GetLevel(NULL));
    }

    if(flagUpdateTempHum)
    {
        __updateTempHum();
        flagUpdateTempHum = FALSE;
    }
}

void __StateSleep(void)
{
    while(!INT1)
    {
    }
    PCON |= 0x02;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    if(wakeUpSource == WAKE_UP_SOURCE_NONE)
    {
        return;
    }

    if(wakeUpSource == WAKE_UP_SOURCE_RTC_1S)
    {
        LCD_FlipTimeColumn();
        wakeUpSource = WAKE_UP_SOURCE_NONE;
    }
    else if(wakeUpSource == WAKE_UP_SOURCE_RTC_1M)
    {
        // update time, temp, hum
        __updateTempHum();
        printf("->Awake\r\n");
        wakeUpSource = WAKE_UP_SOURCE_NONE;
    }
    else if(wakeUpSource == WAKE_UP_SOURCE_RTC_1H)
    {
        LCD_SetBatteryLevel(BAT_GetLevel(NULL));
        wakeUpSource = WAKE_UP_SOURCE_NONE;
    }
    else if(wakeUpSource == WAKE_UP_SOURCE_INT)
    {
        __OnEnterAwake();
    }
}

void __StateSetting(void)
{
    if(TK_Ready)
    {
        TK_Ready = FALSE;
        TouchKey_Event(TK1, TRUE, __onSettingShortPress, __onSettingShortPress);
        TouchKey_Event(TK2, TRUE, __onSettingShortPress, __onSettingShortPress);
        TouchKey_Event(TK3, TRUE, __onSettingShortPress, __onSettingShortPress);
        TouchKey_Event(TK4, TRUE, __onSettingShortPress, __onSettingLongPress);
    }

    if(flagSettingHour)
    {
        if(flagDisplayTime)
        {
            LCD_SetHour(LCD_TIME_EMPTY);
        }
        else
        {
            LCD_SetHour(settingHour);
        }
    }
    else
    {
        if(flagDisplayTime)
        {
            LCD_SetMinute(LCD_TIME_EMPTY);
        }
        else
        {
            LCD_SetMinute(settingMin);
        }
    }
}

void FSM_RUN()
{
    if(fsm.current != NULL)
    {
        fsm.current();
    }
}

void FSM_UpdateTempHum()
{
    flagUpdateTempHum = TRUE;
}

void FSM_FlipFlagDisplayTime()
{
    flagDisplayTime = !flagDisplayTime;
}

void __updateTempHum()
{
    int16 temp = NTC_GetTemp();
    LCD_SetHumidity(HR_GetHum(&temp));
    LCD_SetTemperature(temp);
}

void FSM_SetWakeUpSource(FSM_WAKE_UP_SOURCE_t source)
{
    wakeUpSource = source;
}

void __GPIO_Sleep()
{
    P0_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P1_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P2_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P3_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P3_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P4_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P5_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P6_DIGIT_IN_DISABLE(GPIO_Pin_All);
    P7_DIGIT_IN_DISABLE(GPIO_Pin_All);

    P3_DIGIT_IN_ENABLE(GPIO_Pin_2 | GPIO_Pin_3); // INT1, INT0
    P6_DIGIT_IN_ENABLE(GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
    P5_DIGIT_IN_ENABLE(GPIO_Pin_0); // COM0(3)
    P0_DIGIT_IN_ENABLE(GPIO_Pin_3); // SEG13(27)
}

void __GPIO_Awake()
{
    P0_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P1_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P2_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P3_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P3_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P4_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P5_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P6_DIGIT_IN_ENABLE(GPIO_Pin_All);
    P7_DIGIT_IN_ENABLE(GPIO_Pin_All);
}

/* KEY EVENT FUNCTIONS*/

void __onOnShortPress(u8 key)
{
    switch(key)
    {
        case TK1:
            printf("TK1 short press\r\n");
            __OnEnterSetting();
            break;
        case TK4:
            printf("TK4 short press\r\n");
            __OnEnterSleep();
            fsm.current = __StateSleep;
            break;
        default:
            break;
    }
}

void __onSettingShortPress(u8 key)
{
    switch(key)
    {
        case TK1:
            printf("TK1 short press\r\n");
            flagSettingHour = !flagSettingHour;
            if(flagSettingHour)
            {
                LCD_SetMinute(settingMin);
            }
            else
            {
                LCD_SetHour(settingHour);
            }
            break;
        case TK2:
            printf("TK2 short press\r\n");
            if(flagSettingHour)
            {
                settingHour = (settingHour + 1) % 24;
            }
            else
            {
                settingMin = (settingMin + 1) % 60;
            }
            break;
        case TK3:
            printf("TK3 short press\r\n");
            if(flagSettingHour)
            {
                settingHour = (settingHour + 23) % 24;
            }
            else
            {
                settingMin = (settingMin + 59) % 60;
            }
            break;
        case TK4:
            printf("TK4 short press\r\n");
            __OnExitSettingSave();
            break;
        default:
            break;
    }
}

void __onSettingLongPress(u8 key)
{
    if(key == TK1)
    {
        __OnExitSettingSave();
    }
    else if(key == TK4)
    {
        __OnExitSettingQuit();
    }
    return;
}