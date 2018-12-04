#include "a7106gpio.h"
void delay_ms(uint16_t num)
{
  int16_t i;
  for(i=num;i>0;i--)
    ;
}
void delay_us(uint16_t num)
{
  int16_t i;
  i = num;
  while(i--);
}
void A7106_GPIO_init()
{
    SET_GPIO_OUT(CSCPROT);
    SET_GPIO_OUT(SCKPROT);
    SET_GPIO_OUT(SDIOPROT);
    SET_GPIO_OUT(CKOPROT);
    SET_GPIO_OUT(GIO1PROT);
    SET_GPIO_OUT(GIO2PROT);
/*
    while(1)
    {
      SET_GPIO_H(GIO2PROT);
      delay_us(1);
      SET_GPIO_L(GIO2PROT);
      delay_us(1);
    }
    */
    
    
    SET_GPIO_H(CSCPROT);
    SET_GPIO_L(SCKPROT);
    SET_GPIO_H(SDIOPROT);
    SET_GPIO_H(CKOPROT);
    SET_GPIO_H(GIO1PROT);
    SET_GPIO_H(GIO2PROT);

}







