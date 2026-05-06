#ifndef __APP_SETUP_H__
#define __APP_SETUP_H__
#include <stc8h.h>

#include "Config.h"
#include "GPIO.h"
#include "LCD_Seg.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_UART.h"
#include "Timer.h"
#include "TouchKey.h"
#include "UART.h"

void App_Init();
#endif  // __APP_SETUP_H__