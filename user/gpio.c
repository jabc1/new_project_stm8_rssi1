#include "gpio.h"
/*!
 * @file gpio.c
 * @brief ³õÊ¼»¯¹Ü½Å×´Ì¬
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

void Init_gpio()
{
    GPIO_Init(GPIOA,GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);
    
}



