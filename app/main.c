/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "uart.h"
#include "time.h"
#include "gpio.h"
#include "rtc.h"
#include "fifo.h"
#include "queue_jk.h"
#include "a7106.h"
#include "DigitalTube.h"
#include "LCD.h"
/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void delay()
{
  uint16_t t;
  for(t=0;t<30000;t++)
    ;
}



void main(void)
{
    /*
    CLK_SYSCLKSourceSwitchCmd(ENABLE); 
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI); 
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1); 
    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI) 
    {   } 
   */ 
    delay();
    
    Init_rtc();
    Init_time2();
    Init_gpio();
    Digital_TubeInit();
    LCD_init();
    Init_uart();
    //test_rf();
    //FifoInit(&Uart_Tx,Uart_Tx_buff,Uart_Tx_len);
    //FifoInit(&Uart_Rx,Uart_Rx_buff,Uart_Rx_len);
    //Queue_Init(&Uart_Rx12,Uart_Rx_buff,Uart_Rx_len,2);
    //IWDG_Init();
    //initRF();
    //Inti_lowpower();
    rim();//开启系统总中断
    //UART1_SendByte(0x61);
    //delay();
    //GPIO_Init(GPIOA,GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast);
    while (1)
    {
        //IWDG_ReloadCounter();
        uart_test();
        //tiem2_test();
        //halt();
    }
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


