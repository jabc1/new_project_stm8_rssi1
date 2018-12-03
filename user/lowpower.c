#include "lowpower.h"
#include "time.h"

/*!
 * @file lowpower.c
 * @brief 低功耗功能实现
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

void Inti_lowpower()
{
    CLK_LSEConfig(CLK_LSE_ON);//RTC时钟源选择
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//RTC时钟分频
    while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);//等待时钟源就绪
    
    RTC_WakeUpCmd(DISABLE);//关闭RTC唤醒
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTC时钟门控使能
    RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//RTC唤醒时钟分频
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//RTC唤醒中断使能
    RTC_SetWakeUpCounter(2047*2);//1/(32.768/16)*2048=1S.
    ITC_SetSoftwarePriority(RTC_IRQn, ITC_PriorityLevel_3);//优先级

    PWR_UltraLowPowerCmd(ENABLE);//超低功耗
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//唤醒定时器中断使能
    RTC_WakeUpCmd(ENABLE);//RTC唤醒使能
}

void Delay(uint16_t num)
{
    uint16_t i;
    for(i=0;i<num;i++)
        ;
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    RTC_WakeUpCmd(DISABLE);
    GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
    //tiem2_test();
    RTC_ClearITPendingBit(RTC_IT_WUT);  
    RTC_WakeUpCmd(ENABLE);
    
}





