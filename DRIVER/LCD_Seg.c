#include "LCD_Seg.h"

#define LCD_ADDR_H 0xFB00

#define __S6_ADDR__ 0xAB
#define __13A_ADDR__ 0xAC
#define __13F_ADDR__ 0xAC
#define __12A_ADDR__ 0xAC
#define __12F_ADDR__ 0xAC
#define __11A_ADDR__ 0xAB
#define __11F_ADDR__ 0xAB
#define __10A_ADDR__ 0xAB
#define __10F_ADDR__ 0xAB
#define __SET_ADDR__ 0xAB
#define __H1_ADDR__ 0xAB
#define __6F_ADDR__ 0xAB
#define __6A_ADDR__ 0xAA
#define __7F_ADDR__ 0xAA
#define __7A_ADDR__ 0xAA
#define __8F_ADDR__ 0xAA
#define __8A_ADDR__ 0xAA
#define __9F_ADDR__ 0xA8
#define __9A_ADDR__ 0xA8
#define __S2_ADDR__ 0xA8
#define __S3_ADDR__ 0xA8
#define __1F_ADDR__ 0xAA
#define __1A_ADDR__ 0xAA
#define __2F_ADDR__ 0xAA
#define __2A_ADDR__ 0xA9
#define __3F_ADDR__ 0xA9
#define __3A_ADDR__ 0xA9
#define __4F_ADDR__ 0xA9
#define __4A_ADDR__ 0xA9
#define __5F_ADDR__ 0xA9
#define __5A_ADDR__ 0xA9
#define __T5_ADDR__ 0xA9
#define __S7_ADDR__ 0xA3
#define __13B_ADDR__ 0xA4
#define __13G_ADDR__ 0xA4
#define __12B_ADDR__ 0xA4
#define __12G_ADDR__ 0xA4
#define __11B_ADDR__ 0xA3
#define __11G_ADDR__ 0xA3
#define __10B_ADDR__ 0xA3
#define __10G_ADDR__ 0xA3
#define __COMM_ADDR__ 0xA3
#define __L1_ADDR__ 0xA3
#define __6G_ADDR__ 0xA3
#define __6B_ADDR__ 0xA2
#define __7G_ADDR__ 0xA2
#define __7B_ADDR__ 0xA2
#define __8G_ADDR__ 0xA2
#define __8B_ADDR__ 0xA2
#define __9G_ADDR__ 0xA0
#define __9B_ADDR__ 0xA0
#define __LX_ADDR__ 0xA0
#define __V_ADDR__ 0xA0
#define __1G_ADDR__ 0xA2
#define __1B_ADDR__ 0xA2
#define __2G_ADDR__ 0xA2
#define __2B_ADDR__ 0xA1
#define __3G_ADDR__ 0xA1
#define __3B_ADDR__ 0xA1
#define __4G_ADDR__ 0xA1
#define __4B_ADDR__ 0xA1
#define __5G_ADDR__ 0xA1
#define __5B_ADDR__ 0xA1
#define __T4_ADDR__ 0xA1
#define __S8_ADDR__ 0x9B
#define __13C_ADDR__ 0x9C
#define __13E_ADDR__ 0x9C
#define __12C_ADDR__ 0x9C
#define __12E_ADDR__ 0x9C
#define __11C_ADDR__ 0x9B
#define __11E_ADDR__ 0x9B
#define __10C_ADDR__ 0x9B
#define __10E_ADDR__ 0x9B
#define __ALARM_ADDR__ 0x9B
#define __H2_ADDR__ 0x9B
#define __6E_ADDR__ 0x9B
#define __6C_ADDR__ 0x9A
#define __7E_ADDR__ 0x9A
#define __7C_ADDR__ 0x9A
#define __8E_ADDR__ 0x9A
#define __8C_ADDR__ 0x9A
#define __9E_ADDR__ 0x98
#define __9C_ADDR__ 0x98
#define __Celsius_ADDR__ 0x98
#define __mA_ADDR__ 0x98
#define __1E_ADDR__ 0x9A
#define __1C_ADDR__ 0x9A
#define __2E_ADDR__ 0x9A
#define __2C_ADDR__ 0x99
#define __3E_ADDR__ 0x99
#define __3C_ADDR__ 0x99
#define __4E_ADDR__ 0x99
#define __4C_ADDR__ 0x99
#define __5E_ADDR__ 0x99
#define __5C_ADDR__ 0x99
#define __T3_ADDR__ 0x99
#define __KPa_ADDR__ 0x93
#define __RH_ADDR__ 0x94
#define __13D_ADDR__ 0x94
#define __DP12_ADDR__ 0x94
#define __12D_ADDR__ 0x94
#define __DP11_ADDR__ 0x93
#define __11D_ADDR__ 0x93
#define __DP10_ADDR__ 0x93
#define __10D_ADDR__ 0x93
#define __REC_ADDR__ 0x93
#define __L2_ADDR__ 0x93
#define __6D_ADDR__ 0x93
#define __DP6_ADDR__ 0x92
#define __7D_ADDR__ 0x92
#define __DP7_ADDR__ 0x92
#define __8D_ADDR__ 0x92
#define __DP8_ADDR__ 0x92
#define __9D_ADDR__ 0x90
#define __S1_ADDR__ 0x90
#define __ppm_ADDR__ 0x90
#define __MPa_ADDR__ 0x90
#define __1D_ADDR__ 0x92
#define __STATUS_ADDR__ 0x92
#define __2D_ADDR__ 0x92
#define __S5_ADDR__ 0x91
#define __3D_ADDR__ 0x91
#define __COL_ADDR__ 0x91
#define __4D_ADDR__ 0x91
#define __S4_ADDR__ 0x91
#define __5D_ADDR__ 0x91
#define __T1_ADDR__ 0x91
#define __T2_ADDR__ 0x91

