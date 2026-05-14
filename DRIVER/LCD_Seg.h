#ifndef __LCD_SEG_H__
#define __LCD_SEG_H__
#include <STC8H.h>

#include "Config.h"
#define LCD_HUMIDITY_EMPTY 10000
#define LCD_TEMPERATURE_EMPTY 32767
#define LCD_TIME_EMPTY 0xff

typedef enum
{
    LCD_STATE_ERROR = 0,
    LCD_STATE_ON,
    LCD_STATE_SETTING,
    LCD_STATE_SLEEP,
} LCD_State_t;

void LCD_Config();

// void LCD_UseInternalOscillator();

// void LCD_UseExternalOscillator();

void LCD_SetSignalSign(int8 signal);
void LCD_SetState(int8 stateNum);
void LCD_FlipTimeColumn();
void LCD_TimeColOn();
void LCD_TimeColOff();

void LCD_SetHour(u8 hour);
void LCD_SetMinute(u8 minute);
void LCD_SetTime(u8 hour, u8 minute);

void LCD_SetBatteryLevel(int8 level);
void LCD_SetStateLabels(u8 stateBitmask);
void LCD_SetTemperature(int16 num);
void LCD_SetHumidity(u16 num);
void LCD_SetUnits(u8 unitBitmask);
void LCD_SetTriangle(u8 triangleBitmask);

void __LCD_SetDigitalTube(u8 tubeIndex, int8 num, bit withDP);
void __LCD_SET_SEG(u8 addr, u8 bitPos, bit setVal);

void LCD_ALL();
void LCD_CLEAR();

#endif // __LCD_SEG_H__