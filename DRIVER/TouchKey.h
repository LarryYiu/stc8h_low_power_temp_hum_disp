#ifndef __TOUCH_KEY_H__
#define __TOUCH_KEY_H__

#include <stc8h.h>
#include <stdio.h>

#include "AppConfig.h"
#include "Config.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"

#define TK_MAX_CHANNEL \
    16  // This is the maximum number of touch key channels supported by the
        // hardware. The actual number of channels used can be configured using
        // TK_CHANNEL_ENABLED.

/**
 * MSB channel 15 ~ LSB channel 0, bit 0 ~ bit 15, 1 for enable, 0 for disable
 */
#ifndef TK_CHANNEL_ENABLED
#define TK_CHANNEL_ENABLED 0x70c0  //  0111 0000 1100 0000 (12 13 14 15)
#endif                             // TK_CHANNEL_ENABLED

#ifndef TK_CFG1
#define TK_CFG1 (1 << 4) + 6
#endif  // TK_CFG1

#ifndef TK_LOWPASS_ENABLED
#define TK_LOWPASS_ENABLED FALSE
#endif  // TK_LOWPASS_ENABLED

#ifndef TK_PRESS_THRESHOLD_MULTIPLIER
#define TK_PRESS_THRESHOLD_MULTIPLIER 0.5F
#endif  // TK_PRESS_THRESHOLD_MULTIPLIER

#ifndef TK_UNPRESS_THRESHOLD_MULTIPLIER
#define TK_UNPRESS_THRESHOLD_MULTIPLIER 0.666F
#endif  // TK_UNPRESS_THRESHOLD_MULTIPLIER

#ifndef TK_LONG_PRESS_THRESHOLD
#define TK_LONG_PRESS_THRESHOLD 5
#endif  // TK_LONG_PRESS_THRESHOLD

#ifndef TK_CONTINUOUS_PRESS_THRESHOLD
#define TK_CONTINUOUS_PRESS_THRESHOLD 3
#endif  // TK_CONTINUOUS_PRESS_THRESHOLD

#ifndef TK_CLEAR_DURATION_DELAY
#define TK_CLEAR_DURATION_DELAY 1
#endif  // TK_CLEAR_DURATION_DELAY

#ifndef TK_ALLOW_ZERO_FOLLOWING
#define TK_ALLOW_ZERO_FOLLOWING TRUE
#endif  // TK_ALLOW_ZERO_FOLLOWING

#ifndef TK_DEBUG
#define TK_DEBUG TRUE
#endif  // TK_DEBUG

#ifndef TK_USE_PRIORITY
#define TK_USE_PRIORITY FALSE
#define TK_INTERRUPT_PRIORITY 0
#endif  // TK_USE_PRIORITY

/**
 * @brief TouchKey_t is a structure that holds the state and timing information
 * for a single touch key channel.
 *
 * It includes the following members:
 *
 * - `pressDuration`: The duration (in scan cycles) that the touch key has been
 * continuously pressed. This value is incremented in the interrupt handler when
 * the key is detected as pressed, and reset to 0 when the key is released.
 *
 * - `pressCount`: The count of how many times the touch key has been pressed.
 * This value is incremented each time a new press is detected (when the key
 * transitions from not pressed to pressed).
 *
 * - `lastReleaseDuration`: The duration (in scan cycles) that the touch key was
 * continuously released before the most recent press. This value is updated in
 * the interrupt handler when the key is released.
 *
 * - `isPressing`: A flag indicating whether the touch key is currently being
 * pressed (1) or not (0). This value is updated in the interrupt handler based
 * on the current scan results for the touch key channel.
 *
 */
typedef struct
{
    u8 pressDuration;
    u8 pressCount;
    u8 lastReleaseDuration;
    u8 isPressing;
} TouchKey_t;

extern TouchKey_t xdata touchKeys[TK_MAX_CHANNEL];

/**
 * @brief touchKeyStatus is a 16-bit variable where each bit represents the
 * current status of a touch key (1 for pressed, 0 for not pressed).
 * MSB 15 ~ LSB 0 corresponds to TK15 ~ TK0. The status is updated in the
 * interrupt handler.
 */
extern u16 xdata touchKeyStatus;

