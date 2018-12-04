#include "LCD.h"
/*
  LCD->RAM[LCD_RAMRegister_0] |= 1<<3;// doc
  LCD->RAM[LCD_RAMRegister_0] |= 1<<1;// oc
  LCD->RAM[LCD_RAMRegister_0] |= 1<<5;// ph
  LCD->RAM[LCD_RAMRegister_0] |= 1<<7;// us
  */
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
  LCD_Init(LCD_Prescaler_1, LCD_Divider_16, LCD_Duty_1_4, 
  LCD_Bias_1_3,   LCD_VoltageSource_External);
  LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);
  LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0x7F);

  LCD_ContrastConfig(LCD_Contrast_3V0);
  LCD_DeadTimeConfig(LCD_DeadTime_0);
  LCD_PulseOnDurationConfig(LCD_PulseOnDuration_7);//LCD_PulseOnDuration_1
  LCD_Cmd(ENABLE);
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
  LCD->RAM[LCD_RAMRegister_0] &= (~0x04);//1<<2
  LCD->RAM[LCD_RAMRegister_0] |= (uint8_t)((LCM_Num[bNum]&0x01)<<2);// 1a
  //COM1  
  LCD->RAM[LCD_RAMRegister_3] &= (~0x40);//1<<6
  LCD->RAM[LCD_RAMRegister_3] |= (uint8_t)((LCM_Num[bNum]&0x40));// 1g 
  LCD->RAM[LCD_RAMRegister_3] &= (~0x80);//1<<7
  LCD->RAM[LCD_RAMRegister_3] |= (uint8_t)((LCM_Num[bNum]&0x02) << 6);// 1b
  //COM2  
  LCD->RAM[LCD_RAMRegister_7] &= (~0x08);//1<<3
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x20)>>2);// 1f
  LCD->RAM[LCD_RAMRegister_7] &= (~0x04);//1<<2
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x10) >> 2);// 1e 
  //COM3
  LCD->RAM[LCD_RAMRegister_10] &= (~0x40);//1<<6
  LCD->RAM[LCD_RAMRegister_10] |= (uint8_t)((LCM_Num[bNum]&0x08)<< 3);// 1d 
  LCD->RAM[LCD_RAMRegister_10] &= (~0x80);//1<<7
  LCD->RAM[LCD_RAMRegister_10] |= (uint8_t)((LCM_Num[bNum]&0x04)<< 5);// 1c   
}
void LCD_WriteNum3(u8 bNum)
{
  LCD->RAM[LCD_RAMRegister_0] &= (~0x10);//1<<4
  LCD->RAM[LCD_RAMRegister_0] |= (uint8_t)((LCM_Num[bNum]&0x01)<<4);// 1a
  LCD->RAM[LCD_RAMRegister_4] &= (~0x01);//1<<0
  LCD->RAM[LCD_RAMRegister_4] |= (uint8_t)((LCM_Num[bNum]&0x40)>>6);// 1g 
  LCD->RAM[LCD_RAMRegister_4] &= (~0x02);//1<<1
  LCD->RAM[LCD_RAMRegister_4] |= (uint8_t)((LCM_Num[bNum]&0x02));// 1b
  LCD->RAM[LCD_RAMRegister_7] &= (~0x20);//1<<5
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x20));// 1f
  LCD->RAM[LCD_RAMRegister_7] &= (~0x10);//1<<4
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x10));// 1e 
  LCD->RAM[LCD_RAMRegister_11] &= (~0x01);//1<<0
  LCD->RAM[LCD_RAMRegister_11] |= (uint8_t)((LCM_Num[bNum]&0x08)>> 3);// 1d 
  LCD->RAM[LCD_RAMRegister_11] &= (~0x02);//1<<1
  LCD->RAM[LCD_RAMRegister_11] |= (uint8_t)((LCM_Num[bNum]&0x04)>> 1);// 1c   
}
void LCD_WriteNum4(u8 bNum)
{
  //COM0      
  LCD->RAM[LCD_RAMRegister_0] &= (~0x40);//1<<6
  LCD->RAM[LCD_RAMRegister_0] |= (uint8_t)((LCM_Num[bNum]&0x01)<<6);// 1a
  //COM1  
  LCD->RAM[LCD_RAMRegister_4] &= (~0x04);//1<<2
  LCD->RAM[LCD_RAMRegister_4] |= (uint8_t)((LCM_Num[bNum]&0x40)>>4);// 1g 
  LCD->RAM[LCD_RAMRegister_4] &= (~0x08);//1<<3
  LCD->RAM[LCD_RAMRegister_4] |= (uint8_t)((LCM_Num[bNum]&0x02)<<2);// 1b
  //COM2  
  LCD->RAM[LCD_RAMRegister_7] &= (~0x80);//1<<7
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x20)<<2);// 1f
  LCD->RAM[LCD_RAMRegister_7] &= (~0x40);//1<<6
  LCD->RAM[LCD_RAMRegister_7] |= (uint8_t)((LCM_Num[bNum]&0x10)<<2);// 1e 
  //COM3
  LCD->RAM[LCD_RAMRegister_11] &= (~0x04);//1<<2
  LCD->RAM[LCD_RAMRegister_11] |= (uint8_t)((LCM_Num[bNum]&0x08)>>1);// 1d 
  LCD->RAM[LCD_RAMRegister_11] &= (~0x08);//1<<3
  LCD->RAM[LCD_RAMRegister_11] |= (uint8_t)((LCM_Num[bNum]&0x04)<<1);// 1c   
}

void led_show(uint16_t x)
{
  unsigned char s[4];
  s[0]=x/1000;//四位数的 千位
  s[1]=x/100%10;//四位数的 百位
  s[2]=x/10%10;//四位数的 十位
  s[3]=x%10;//四位数的 个位
  
  LCD_WriteNum1(s[0]);
  LCD_WriteNum2(s[1]);
  LCD_WriteNum3(s[2]);
  LCD_WriteNum4(s[3]);
}




