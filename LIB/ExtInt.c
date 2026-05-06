#include "ExtInt.h"

void ExtInt_Config(u8 extNum, bit mode, int8 priority)
{
    EXTI_InitTypeDef Exti_InitStructure;

    Exti_InitStructure.EXTI_Mode = mode;
    Ext_Inilize(extNum, &Exti_InitStructure);
    switch (extNum)
    {
        case EXT_INT0:
            if (priority < 0)
                NVIC_INT0_Init(DISABLE, NULL);
            else
                NVIC_INT0_Init(ENABLE, priority);
            break;
        case EXT_INT1:
            if (priority < 0)
                NVIC_INT1_Init(DISABLE, NULL);
            else
                NVIC_INT1_Init(ENABLE, priority);
            break;
        case EXT_INT2:
            if (priority < 0)
                NVIC_INT2_Init(DISABLE, NULL);
            else
                NVIC_INT2_Init(ENABLE, priority);
            break;
        case EXT_INT3:
            if (priority < 0)
                NVIC_INT3_Init(DISABLE, NULL);
            else
                NVIC_INT3_Init(ENABLE, priority);
            break;
        case EXT_INT4:
            if (priority < 0)
                NVIC_INT4_Init(DISABLE, NULL);
            else
                NVIC_INT4_Init(ENABLE, priority);
            break;
        default:
            break;
    }
}