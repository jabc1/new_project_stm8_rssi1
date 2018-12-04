#include "function.h"
#include "table.h"
#include "DigitalTube.h"
#include "LCD.h"
#include <stdlib.h>
#include <string.h>
#include "stm8l15x_lcd.h"
/*!
 * @file function.c
 * @brief 主要实现对函数的查表执行便于维护
 * @author jason
 * @date 2018-11-21
 * @version ver1.0
 */

const struct attr_exe_data SysAttrTable[] =
{
    {0x01,test_function},
    {0x02,State_function},
    {0x03,SoftVer_funtion}, 
};

u8 GetFunctionNum()
{
    return ( sizeof(SysAttrTable) / sizeof(struct attr_exe_data) );
}

bool Msg_deal(u8 *data,u16 len)
{
    u8 i,count;
    _Cmd *pBuf;
    const struct attr_exe_data * p_attr_exe = SysAttrTable;
    pBuf = (_Cmd *)data;
    count = GetFunctionNum();
    
    for(i=0;i<count;i++)
    {
        if(p_attr_exe->cmd == pBuf->head)
        {
            if(p_attr_exe->exe_attr != NULL)
            {
                p_attr_exe->exe_attr(pBuf->head,pBuf->data,sizeof(pBuf->data));
                return true;
            }
        }
        p_attr_exe++;
    }
    return false;
}

void test_function(u8 cmd,u8 *data,u16 len)
{
    ;
}

void State_function(u8 cmd,u8 *data,u16 len)
{
    ;
}

void SoftVer_funtion(u8 cmd,u8 *data,u16 len)
{
    ;
}

void cmd_Operation(u8 *segment_ptr[])
{
    if(strcmp((char *)(segment_ptr[1]), "0")== 0)
    {
      LCD_WriteNum4(0);
    }
    else if(strcmp((char *)(segment_ptr[1]), "1")== 0)
    {
      LCD_WriteNum4(1);
    }
    else if(strcmp((char *)(segment_ptr[1]), "2")== 0)
    {
      LCD_WriteNum4(2);
    }
    else if(strcmp((char *)(segment_ptr[1]), "3")== 0)
    {
      LCD_WriteNum4(3);
    }
        else if(strcmp((char *)(segment_ptr[1]), "4")== 0)
    {
        LCD_WriteNum4(4);
    }
        else if(strcmp((char *)(segment_ptr[1]), "5")== 0)
    {
      LCD_WriteNum4(5);
    }
        else if(strcmp((char *)(segment_ptr[1]), "6")== 0)
    {
      LCD_WriteNum4(6);
    }
        else if(strcmp((char *)(segment_ptr[1]), "7")== 0)
    {
      LCD_WriteNum4(7);
    }
        else if(strcmp((char *)(segment_ptr[1]), "8")== 0)
    {
      LCD_WriteNum4(8);
    }
        else if(strcmp((char *)(segment_ptr[1]), "9")== 0)
    {
      LCD_WriteNum4(9);
    }
        
    
        

}
//命令格式
//head=test,cmd=test
void vfunction(u8 *data)
{
    char *token,*segment_ptr[4],i;
    for(i = 0; i < 4; i++)	
    {       
        segment_ptr[i] = NULL;  
    }
    i=0;
    token = strtok((char *)data, ",=");      
    while(token != NULL && i < 4)      
    {           
        segment_ptr[i] = token;
        i++;            
        token = strtok(NULL,",=");                 
    }
    
    if((strcmp((char *)(segment_ptr[0]), "head")== 0)||(strcmp((char *)(segment_ptr[2]), "cmd")== 0))
    {
        cmd_Operation(segment_ptr);
    }

}









