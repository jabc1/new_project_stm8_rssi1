#ifndef _uart_h
#define _uart_h
#include "fifo.h"
#include "function.h"
#include "table.h"


#include "stm8l15x_usart.h"

#define     uart_len            255
#define     Uart_Rx_len         512
#define     Uart_Tx_len         512

#pragma pack(push, 1)
typedef  struct
{
    uint16_t len;
    uint16_t time;
    uint8_t flag;
    uint8_t buff[uart_len];
    uint8_t back_buff[uart_len];
}UART1;
#pragma pack(pop)

extern UART1       Uart1;
extern Fifo_t      Uart_Rx, Uart_Tx;
extern uint8_t     Uart_Rx_buff[],Uart_Tx_buff[];

void Init_uart(void);
void uart_test(void);
void uart_fifo(void);
void UART1_SendByte(u8 data);



#endif








