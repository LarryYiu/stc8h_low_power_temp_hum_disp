#include "TouchKey.h"

/**
 * @brief __TK_DAT_BUFF is an array that stores the raw data read from each
 * touch key channel during scanning. The index corresponds to the touch key
 * channel number (0-15). This data can be used for debugging, calibration, or
 * implementing advanced features like auto-calibration. The values are updated
 * in the interrupt handler when a scan is completed for each channel. Note that
 * the values in __TK_DAT_BUFF are the raw readings and may need to be processed
 * (e.g., low-pass filtered) before being used for touch detection, depending on
 * the configuration.
 */
u16 xdata __TK_DAT_BUFF[TK_MAX_CHANNEL];

TouchKey_t xdata touchKeys[TK_MAX_CHANNEL];

/**
 * @brief The scanning stops at the last TKx, where x is the bit counting from
 * the MSB of TK_CHANNEL_ENABLED, so we can use this variable to check if the
 * scanning is done in the interrupt handler.
 */
u8 xdata __keyNumMSB = 0;

u16 xdata __TOUCH_KEY_INITIAL_VAL[TK_MAX_CHANNEL];

u16 xdata touchKeyStatus = 0x0000;
bit TK_Ready = FALSE;

u8 code __TOUCH_KEY_GPIO_LOOKUP_TABLE[TK_MAX_CHANNEL][2] = {
    {GPIO_P1, GPIO_Pin_0},  // TK0
    {GPIO_P1, GPIO_Pin_1},  // TK1
    {GPIO_P5, GPIO_Pin_4},  // TK2
    {GPIO_P1, GPIO_Pin_3},  // TK3
    {GPIO_P1, GPIO_Pin_4},  // TK4
    {GPIO_P1, GPIO_Pin_5},  // TK5
    {GPIO_P2, GPIO_Pin_6},  // TK6
    {GPIO_P2, GPIO_Pin_7},  // TK7
    {GPIO_P5, GPIO_Pin_0},  // TK8
    {GPIO_P5, GPIO_Pin_1},  // TK9
    {GPIO_P5, GPIO_Pin_2},  // TK10
    {GPIO_P5, GPIO_Pin_3},  // TK11
    {GPIO_P0, GPIO_Pin_0},  // TK12
    {GPIO_P0, GPIO_Pin_1},  // TK13
    {GPIO_P0, GPIO_Pin_2},  // TK14
    {GPIO_P0, GPIO_Pin_3}   // TK15
};

typedef enum
{
    TK_PRESSED = 0,
    TK_RELEASED = 1,
    TK_GRAY_AREA = 2
} __TK_STATE;

bit __TK_CheckPressCondition(u8 tkIndex)
{
    if ((__TOUCH_KEY_INITIAL_VAL[tkIndex] - __TK_DAT_BUFF[tkIndex]) >=
        (TK_PRESS_THRESHOLD_MULTIPLIER * __TOUCH_KEY_INITIAL_VAL[tkIndex]))
    {
        return TK_PRESSED;
    }
    else if ((__TOUCH_KEY_INITIAL_VAL[tkIndex] - __TK_DAT_BUFF[tkIndex]) <=
             (TK_UNPRESS_THRESHOLD_MULTIPLIER *
              __TOUCH_KEY_INITIAL_VAL[tkIndex]))
    {
        return TK_RELEASED;
    }
    else
    {
        return TK_GRAY_AREA;
    }
}

/**
 * [TSIF][TSDOV][/][/][TSDNCHN 3:0]
 * TSIF, Scan complete flag, set by hardware when scan complete, write 1 to
 * clear
 *
 * TSDOV, Data overflow flag, set by hardware when data overflow, write 1
 * to clear
 *
 * TSDNCHN, Current channel number being scanned, 0 ~ 15
 */
