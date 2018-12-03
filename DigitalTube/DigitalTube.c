#include "DigitalTube.h"
void Digital_TubeInit()
{
  SET_GPIO_OUT(COM1);
  SET_GPIO_OUT(COM2);
  SET_GPIO_OUT(COM3);
  SET_GPIO_OUT(COM4);
  
  SET_GPIO_OUT(COMA);
  SET_GPIO_OUT(COMB);
  SET_GPIO_OUT(COMC);
  SET_GPIO_OUT(COMD);
  SET_GPIO_OUT(COME);
  SET_GPIO_OUT(COMF);
  SET_GPIO_OUT(COMG);
  SET_GPIO_OUT(COMPint);
}
void Digital_show(unsigned char num)
{
  ;
}









