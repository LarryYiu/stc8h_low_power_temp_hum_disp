#ifndef __LCD_SEG_H__
#define __LCD_SEG_H__
#include <STC8H.h>

#include "Config.h"

void LCD_Config();
void LCD_SetSignalSign(int8 signal);
void LCD_SetState(int8 stateNum);
void LCD_SetTime(int8 hour, int8 minute, bit showColumn);
void LCD_SetBatteryLevel(int8 level);
void LCD_SetStateLabels(u8 stateBitmask);
void LCD_SetTemperature(float num);
void LCD_SetHumidity(float num);
void LCD_SetUnits(u8 unitBitmask);
void LCD_SetTriangle(u8 triangleBitmask);

#endif  // __LCD_SEG_H__