#define __S6_BIT__ 7
#define __13A_BIT__ 3
#define __13F_BIT__ 2
#define __12A_BIT__ 1
#define __12F_BIT__ 0
#define __11A_BIT__ 6
#define __11F_BIT__ 5
#define __10A_BIT__ 4
#define __10F_BIT__ 3
#define __SET_BIT__ 2
#define __H1_BIT__ 1
#define __6F_BIT__ 0
#define __6A_BIT__ 7
#define __7F_BIT__ 6
#define __7A_BIT__ 5
#define __8F_BIT__ 4
#define __8A_BIT__ 3
#define __9F_BIT__ 3
#define __9A_BIT__ 2
#define __S2_BIT__ 1
#define __S3_BIT__ 0
#define __1F_BIT__ 2
#define __1A_BIT__ 1
#define __2F_BIT__ 0
#define __2A_BIT__ 7
#define __3F_BIT__ 6
#define __3A_BIT__ 5
#define __4F_BIT__ 4
#define __4A_BIT__ 3
#define __5F_BIT__ 2
#define __5A_BIT__ 1
#define __T5_BIT__ 0
#define __S7_BIT__ 7
#define __13B_BIT__ 3
#define __13G_BIT__ 2
#define __12B_BIT__ 1
#define __12G_BIT__ 0
#define __11B_BIT__ 6
#define __11G_BIT__ 5
#define __10B_BIT__ 4
#define __10G_BIT__ 3
#define __COMM_BIT__ 2
#define __L1_BIT__ 1
#define __6G_BIT__ 0
#define __6B_BIT__ 7
#define __7G_BIT__ 6
#define __7B_BIT__ 5
#define __8G_BIT__ 4
#define __8B_BIT__ 3
#define __9G_BIT__ 3
#define __9B_BIT__ 2
#define __LX_BIT__ 1
#define __V_BIT__ 0
#define __1G_BIT__ 2
#define __1B_BIT__ 1
#define __2G_BIT__ 0
#define __2B_BIT__ 7
#define __3G_BIT__ 6
#define __3B_BIT__ 5
#define __4G_BIT__ 4
#define __4B_BIT__ 3
#define __5G_BIT__ 2
#define __5B_BIT__ 1
#define __T4_BIT__ 0
#define __S8_BIT__ 7
#define __13C_BIT__ 3
#define __13E_BIT__ 2
#define __12C_BIT__ 1
#define __12E_BIT__ 0
#define __11C_BIT__ 6
#define __11E_BIT__ 5
#define __10C_BIT__ 4
#define __10E_BIT__ 3
#define __ALARM_BIT__ 2
#define __H2_BIT__ 1
#define __6E_BIT__ 0
#define __6C_BIT__ 7
#define __7E_BIT__ 6
#define __7C_BIT__ 5
#define __8E_BIT__ 4
#define __8C_BIT__ 3
#define __9E_BIT__ 3
#define __9C_BIT__ 2
#define __Celsius_BIT__ 1
#define __mA_BIT__ 0
#define __1E_BIT__ 2
#define __1C_BIT__ 1
#define __2E_BIT__ 0
#define __2C_BIT__ 7
#define __3E_BIT__ 6
#define __3C_BIT__ 5
#define __4E_BIT__ 4
#define __4C_BIT__ 3
#define __5E_BIT__ 2
#define __5C_BIT__ 1
#define __T3_BIT__ 0
#define __KPa_BIT__ 7
#define __RH_BIT__ 3
#define __13D_BIT__ 2
#define __DP12_BIT__ 1
#define __12D_BIT__ 0
#define __DP11_BIT__ 6
#define __11D_BIT__ 5
#define __DP10_BIT__ 4
#define __10D_BIT__ 3
#define __REC_BIT__ 2
#define __L2_BIT__ 1
#define __6D_BIT__ 0
#define __DP6_BIT__ 7
#define __7D_BIT__ 6
#define __DP7_BIT__ 5
#define __8D_BIT__ 4
#define __DP8_BIT__ 3
#define __9D_BIT__ 3
#define __S1_BIT__ 2
#define __ppm_BIT__ 1
#define __MPa_BIT__ 0
#define __1D_BIT__ 2
#define __STATUS_BIT__ 1
#define __2D_BIT__ 0
#define __S5_BIT__ 7
#define __3D_BIT__ 6
#define __COL_BIT__ 5
#define __4D_BIT__ 4
#define __S4_BIT__ 3
#define __5D_BIT__ 2
#define __T1_BIT__ 1
#define __T2_BIT__ 0

