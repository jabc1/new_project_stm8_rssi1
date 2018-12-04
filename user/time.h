#ifndef _time_h
#define _time_h
#include "stm8l15x_tim2.h"

#pragma pack(push, 1)
typedef struct
{
    uint8_t flag;
    uint16_t count;
    uint8_t sec;
    uint8_t min;
    uint8_t hours;
}TIME2;
#pragma pack(pop)

extern TIME2   Time2;

void Init_time2(void);
void tiem2_test(void);


#endif

