#include "KeyExt.h"

void Key_Config()
{
    ExtInt_Config(EXT_INT1, EXT_MODE_Fall, Priority_0);
    GPIO_Config(GPIO_P3, GPIO_Pin_0, GPIO_PullUp);
}

void INT1_ISR_Handler(void) interrupt INT1_VECTOR
{
    // awaken from lp mode
    // update state of FSM
}