int8 xdata __LCD_CurrentNumDisplayed[13] = {-1, -1, -1, -1, -1, -1, -1,
                                            -1, -1, -1, -1, -1, -1};

void LCD_Config()
{
    /**
     * LCDCFG CKSEL[7] VRLPSEL[3, not used] VLCDSEL[2:0]
     * CKSEL: 0 cpu clock, 1 external 32kHz
     * VLCDSEL: 111 for 1.0 * VCC
     */
    LCDCFG = 0x07;

    /**
     * LCDCFG2[3:0] pin mux for COM0-COM3
     * LCDCFG2[3]: SEG3PS, 0 for P1.2, 1 for P7.4
     * LCDCFG2[2]: SEG2PS, 0 for P1.3, 1 for P7.5
     * LCDCFG2[1]: SEG1PS, 0 for P1.4, 1 for P7.6
     * LCDCFG2[0]: SEG0PS, 0 for P1.5, 1 for P7.7
     */
    LCDCFG2 = 0x0f;

    /**
     * LCD REFRESH RATE = f(CLK)/(DBLEN[2:0] + COMLEN[19:0] + 1) * NUM_OF_COM
     * DBLEN = 2
     * COMLEN = 0x00c34d = 5005
     * NUM_OF_COM = 22
     */
    DBLEN = 0x02;
    COMLENH = 0x00;
    COMLENM = 0xc3;
    COMLENL = 0x4d;

    /*FLICKER RATE 60Hz*/
    BLINKRATE = 60;

    /* Enable LCD COMs and SEGs */
    COMON = 0x0f;
    SEGON1 = 0x0f;
    SEGON2 = 0xff;
    SEGON3 = 0xff;
    SEGON4 = 0xff;
    SEGON5 = 0x0f;

    /**
     * LCDCR ACTMODE[1:0]
     * 00: Normal mode
     * 01: Always on mode
     * 10: Always off mode
     * 11: Blinking mode
     *
     * LCDCR[0] is the ENABLE bit
     */
    LCDCR = 0x01;  // Enable LCD
}
const u8 code __LCD_DT_NUM_LOOKUP[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                                       0x6d, 0x7d, 0x07, 0x7f, 0x6f,
                                       0x00, 0x40, 0x79, 0x50};
