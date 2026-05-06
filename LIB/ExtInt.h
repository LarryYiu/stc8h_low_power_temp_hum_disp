#ifndef __EXT_INT_H__
#define __EXT_INT_H__

#include "Config.h"
#include "STC8G_H_Exti.h"
#include "STC8G_H_NVIC.h"

/**
 * @brief Configures the specified external interrupt with the given mode and
 * priority.
 * @param extNum The external interrupt number.
 * @param mode The interrupt mode. EXT_MODE_RiseFall, EXT_MODE_Fall
 * @param priority The interrupt priority. Set to a negative value to disable,
 * Priority_0,Priority_1,Priority_2,Priority_3 the interrupt.
 */
void ExtInt_Config(u8 extNum, bit mode, int8 priority);

#endif  // __EXT_INT_H__