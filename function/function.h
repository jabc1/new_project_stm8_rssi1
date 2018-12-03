#ifndef _function_h
#define _function_h
#include  "base.h"

struct attr_exe_data
{
    u32 cmd;
    void (*exe_attr)(u8 ,u8 *,u16);
};

#pragma pack(push,1)
typedef struct{
    u8 head;
    u8 len;
    u8 data[100];
    u8 crc;
}_Cmd;
#pragma pack(pop)


void vfunction(u8 *data);

u8 GetFunctionNum(void);


bool Msg_deal(u8 *data,u16 len);


void test_function(u8 cmd,u8 *data,u16 len);
void State_function(u8 cmd,u8 *data,u16 len);
void SoftVer_funtion(u8 cmd,u8 *data,u16 len);

#endif



