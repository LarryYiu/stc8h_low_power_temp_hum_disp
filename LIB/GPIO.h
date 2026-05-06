#ifndef __GPIO_H__
#define __GPIO_H__

#include "Config.h"
#include "STC8G_H_GPIO.h"

extern u8 code GPIO_PIN_LOOKUP_TABLE[8];
extern u8 code GPIO_GROUP_LOOKUP_TABLE[8];

/**
 * @brief GPIO pin configuration function, This function does not extend the
 * register access.
 * @param pinGroup: GPIO pin group (e.g., P1x, P2x, etc.)
 * @param pinNumber: GPIO pin number within the group (0-7)
 * @param pinMode: GPIO pin mode, can be one of the following: GPIO_PullUp,
 * GPIO_HighZ, GPIO_OUT_OD, GPIO_OUT_PP
 */
void GPIO_Config(u8 pinGroup, u8 pinNumber, u8 pinMode);

/**
 * @brief GPIO pin configuration function with a pre-allocated GPIO_InitTypeDef
 * structure, This function is designed for scenarios where the GPIO_InitTypeDef
 * structure needs to be reused or modified after initialization
 * @param pinGroup: GPIO pin group (e.g., P1x, P2x, etc.)
 * @param pinNumber: GPIO pin number within the group (0-7)
 * @param pinMode: GPIO pin mode, can be one of the following: GPIO_PullUp,
 * GPIO_HighZ, GPIO_OUT_OD, GPIO_OUT_PP
 * @param GPIO_InitStructure: Pointer to a pre-allocated GPIO_InitTypeDef
 * structure
 */
void GPIO_FrqConfig(u8 pinGroup, u8 pinNumber, u8 pinMode,
                    GPIO_InitTypeDef* GPIO_InitStructure);
#endif  // __GPIO_H__