const u8 code __LCD_DT_ADDR_LOOKUP[13][8][2] = {
    {{__1A_ADDR__, __1A_BIT__},
     {__1B_ADDR__, __1B_BIT__},
     {__1C_ADDR__, __1C_BIT__},
     {__1D_ADDR__, __1D_BIT__},
     {__1E_ADDR__, __1E_BIT__},
     {__1F_ADDR__, __1F_BIT__},
     {__1G_ADDR__, __1G_BIT__},
     {0x00, 0x00}},
    {{__2A_ADDR__, __2A_BIT__},
     {__2B_ADDR__, __2B_BIT__},
     {__2C_ADDR__, __2C_BIT__},
     {__2D_ADDR__, __2D_BIT__},
     {__2E_ADDR__, __2E_BIT__},
     {__2F_ADDR__, __2F_BIT__},
     {__2G_ADDR__, __2G_BIT__},
     {0x00, 0x00}},
    {{__3A_ADDR__, __3A_BIT__},
     {__3B_ADDR__, __3B_BIT__},
     {__3C_ADDR__, __3C_BIT__},
     {__3D_ADDR__, __3D_BIT__},
     {__3E_ADDR__, __3E_BIT__},
     {__3F_ADDR__, __3F_BIT__},
     {__3G_ADDR__, __3G_BIT__},
     {0x00, 0x00}},
    {{__4A_ADDR__, __4A_BIT__},
     {__4B_ADDR__, __4B_BIT__},
     {__4C_ADDR__, __4C_BIT__},
     {__4D_ADDR__, __4D_BIT__},
     {__4E_ADDR__, __4E_BIT__},
     {__4F_ADDR__, __4F_BIT__},
     {__4G_ADDR__, __4G_BIT__},
     {0x00, 0x00}},
    {{__5A_ADDR__, __5A_BIT__},
     {__5B_ADDR__, __5B_BIT__},
     {__5C_ADDR__, __5C_BIT__},
     {__5D_ADDR__, __5D_BIT__},
     {__5E_ADDR__, __5E_BIT__},
     {__5F_ADDR__, __5F_BIT__},
     {__5G_ADDR__, __5G_BIT__},
     {0x00, 0x00}},
    {{__6A_ADDR__, __6A_BIT__},
     {__6B_ADDR__, __6B_BIT__},
     {__6C_ADDR__, __6C_BIT__},
     {__6D_ADDR__, __6D_BIT__},
     {__6E_ADDR__, __6E_BIT__},
     {__6F_ADDR__, __6F_BIT__},
     {__6G_ADDR__, __6G_BIT__},
     {__DP6_ADDR__, __DP6_BIT__}},
    {{__7A_ADDR__, __7A_BIT__},
     {__7B_ADDR__, __7B_BIT__},
     {__7C_ADDR__, __7C_BIT__},
     {__7D_ADDR__, __7D_BIT__},
     {__7E_ADDR__, __7E_BIT__},
     {__7F_ADDR__, __7F_BIT__},
     {__7G_ADDR__, __7G_BIT__},
     {__DP7_ADDR__, __DP7_BIT__}},
    {{__8A_ADDR__, __8A_BIT__},
     {__8B_ADDR__, __8B_BIT__},
     {__8C_ADDR__, __8C_BIT__},
     {__8D_ADDR__, __8D_BIT__},
     {__8E_ADDR__, __8E_BIT__},
     {__8F_ADDR__, __8F_BIT__},
     {__8G_ADDR__, __8G_BIT__},
     {__DP8_ADDR__, __DP8_BIT__}},
    {{__9A_ADDR__, __9A_BIT__},
     {__9B_ADDR__, __9B_BIT__},
     {__9C_ADDR__, __9C_BIT__},
     {__9D_ADDR__, __9D_BIT__},
     {__9E_ADDR__, __9E_BIT__},
     {__9F_ADDR__, __9F_BIT__},
     {__9G_ADDR__, __9G_BIT__},
     {0x00, 0x00}},
    {{__10A_ADDR__, __10A_BIT__},
     {__10B_ADDR__, __10B_BIT__},
     {__10C_ADDR__, __10C_BIT__},
     {__10D_ADDR__, __10D_BIT__},
     {__10E_ADDR__, __10E_BIT__},
     {__10F_ADDR__, __10F_BIT__},
     {__10G_ADDR__, __10G_BIT__},
     {__DP10_ADDR__, __DP10_BIT__}},
    {{__11A_ADDR__, __11A_BIT__},
     {__11B_ADDR__, __11B_BIT__},
     {__11C_ADDR__, __11C_BIT__},
     {__11D_ADDR__, __11D_BIT__},
     {__11E_ADDR__, __11E_BIT__},
     {__11F_ADDR__, __11F_BIT__},
     {__11G_ADDR__, __11G_BIT__},
     {__DP11_ADDR__, __DP11_BIT__}},
    {{__12A_ADDR__, __12A_BIT__},
     {__12B_ADDR__, __12B_BIT__},
     {__12C_ADDR__, __12C_BIT__},
     {__12D_ADDR__, __12D_BIT__},
     {__12E_ADDR__, __12E_BIT__},
     {__12F_ADDR__, __12F_BIT__},
     {__12G_ADDR__, __12G_BIT__},
     {__DP12_ADDR__, __DP12_BIT__}},
    {{__13A_ADDR__, __13A_BIT__},
     {__13B_ADDR__, __13B_BIT__},
     {__13C_ADDR__, __13C_BIT__},
     {__13D_ADDR__, __13D_BIT__},
     {__13E_ADDR__, __13E_BIT__},
     {__13F_ADDR__, __13F_BIT__},
     {__13G_ADDR__, __13G_BIT__},
     {0x00, 0x00}},
};

