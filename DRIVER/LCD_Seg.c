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
    LCDCFG2 = 0x0B;

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
    SEGON2 = 0x30;
    SEGON3 = 0xa6;
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