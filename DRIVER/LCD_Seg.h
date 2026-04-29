#ifndef __LCD_SEG_H__
#define __LCD_SEG_H__
#include <STC8H.h>

#include "Config.h"

void LCD_Config();
void __LCD_SET_SEG(u8 addr, u8 bitPos, bit setVal);

#endif  // __LCD_SEG_H__