void __LCD_SET_SEG(u8 addr, u8 bitPos, bit setVal)
{
    if (setVal)
    {
        (*(unsigned char volatile xdata*)((u16)LCD_ADDR_H | addr)) |=
            (1 << bitPos);
    }
    else
    {
        (*(unsigned char volatile xdata*)((u16)LCD_ADDR_H | addr)) &=
            ~(1 << bitPos);
    }
}

// to be consistant with the datasheet, the tubeindex starts from 1, not 0,
// range 1-13
void __LCD_SetDigitalTube(u8 tubeIndex, int8 num, bit withDP)
{
    if (tubeIndex < 1 || tubeIndex > 13)
        return;
    if (num == __LCD_CurrentNumDisplayed[tubeIndex - 1])
    {
        if (__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][0] != 0x00)
        {
            if (withDP)
            {
                __LCD_SET_SEG(__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][0],
                              __LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][1], 1);
            }
            else
            {
                __LCD_SET_SEG(__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][0],
                              __LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][1], 0);
            }
        }

        return;
    }
    else
    {
        u8 segments = __LCD_DT_NUM_LOOKUP[num > 13 ? 8 : num];
        u8 i;
        __LCD_CurrentNumDisplayed[tubeIndex - 1] = num;
        for (i = 0; i < 7; i++)
        {
            __LCD_SET_SEG(__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][i][0],
                          __LCD_DT_ADDR_LOOKUP[tubeIndex - 1][i][1],
                          (segments >> i) & 0x01);
        }
        if (__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][0] != 0x00)
        {
            if (withDP)
            {
                __LCD_SET_SEG(__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][0],
                              __LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][1], 1);
            }
            else
            {
                __LCD_SET_SEG(__LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][0],
                              __LCD_DT_ADDR_LOOKUP[tubeIndex - 1][7][1], 0);
            }
        }
    }
}

void LCD_SetSignalSign(int8 signal)
{
    __LCD_SET_SEG(__S1_ADDR__, __S1_BIT__, signal >= 0);
    __LCD_SET_SEG(__S2_ADDR__, __S2_BIT__, signal >= 1);
    __LCD_SET_SEG(__S3_ADDR__, __S3_BIT__, signal >= 2);
    __LCD_SET_SEG(__S4_ADDR__, __S4_BIT__, signal >= 3);
    __LCD_SET_SEG(__S5_ADDR__, __S5_BIT__, signal >= 4);
}