void TouchKey_ISR() interrupt TKSU_VECTOR
{
    u8 tkIndex = TSSTA2;

    if (tkIndex & 0x40)  // 数据溢出, 错误处理(略)
    {
        TSSTA2 |= 0x40;  // 写1清零
    }
    if (tkIndex & 0x80)  // 扫描完成
    {
        tkIndex &= 0x0f;
        TSSTA2 |= 0x80;  // 写1清零

#if (TK_LOWPASS_ENABLED)
        __TK_DAT_BUFF[tkIndex] =
            ((__TK_DAT_BUFF[tkIndex] * 3) >> 2) + TSDAT / 16;
#else
        // __TK_DAT_BUFF[tkIndex] = TSDAT / 4;
        __TK_DAT_BUFF[tkIndex] = TSDAT;
#endif  // TK_LOWPASS_ENABLED

#if (TK_ALLOW_ZERO_FOLLOWING)
        if (__TOUCH_KEY_INITIAL_VAL[tkIndex] >= __TK_DAT_BUFF[tkIndex])
        {
            if (__TK_CheckPressCondition(tkIndex) == TK_PRESSED)
            {
                __TOUCH_KEY_INITIAL_VAL[tkIndex]--;
                touchKeyStatus |= (0x0001 << tkIndex);

                if (touchKeys[tkIndex].isPressing)
                {
                    touchKeys[tkIndex].pressDuration++;
                }
                else  // was not pressing, now pressing
                {
                    if (touchKeys[tkIndex].lastReleaseDuration <
                        TK_CONTINUOUS_PRESS_THRESHOLD)
                    {
                        touchKeys[tkIndex].pressCount++;
                    }
                    else
                    {
                        touchKeys[tkIndex].pressCount =
                            1;  // reset press count if last
                                // release was long enough
                    }
                }
                touchKeys[tkIndex].isPressing = TRUE;
                touchKeys[tkIndex].lastReleaseDuration = 0;
            }
            else if (__TK_CheckPressCondition(tkIndex) == TK_RELEASED)
            {
                touchKeyStatus &= ~(0x0001 << tkIndex);
                if (touchKeys[tkIndex].lastReleaseDuration >=
                    TK_CONTINUOUS_PRESS_THRESHOLD)
                {
                    touchKeys[tkIndex].pressCount = 0;
                }
                if (touchKeys[tkIndex].lastReleaseDuration >=
                    TK_CLEAR_DURATION_DELAY)
                {
                    touchKeys[tkIndex].pressDuration = 0;
                }
                touchKeys[tkIndex].lastReleaseDuration++;
                touchKeys[tkIndex].isPressing = FALSE;
            }
        }
        else
        {
            touchKeyStatus &= ~(0x0001 << tkIndex);
            if ((__TK_DAT_BUFF[tkIndex] - __TOUCH_KEY_INITIAL_VAL[tkIndex]) >
                100)
                __TOUCH_KEY_INITIAL_VAL[tkIndex] +=
                    50;  // 差别很大, 则快速回0点
            else
                __TOUCH_KEY_INITIAL_VAL[tkIndex] +=
                    10;  // 差别不大, 则慢速回0点
        }
#else
        if (__TK_CheckPressCondition(tkIndex) == TK_PRESSED)
        {
            touchKeyStatus |= (0x0001 << tkIndex);

            if (touchKeys[tkIndex].isPressing)
            {
                touchKeys[tkIndex].pressDuration++;
            }
            else  // was not pressing, now pressing
            {
                if (touchKeys[tkIndex].lastReleaseDuration <
                    TK_CONTINUOUS_PRESS_THRESHOLD)
                {
                    touchKeys[tkIndex].pressCount++;
                }
                else
                {
                    touchKeys[tkIndex].pressCount =
                        1;  // reset press count if last
                            // release was long enough
                }
            }
            touchKeys[tkIndex].isPressing = TRUE;
            touchKeys[tkIndex].lastReleaseDuration = 0;
        }
        else if (__TK_CheckPressCondition(tkIndex) == TK_RELEASED)
        {
            if (touchKeys[tkIndex].lastReleaseDuration >=
                TK_CONTINUOUS_PRESS_THRESHOLD)
            {
                touchKeys[tkIndex].pressCount = 0;
            }

            if (touchKeys[tkIndex].lastReleaseDuration >=
                TK_CLEAR_DURATION_DELAY)
            {
                touchKeys[tkIndex].pressDuration = 0;
            }
            touchKeys[tkIndex].lastReleaseDuration++;
            touchKeys[tkIndex].isPressing = FALSE;
        }
#endif  // TK_ALLOW_ZERO_FOLLOWING
        if (tkIndex == __keyNumMSB)
        {
            TK_Ready = TRUE;
        }
    }
}

void __TK_GPIO_Config()
{
    u8 i;
    for (i = 0; i < TK_MAX_CHANNEL; i++)
    {
        if ((TK_CHANNEL_ENABLED >> i) & 0x0001)
        {
            GPIO_Config(__TOUCH_KEY_GPIO_LOOKUP_TABLE[i][0],
                        __TOUCH_KEY_GPIO_LOOKUP_TABLE[i][1], GPIO_HighZ);
        }
    }
}

