#ifndef _a7106gpio_h
#define _a7106gpio_h
#include "stm8l15x_gpio.h"
/*
SCS---->PB4
SCK---->PB5
SDIO--->(MOSI<---PB6/PB7-->MISO)
CKO---->PD5
GIO1--->PD4
GIO2--->PF0
//MODE--->PC1

*/
#define     CSCPROT          GPIOB
#define     CSCPROT_Pin      GPIO_Pin_4
#define     SCKPROT          GPIOB
#define     SCKPROT_Pin      GPIO_Pin_5

#if 1
#define     SDIOPROT        GPIOB
#define     SDIOPROT_Pin    GPIO_Pin_6
#else
#define     MOSIPROT        GPIOB
#define     MOSIPROT_Pin    GPIO_Pin_6
#define     MISOPROT        GPIOB
#define     MISOPROT_Pin    GPIO_Pin_7
#endif

#define     CKOPROT          GPIOD
#define     CKOPROT_Pin      GPIO_Pin_5
#define     GIO1PROT         GPIOF
#define     GIO1PROT_Pin     GPIO_Pin_0
#define     GIO2PROT         GPIOD
#define     GIO2PROT_Pin     GPIO_Pin_4

#define     LED             GPIOA
#define     LED_Pin         GPIO_Pin_6

#define     SET_GPIO_OUT(x)        GPIO_Init(x,x##_Pin, GPIO_Mode_Out_PP_High_Fast)
#define     SET_GPIO_IN(x)         GPIO_Init(x,x##_Pin, GPIO_Mode_In_PU_No_IT)   
#define     SET_GPIO_H(x)          GPIO_SetBits(x,x##_Pin) 
#define     SET_GPIO_L(x)          GPIO_ResetBits(x,x##_Pin) 
#define     Read_GPIO(x)           GPIO_ReadInputDataBit(x,x##_Pin) 



void A7106_GPIO_init(void);

#endif