void LCD_SetState(int8 stateNum)
{
    __LCD_SET_SEG(__STATUS_ADDR__, __STATUS_BIT__, stateNum >= 0);
    __LCD_SetDigitalTube(1, stateNum < 0 ? 10 : stateNum, 0);
}

void LCD_SetTime(int8 hour, int8 minute, bit showColumn)
{
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
    {
        __LCD_SetDigitalTube(2, 12, 1);
        __LCD_SetDigitalTube(3, 13, 1);
        __LCD_SetDigitalTube(4, 13, 1);
        __LCD_SetDigitalTube(5, 10, 0);
        return;
    }
    __LCD_SetDigitalTube(2, (hour / 10) == 0 ? 10 : hour / 10, 0);
    __LCD_SetDigitalTube(3, hour % 10, 0);
    __LCD_SetDigitalTube(4, minute / 10, 0);
    __LCD_SetDigitalTube(5, minute % 10, 0);
    __LCD_SET_SEG(__COL_ADDR__, __COL_BIT__, showColumn);
}

void LCD_SetBatteryLevel(int8 level)
{
    __LCD_SET_SEG(__T1_ADDR__, __T1_BIT__, level >= 0);
    __LCD_SET_SEG(__T2_ADDR__, __T2_BIT__, level >= 1);
    __LCD_SET_SEG(__T3_ADDR__, __T3_BIT__, level >= 2);
    __LCD_SET_SEG(__T4_ADDR__, __T4_BIT__, level >= 3);
    __LCD_SET_SEG(__T5_ADDR__, __T5_BIT__, level >= 4);
}

void LCD_SetStateLabels(u8 stateBitmask)
{
    __LCD_SET_SEG(__SET_ADDR__, __SET_BIT__, stateBitmask & 0x01);
    __LCD_SET_SEG(__COMM_ADDR__, __COMM_BIT__, stateBitmask & 0x02);
    __LCD_SET_SEG(__ALARM_ADDR__, __ALARM_BIT__, stateBitmask & 0x04);
    __LCD_SET_SEG(__REC_ADDR__, __REC_BIT__, stateBitmask & 0x08);

    __LCD_SET_SEG(__H1_ADDR__, __H1_BIT__, stateBitmask & 0x10);
    __LCD_SET_SEG(__H2_ADDR__, __H2_BIT__, stateBitmask & 0x20);
    __LCD_SET_SEG(__L1_ADDR__, __L1_BIT__, stateBitmask & 0x40);
    __LCD_SET_SEG(__L2_ADDR__, __L2_BIT__, stateBitmask & 0x80);
}

void LCD_SetTemperature(int16 num)
{
    if (num < -550 || num > 1250)
    {
        __LCD_SetDigitalTube(6, 12, 1);
        __LCD_SetDigitalTube(7, 13, 1);
        __LCD_SetDigitalTube(8, 13, 1);
        __LCD_SetDigitalTube(9, 10, 0);
        return;
    }
    else
    {
        if (num < 0)
        {
            idata u8 d1 = (-num) / 100;
            idata u8 d2 = ((-num) / 10) % 10;
            idata u8 d3 = (-num) % 10;
            if (d1)
            {
                __LCD_SetDigitalTube(6, 11, 0);
                __LCD_SetDigitalTube(7, d1, 0);
                __LCD_SetDigitalTube(8, d2, 1);
                __LCD_SetDigitalTube(9, d3, 0);
            }
            else
            {
                __LCD_SetDigitalTube(6, 10, 0);
                __LCD_SetDigitalTube(7, 11, 0);
                __LCD_SetDigitalTube(8, d2, 1);
                __LCD_SetDigitalTube(9, d3, 0);
            }
        }
        else
        {
            idata u8 d1 = num / 1000;
            idata u8 d2 = (num / 100) % 10;
            __LCD_SetDigitalTube(6, d1 ? d1 : 10, 0);
            __LCD_SetDigitalTube(7, d2 ? d2 : 10, 0);
            __LCD_SetDigitalTube(8, (num / 10) % 10, 1);
            __LCD_SetDigitalTube(9, num % 10, 0);
        }
    }
}

