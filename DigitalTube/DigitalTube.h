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
#define         a               0x01
#define         b               0x02
#define         c               0x04
#define         d               0x08
#define         e               0x10
#define         f               0x20
#define         g               0x40
#define         pint            0x80

#define         One             a+b
#define         Two             a+b+g+e+d
#define         Three           a+b+g+c+d
#define         Four            f+b+c+g
#define         Five            a+f+g+c+d
#define         Six             a+f+e+g+c+d
#define         Seven           a+b+c
#define         Eight           a+b+c+d+e+f+g
#define         Nine            a+b+c+f+g+d
#define         Zero            a+b+c+d+e+f

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
void show(unsigned char x);
void show_qian(unsigned char qian);
void show_bai(unsigned char bai);
void show_shi(unsigned char shi);
void show_ge(unsigned char ge);
void Digital_show(uint16_t x);
void num_test(void);
#endif