void __TK_Calibrate()
{
    u8 i;

    // wait for the readings to stabilize before calibration
    for (i = 0; i < 20; i++)
    {
        TouchKey_Scan();
        delay_ms(20);
    }
    for (i = 0; i < TK_MAX_CHANNEL; i++)
    {
        if ((TK_CHANNEL_ENABLED >> i) & 0x0001)
        {
            __TOUCH_KEY_INITIAL_VAL[i] = __TK_DAT_BUFF[i];
#if (TK_DEBUG)
            printf("TouchKey Calibration of channel %bu, initial value: %u\r\n",
                   i, __TOUCH_KEY_INITIAL_VAL[i]);
#endif  // TK_DEBUG
        }
    }
}

/**
 * TK6 TK7 TK12 TK13 TK14
 */
void TouchKey_Config()
{
    u8 i;
    for (i = 0; i < TK_MAX_CHANNEL; i++)
    {
        if (TK_CHANNEL_ENABLED & (0x8000 >> i))
        {
            __keyNumMSB = 15 - i;
            break;
        }
    }
    __TK_GPIO_Config();
    TSCHEN1 = (u8)(TK_CHANNEL_ENABLED & 0x00FF);         // TK7 ~ TK0
    TSCHEN2 = (u8)((TK_CHANNEL_ENABLED >> 8) & 0x00FF);  // TK15 ~ TK8
    TSCFG1 = TK_CFG1;  // Configuration register 1, SCR and DT
    TSCFG2 = 0x01;     // Configuration register 2, TSVR
    TSRT = 0x00;       // Disable the led time-sharing
    IE2 |= 0x80;       // Enable touch key interrupt, IE2 bit 7 is EUSB idk why
#if (TK_USE_PRIORITY)
    PTKSU_Priority(TK_INTERRUPT_PRIORITY);
#endif  // TK_USE_PRIORITY

    EA = 1;
#if (TK_DEBUG)
    printf("TouchKey: MSB channel: %bu\r\n", __keyNumMSB);
#endif  // TK_DEBUG
    __TK_Calibrate();
    EA = 0;
}

void TouchKey_Scan() { TSCTRL = (1 << 7) + (1 << 6) + 1; }

bit TouchKey_IsAnyPressed()
{
    return (bit)(touchKeyStatus && TouchKey_GetPressedKeys());
}

u16 TouchKey_GetPressedKeys() { return touchKeyStatus & TK_CHANNEL_ENABLED; }

bit TouchKey_IsPressed(u8 channel)
{
    if (channel < TK_MAX_CHANNEL && channel >= 0)
    {
        return ((touchKeyStatus >> channel) & 0x0001 > 0);
    }
    else
    {
        return FALSE;
    }
}

u16 TouchKey_GetRawData(u8 channel)
{
    if (channel < TK_MAX_CHANNEL && channel >= 0)
    {
        return __TK_DAT_BUFF[channel];
    }
    else
    {
        return 0;
    }
}

u16 TouchKey_GetInitVal(u8 channel)
{
    if (channel < TK_MAX_CHANNEL && channel >= 0)
    {
        return __TOUCH_KEY_INITIAL_VAL[channel];
    }
    else
    {
        return 0;
    }
}

void TouchKey_Event(u8 keyIndex, bit isReleaseTrigger,
                    void (*onShortPress)(u8 pressCount),
                    void (*onLongPress)(u8 pressCount))
{
    static u16 lastPressed;

    if (keyIndex < TK_MAX_CHANNEL && keyIndex >= 0 &&
        touchKeys[keyIndex].isPressing)
    {
        if ((lastPressed >> keyIndex & 0x0001) == 0)
        {
            lastPressed |= (0x0001 << keyIndex);
        }
        if (!isReleaseTrigger)
        {
            if (touchKeys[keyIndex].pressDuration >= TK_LONG_PRESS_THRESHOLD)
            {
                if (onLongPress)
                {
                    onLongPress(keyIndex);
                }
            }
            else
            {
                if (onShortPress)
                {
                    onShortPress(keyIndex);
                }
            }
        }
    }
    else
    {
        if (isReleaseTrigger)
        {
            if ((lastPressed >> keyIndex & 0x0001) != 0)
            {
                if (touchKeys[keyIndex].pressDuration >=
                    TK_LONG_PRESS_THRESHOLD)
                {
                    if (onLongPress)
                    {
                        onLongPress(keyIndex);
                    }
                }
                else
                {
                    if (onShortPress)
                    {
                        onShortPress(keyIndex);
                    }
                }
            }
        }
        lastPressed &= ~(0x0001 << keyIndex);
        return;
    }
}