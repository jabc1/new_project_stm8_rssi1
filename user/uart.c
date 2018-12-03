#include "uart.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x.h"  
#include "queue_jk.h"

/*!
 * @file uart.c
 * @brief 主要实现muc外设串口相关功能
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

Fifo_t      Uart_Rx;
Fifo_t      Uart_Tx;
uint8_t     Uart_Rx_buff[Uart_Rx_len],Uart_Tx_buff[Uart_Tx_len];

UART1   Uart1;
void Init_uart()
{
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);//RXD
    USART_DeInit(USART1);       //复位UART1

    USART_Init(USART1,9600, USART_WordLength_8b, USART_StopBits_1, \
               USART_Parity_No, USART_Mode_Tx|USART_Mode_Rx);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启接收中断
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
    //USART_ITConfig(USART1, USART_IT_PE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_ERR, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    USART_Cmd(USART1, ENABLE);
    memset(Uart1.buff,0,sizeof(Uart1.buff));
    Uart1.flag = FALSE;
    Uart1.len = 0;    
}

/*******************************************************************************
* 名称: UART1_SendByte
* 功能: UART1发送一个字节
* 形参: data -> 要发送的字节
* 返回: 无
* 说明: 无
******************************************************************************/
void UART1_SendByte(u8 data)
{
    USART_SendData8(USART1, data);
    /* 等待传输结束 */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/*******************************************************************************
* 名称: UART1_SendStr
* 功能: UART1发送len个字符
* 形参: data -> 指向要发送的字符串
*       len -> 要发送的字节数
* 返回: 无
* 说明: 无
******************************************************************************/
void UART1_SendStr(u8 *str)
{
    while(*str != '\0')
    {
        UART1_SendByte(*str++); /* 循环调用发送一个字符函数 */
    }   
}

void uart_test()
{

    if((Uart1.time-- == 0)&&(Uart1.flag == TRUE))
    {
        //Msg_deal(Uart1.buff,Uart1.len);
        //UART1_SendStr(Uart1.buff);
        vfunction(Uart1.buff);
        memset(Uart1.buff,0,sizeof(Uart1.buff));
        Uart1.flag = FALSE;
        Uart1.len = 0;
    }
}
void uart_fifo()
{
    uint16_t t;
    u8 temp;
    
    if(Queue_Get(&Uart_Rx12,&temp))
    {
        if(temp == 'a')
        {
            Uart1.len = 0;
            while(Queue_Get(&Uart_Rx12,&Uart1.buff[Uart1.len++]))
            {
                ;
            }
            Uart1.buff[Uart1.len] = 0;
            UART1_SendStr(Uart1.buff);
            memset(Uart1.buff,0,sizeof(Uart1.buff));
        }
    }
}

INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    unsigned char ch;
    if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//接收中断处理
    {
        USART_ClearITPendingBit (USART1,USART_IT_RXNE);//清中断标志      
        ch = USART_ReceiveData8(USART1);
        Uart1.time = 500;
        Uart1.flag = TRUE;
        Uart1.buff[Uart1.len ++] = ch;
        //Queue_Put(&Uart_Rx12,&ch);        
    }
    /*
    if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
    {
        USART_ClearITPendingBit (USART1,USART_IT_IDLE);
        Uart1.flag = TRUE;
        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    }
    */
}







