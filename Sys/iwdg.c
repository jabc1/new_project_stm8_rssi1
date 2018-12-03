#include "iwdg.h"
/*!
 * @file iwdg.c
 * @brief 实现看门狗功能
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

void IWDG_Init(void)
{
    CLK_LSICmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);
    CLK_BEEPClockConfig(CLK_BEEPCLKSource_LSI);
    CLK_PeripheralClockConfig(CLK_Peripheral_BEEP, ENABLE);
    IWDG_Enable();//记得先使能
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    IWDG_SetReload((uint8_t)254);//RELOAD_VALUE=254  1.724s
    IWDG_ReloadCounter();
}