void LCD_SetHumidity(u16 num)
{
    if (num > 9999)
    {
        __LCD_SetDigitalTube(10, 12, 1);
        __LCD_SetDigitalTube(11, 13, 1);
        __LCD_SetDigitalTube(12, 13, 1);
        __LCD_SetDigitalTube(13, 10, 0);
        printf("Invalid humidity, error 9999: %u\n", num);
        return;
    }
    else
    {
        idata u8 d1 = num / 1000;
        idata u8 d2 = (num / 100) % 10;
        __LCD_SetDigitalTube(10, d1 ? d1 : 10, 0);
        __LCD_SetDigitalTube(11, d2 ? d2 : 10, 0);
        __LCD_SetDigitalTube(12, (num / 10) % 10, 1);
        __LCD_SetDigitalTube(13, num % 10, 0);
    }
}

void LCD_SetUnits(u8 unitBitmask)  // tested
{
    __LCD_SET_SEG(__Celsius_ADDR__, __Celsius_BIT__, unitBitmask & 0x01);
    __LCD_SET_SEG(__LX_ADDR__, __LX_BIT__, unitBitmask & 0x02);
    __LCD_SET_SEG(__V_ADDR__, __V_BIT__, unitBitmask & 0x04);
    __LCD_SET_SEG(__mA_ADDR__, __mA_BIT__, unitBitmask & 0x08);

    __LCD_SET_SEG(__RH_ADDR__, __RH_BIT__, unitBitmask & 0x10);
    __LCD_SET_SEG(__ppm_ADDR__, __ppm_BIT__, unitBitmask & 0x20);
    __LCD_SET_SEG(__MPa_ADDR__, __MPa_BIT__, unitBitmask & 0x40);
    __LCD_SET_SEG(__KPa_ADDR__, __KPa_BIT__, unitBitmask & 0x80);
}

void LCD_SetTriangle(u8 triangleBitmask)
{
    __LCD_SET_SEG(__S6_ADDR__, __S6_BIT__, triangleBitmask & 0x01);
    __LCD_SET_SEG(__S7_ADDR__, __S7_BIT__, triangleBitmask & 0x02);
    __LCD_SET_SEG(__S8_ADDR__, __S8_BIT__, triangleBitmask & 0x04);
}

void LCD_ALL()
{
    C0SEGV0 = 0xFF;
    C0SEGV1 = 0xFF;
    C0SEGV2 = 0xFF;
    C0SEGV3 = 0xFF;
    C0SEGV4 = 0xFF;

    C1SEGV0 = 0xFF;
    C1SEGV1 = 0xFF;
    C1SEGV2 = 0xFF;
    C1SEGV3 = 0xFF;
    C1SEGV4 = 0xFF;

    C2SEGV0 = 0xFF;
    C2SEGV1 = 0xFF;
    C2SEGV2 = 0xFF;
    C2SEGV3 = 0xFF;
    C2SEGV4 = 0xFF;

    C3SEGV0 = 0xFF;
    C3SEGV1 = 0xFF;
    C3SEGV2 = 0xFF;
    C3SEGV3 = 0xFF;
    C3SEGV4 = 0xFF;
}

void LCD_CLEAR()
{
    C0SEGV0 = 0x00;
    C0SEGV1 = 0x00;
    C0SEGV2 = 0x00;
    C0SEGV3 = 0x00;
    C0SEGV4 = 0x00;

    C1SEGV0 = 0x00;
    C1SEGV1 = 0x00;
    C1SEGV2 = 0x00;
    C1SEGV3 = 0x00;
    C1SEGV4 = 0x00;

    C2SEGV0 = 0x00;
    C2SEGV1 = 0x00;
    C2SEGV2 = 0x00;
    C2SEGV3 = 0x00;
    C2SEGV4 = 0x00;

    C3SEGV0 = 0x00;
    C3SEGV1 = 0x00;
    C3SEGV2 = 0x00;
    C3SEGV3 = 0x00;
    C3SEGV4 = 0x00;
}