#include "fifo.h"
/*!
 * @file fifo.c
 * @brief 实现缓存机制
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */
uint16_t FifoNext( Fifo_t *fifo, uint16_t index )
{
    return (index+1) == fifo->Size? 0 : (index + 1);
}
void FifoInit( Fifo_t *fifo, char *buffer, uint16_t size )
{
    fifo->Begin = 0;
    fifo->End = 0;
    fifo->Data = buffer;
    fifo->Size = size;
    fifo->len = 0;
}

void FifoPush( Fifo_t *fifo, char data )
{
    *(fifo->Data+fifo->End)=data;  
    fifo->End = FifoNext(fifo,fifo->End);
}
char FifoPop( Fifo_t *fifo )
{
    if(IsFifoEmpty(fifo))
        return 0x00;
    char data = *(fifo->Data+ fifo->Begin);
    fifo->Begin = FifoNext( fifo, fifo->Begin );
    return data;
}

void FifoFlush( Fifo_t *fifo )
{
    fifo->Begin = 0;
    fifo->End = 0;
}
bool IsFifoEmpty( Fifo_t *fifo )
{
    return ( fifo->Begin == fifo->End );
}
bool IsFifoFull( Fifo_t *fifo )
{
    return ( FifoNext( fifo, fifo->End ) == fifo->Begin );
}

void PushBuffer(Fifo_t *fifo, char *buffer, int len)
{
    int i;
    char *tmp = buffer;
    for(i=0; i<len; i++)
    {
        if(IsFifoFull(fifo) == true)
        {
            fifo->End = FifoNext( fifo, fifo->End );
        }
        FifoPush( fifo, *(tmp+i) );
    }
    //fifo->len++;
}

void PopBuffer(Fifo_t *fifo, char *buffer, int len)
{
    int i;
    char *tmp = buffer;
    for(i=0; i<len; i++)
    {
        *(tmp+i) = FifoPop(fifo);
    }
    //fifo->len--;
}







