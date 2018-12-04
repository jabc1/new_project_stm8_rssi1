#ifndef _LCD_h
#define _LCD_h
#include "a7106gpio.h"
#include "stm8l15x_lcd.h"

/*
COM1------PA4
COM2------PA5
COM3------PA6
COM4------PD1
*/
#define         uint8           uint8_t

#define         LCDCOM1         GPIOA      
#define         LCDCOM1_Pin     GPIO_Pin_4
#define         LCDCOM2         GPIOA      
#define         LCDCOM2_Pin     GPIO_Pin_5
#define         LCDCOM3         GPIOA      
#define         LCDCOM3_Pin     GPIO_Pin_6
#define         LCDCOM4         GPIOD      
#define         LCDCOM4_Pin     GPIO_Pin_1

#define         SET_GPIO_OUT_H(x)        GPIO_Init(x,x##_Pin, GPIO_Mode_Out_PP_High_Fast)
extern uint8_t  LCM_Num[];

extern const uint8 LCD_CodeTable[];
void LCD_init(void);
void led_show(uint16_t x);
void LCD_WriteNum1(u8 bNum);
void LCD_WriteNum2(u8 bNum);
void LCD_WriteNum3(u8 bNum);
void LCD_WriteNum4(u8 bNum);
#endif

