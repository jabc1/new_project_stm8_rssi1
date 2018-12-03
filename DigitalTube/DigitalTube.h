#ifndef _DigitalTube_h
#define _DigitalTube_h
#include "a7106gpio.h"
#include "stm8l15x_gpio.h"
/*
COM1  --------  PE7
COM2  --------  PC0
COM3  --------  PD7
COM4  --------  PB3
A-----------PE6
B-----------PD6
C-----------PB1
D-----------PD3
E-----------PD2
F-----------PC7
G-----------PB2
pint-------PB0
*/

#define     COM1             GPIOE
#define     COM1_Pin         GPIO_Pin_7
#define     COM2             GPIOC
#define     COM2_Pin         GPIO_Pin_0
#define     COM3             GPIOD
#define     COM3_Pin         GPIO_Pin_7
#define     COM4             GPIOB
#define     COM4_Pin         GPIO_Pin_3

#define     COMA             GPIOE
#define     COMA_Pin         GPIO_Pin_6
#define     COMB             GPIOD
#define     COMB_Pin         GPIO_Pin_6
#define     COMC             GPIOB
#define     COMC_Pin         GPIO_Pin_1
#define     COMD             GPIOD
#define     COMD_Pin         GPIO_Pin_3
#define     COME             GPIOD
#define     COME_Pin         GPIO_Pin_2
#define     COMF             GPIOC
#define     COMF_Pin         GPIO_Pin_7
#define     COMG             GPIOB
#define     COMG_Pin         GPIO_Pin_2
#define     COMPint          GPIOB
#define     COMPint_Pin      GPIO_Pin_0


void Digital_TubeInit(void);

#endif

