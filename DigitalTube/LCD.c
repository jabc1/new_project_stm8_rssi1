#include "LCD.h"

uint8_t  LCM_Num[10]={0x5f,0x06,0x3b,0x2f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void LCD_init()
{
  /*
  SET_GPIO_OUT_H(LCDCOM1);
  SET_GPIO_OUT_H(LCDCOM2);
  SET_GPIO_OUT_H(LCDCOM3);
  SET_GPIO_OUT_H(LCDCOM4);
  */
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
  LCD_Init(LCD_Prescaler_1, LCD_Divider_31, LCD_Duty_1_4, 
  LCD_Bias_1_3,   LCD_VoltageSource_External);
  LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);
  LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0x7F);

  LCD_ContrastConfig(LCD_Contrast_3V0);
  LCD_DeadTimeConfig(LCD_DeadTime_0);
  LCD_PulseOnDurationConfig(LCD_PulseOnDuration_7);//LCD_PulseOnDuration_1
  LCD_Cmd(ENABLE);


 
}

void LCD_SHOW(unsigned char num)
{
  ;
}








