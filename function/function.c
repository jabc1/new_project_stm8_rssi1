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

void LCD_WriteNum1(u8 bNum)
{
  
  //COM0      
  LCD->RAM[LCD_RAMRegister_0] &= (~0x01);//1<<0
  LCD->RAM[LCD_RAMRegister_0] |= (uint8_t)((LCM_Num[bNum]&0x01));// 1a
  //COM1  
  LCD->RAM[LCD_RAMRegister_3] &= (~0x10);//1<<4
  LCD->RAM[LCD_RAMRegister_3] |= (uint8_t)((LCM_Num[bNum]&0x40)>> 2);// 1g
  LCD->RAM[LCD_RAMRegister_3] &= (~0x20);//1<<5
  LCD->RAM[LCD_RAMRegister_3] |= (uint8_t)((LCM_Num[bNum]&0x02)<< 4);// 1b
  //COM2  
  LCD->RAM[LCD_RAMRegister_7] &= (~0x02);//1<<1
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x20)>>4);// 1f
  LCD->RAM[LCD_RAMRegister_7] &= (~0x01);//1<<0
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x10) >> 4);// 1e 
  //COM3
  LCD->RAM[LCD_RAMRegister_10] &= (~0x10);//1<<4
  LCD->RAM[LCD_RAMRegister_10] |= (uint8_t)((LCM_Num[bNum]&0x08)<< 1);// 1d 
  LCD->RAM[LCD_RAMRegister_10] &= (~0x20);//1<<5
  LCD->RAM[LCD_RAMRegister_10] |= (uint8_t)((LCM_Num[bNum]&0x04)<< 3);// 1c 
  
}
void LCD_WriteNum2(u8 bNum)
{
  
  //COM0      
  LCD->RAM[LCD_RAMRegister_0] &= (~0x04);//1<<3
  LCD->RAM[LCD_RAMRegister_0] |= (uint8_t)((LCM_Num[bNum]&0x04));// 1a
  //COM1  
  LCD->RAM[LCD_RAMRegister_3] &= (~0x10);//1<<6
  LCD->RAM[LCD_RAMRegister_3] |= (uint8_t)((LCM_Num[bNum]&0x40)>> (2+4));// 1g
  LCD->RAM[LCD_RAMRegister_3] &= (~0x20);//1<<7
  LCD->RAM[LCD_RAMRegister_3] |= (uint8_t)((LCM_Num[bNum]&0x02)<< (4+3));// 1b
  //COM2  
  LCD->RAM[LCD_RAMRegister_7] &= (~0x02);//1<<2
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x20)>>4);// 1f
  LCD->RAM[LCD_RAMRegister_7] &= (~0x01);//1<<3
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x10) >> 4);// 1e 
  //COM3
  LCD->RAM[LCD_RAMRegister_10] &= (~0x10);//1<<6
  LCD->RAM[LCD_RAMRegister_10] |= (uint8_t)((LCM_Num[bNum]&0x08)<< 1);// 1d 
  LCD->RAM[LCD_RAMRegister_10] &= (~0x20);//1<<7
  LCD->RAM[LCD_RAMRegister_10] |= (uint8_t)((LCM_Num[bNum]&0x04)<< 3);// 1c 
  
}
void cmd_Operation(u8 *segment_ptr[])
{
    uint16_t t,temp1;
    char i=0,j=0;
    if(strcmp((char *)(segment_ptr[1]), "send")== 0)
    {
        LCD_WriteNum1(0);
        UART1_SendStr("head send mode!");
    }
    else if(strcmp((char *)(segment_ptr[1]), "receive")== 0)
    {
        UART1_SendStr("head receive mode!");
      
        for(i=0;i<13;i++)
        {
          for(j=0;j<8;j++)
          {
            LCD->RAM[i] &= ~(1<<j);
          }
        }
    }
    if(strcmp((char *)(segment_ptr[1]), "clear")== 0)
    {
      UART1_SendStr("cmd clear mode!");
    }
    if(strcmp((char *)(segment_ptr[1]), "0")== 0)
    {
      LCD_WriteNum1(0);
      //LCD_WriteNum2(0);
    }
    else if(strcmp((char *)(segment_ptr[1]), "1")== 0)
    {
      LCD_WriteNum1(1);
    }
    else if(strcmp((char *)(segment_ptr[1]), "2")== 0)
    {
      LCD_WriteNum1(2);
    }
    else if(strcmp((char *)(segment_ptr[1]), "3")== 0)
    {
      LCD_WriteNum1(3);
    }
        else if(strcmp((char *)(segment_ptr[1]), "4")== 0)
    {
      LCD_WriteNum1(4);
    }
        else if(strcmp((char *)(segment_ptr[1]), "5")== 0)
    {
      LCD_WriteNum1(5);
    }
        else if(strcmp((char *)(segment_ptr[1]), "6")== 0)
    {
      LCD_WriteNum1(6);
    }
        else if(strcmp((char *)(segment_ptr[1]), "7")== 0)
    {
      LCD_WriteNum1(7);
    }
        
        else if(strcmp((char *)(segment_ptr[1]), "8")== 0)
    {
      LCD_WriteNum1(8);
    }
        else if(strcmp((char *)(segment_ptr[1]), "9")== 0)
    {
      LCD_WriteNum1(9);
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









