#ifndef _rtc_h
#define _rtc_h
#include "stm8l15x_rtc.h"
void Init_rtc(void);
void rtc_get_time(char *buf);
void rtc_get_date(char *buf);
#endif

