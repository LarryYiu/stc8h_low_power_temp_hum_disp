#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#define TIMER0_INTERVAL_MS 100

// Touch Key configuration
#define TK_CHANNEL_ENABLED 0x001B //  0000 0000 0001 1011 (0 1 3 4)
#define TK_CFG1 (1 << 4) + 6

// btn_power: 15101/16088 - 987- 0.06135
// btn_manual: 16430/17355 - 925 - 0.05330
// btn_down: 17171/18414 - 1243 - 0.06750
// btn_up: 16731/17854 - 1123 - 0.06290
// btn_setting: 15279/16217 - 938 - 0.05784

#define TK_PRESS_THRESHOLD_MULTIPLIER 0.05F
#define TK_UNPRESS_THRESHOLD_MULTIPLIER 0.07F

#define TK_LONG_PRESS_THRESHOLD 10
#define TK_CONTINUOUS_PRESS_THRESHOLD 6

#define TK_ALLOW_ZERO_FOLLOWING TRUE
#define TK_LOWPASS_ENABLED FALSE
#define TK_DEBUG TRUE
// End of Touch Key configuration

// STATE MACHINE configuration
#define FSM_DEBUG TRUE
#define BACKLIGHT_CD 2
// End of STATE MACHINE configuration

// NTC configuration
#define NTC_RES 10.0f
#define NTC_SAMPLE_NUM 5.0f
#define NTC_TABLE_SIZE 181
// End of NTC configuration

#define SETTING_MODE_TIME_FLASHING_INTERVAL_MS 500

#endif // __APP_CONFIG_H__