/**
 * @brief KT_READ_DONE_FLAG is a flag that indicates whether the touch key
 * scanning is completed for the current scan cycle. It is set to TRUE in the
 * interrupt handler when the scanning is done. The main loop can check this
 * flag to know when to read the touch key status and perform related actions.
 * After processing the touch key status, the main loop should set this flag
 * back to FALSE to wait for the next scan cycle.
 *
 * @note the flag is not essential if the timer is tuned properly.
 */
extern bit TK_Ready;

/**
 * @brief TouchKey_Config initializes the touch key channels and related GPIOs.
 * It should be called before using any touch key functions. This function WILL
 * configure the GPIO pins for the enabled touch key channels, set up the touch
 * key scanning parameters, and enable the touch key interrupt.
 */
void TouchKey_Config();

/**
 * @brief TouchKey_Scan performs a scan of the touch key channels to update
 * their status.
 *
 * @note This function is typically called in the timer interrupt
 * handler to continuously monitor the touch key states.
 *
 * @warning must set up related registers before calling this function
 */
void TouchKey_Scan();

/**
 * @brief TouchKey_IsAnyPressed checks if any touch key is currently pressed.
 * @return TRUE if any touch key is pressed, FALSE otherwise.
 * Note: The touch key status is updated in the interrupt handler, so this
 * function should be called after the TK_READ_DONE_FLAG is set to TRUE to get
 * the latest status.
 */
bit TouchKey_IsAnyPressed();

/**
 * @brief TouchKey_GetPressedKeys returns a 16-bit bitmask representing the
 * pressed status of each touch key channel. Each bit corresponds to a touch key
 * channel, where bit 0 corresponds to TK0 and bit 15 corresponds to TK15. A bit
 * value of 1 indicates that the corresponding touch key is pressed, while a bit
 * value of 0 indicates that it is not pressed.
 */
u16 TouchKey_GetPressedKeys();

/**
 * @brief Get the raw data value of a specific touch key channel. Call after
 * TK_READ_DONE_FLAG is set to TRUE to get the latest data.
 *
 * @param channel The touch key channel number (0-15) to check.
 *
 * @return The raw data value of the specified touch key channel.
 */
u16 TouchKey_GetRawData(u8 channel);

/**
 * @brief Get the initial value (baseline) of a specific touch key channel. This
 * value is used to determine the press and release thresholds for the touch
 * key.
 *
 * @note initial value is recorded during the first few scan cycles after the
 * system starts up, and is updated if the touch key is not pressed for a
 * certain duration to adapt to environmental changes if TK_ALLOW_ZERO_FOLLOWING
 * is enabled.
 *
 * @param channel The touch key channel number (0-15) to check.
 *
 * @return The initial value (baseline) of the specified touch key channel.
 */
u16 TouchKey_GetInitVal(u8 channel);

/**
 * @brief TouchKey_IsPressed checks if a specific touch key channel is currently
 * pressed. Call after TK_READ_DONE_FLAG is set to TRUE to get the latest
 * status.
 *
 * @param channel The touch key channel number (0-15) to check.
 * @return TRUE if the specified touch key channel is pressed, FALSE otherwise.
 */
bit TouchKey_IsPressed(u8 channel);

/**
 * @brief TouchKey_Event registers callback functions for short press and long
 * press events for a specific touch key channel. add continuous press event if
 * needed.
 *
 * @param keyIndex The touch key channel number (0-15) to register the events
 * for.
 * @param isReleaseTrigger A flag indicating whether the events should be
 * triggered on release (TRUE) or on press (FALSE).
 * @param onShortPress A pointer to the callback function to be called when a
 * short press event is detected for the specified touch key channel. The
 * callback function should take a single parameter of type u8, which can be
 * pressCount or key index.
 *
 * @param onLongPress A pointer to the callback function to be called when a
 * long press event is detected for the specified touch key channel. The
 * callback function should take a single parameter of type u8, which can be
 * pressCount or key index.
 */
void TouchKey_Event(u8 keyIndex, bit isReleaseTrigger,
                    void (*onShortPress)(u8 pressCount),
                    void (*onLongPress)(u8 pressCount));

#endif  // __TOUCH_KEY_H__