#include "rtc.h"
#include "uart.h"
#include "fifo.h"
/*!
 * @file rtc.c
 * @brief 芯片rtc功能实现
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

void Init_rtc(void)
{
	RTC_InitTypeDef RTC_InitStr;
	RTC_TimeTypeDef RTC_TimeStr;
	RTC_DateTypeDef RTC_DateStr;
 
#if 0
	/* LSI *///38k
	CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
	CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
 
	RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
	RTC_InitStr.RTC_AsynchPrediv = 0x7C;
	RTC_InitStr.RTC_SynchPrediv = 0x012F;
	RTC_Init(&RTC_InitStr);
#else
	/* LSE *///32.768k
	CLK_LSEConfig(CLK_LSE_ON);
	while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);
	CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
	CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
 
	RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
	RTC_InitStr.RTC_AsynchPrediv = 127;
	RTC_InitStr.RTC_SynchPrediv = 255;
	RTC_Init(&RTC_InitStr);
#endif
 
	RTC_TimeStructInit(&RTC_TimeStr);
	RTC_TimeStr.RTC_Hours = 00;
	RTC_TimeStr.RTC_Minutes = 00;
	RTC_TimeStr.RTC_Seconds = 00;
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
 
	RTC_DateStructInit(&RTC_DateStr);
	RTC_DateStr.RTC_WeekDay = RTC_Weekday_Saturday;
	RTC_DateStr.RTC_Date = 13;
	RTC_DateStr.RTC_Month = RTC_Month_October;
	RTC_DateStr.RTC_Year = 18;
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);
}
 
void rtc_get_time(char *buf)
{
	RTC_TimeTypeDef RTC_TimeStr;
 
	while (RTC_WaitForSynchro() != SUCCESS);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);

    sprintf(buf, "%02d:%02d:%02d",
		(RTC_TimeStr.RTC_Hours & 0xff), (RTC_TimeStr.RTC_Minutes & 0xff), (RTC_TimeStr.RTC_Seconds & 0xff));
}
 
void rtc_get_date(char *buf)
{
	RTC_DateTypeDef RTC_DateStr;
 
	while (RTC_WaitForSynchro() != SUCCESS);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
    
	sprintf(buf, "%04d-%02d-%02d:%02d",
		(RTC_DateStr.RTC_Year & 0xff) + 2000, RTC_DateStr.RTC_Month & 0xff,  \
		 RTC_DateStr.RTC_Date & 0xff , RTC_DateStr.RTC_WeekDay & 0xff);
}







