#include "a7106.h"
#include "a7106reg.h"
#include "a7106gpio.h"


#define     speed       1//26us

void test_rf()
{
    SET_GPIO_OUT(LED);
    while(1)
    {
        //GPIO_ToggleBits(LED,LED_Pin);
        SET_GPIO_H(LED);
        SET_GPIO_L(LED);
    }
}
/*********************************************************************
** initRF
*********************************************************************/
void initRF(void)
{
    A7106_GPIO_init();
    
    //A7106_WriteReg(1,0x62);

    A7106_Reset();  //reset A7106 RF chip
    A7106_WriteID();//write ID code
    A7106_WriteReg(CPC_REG, 0x77);    // RGC=3
    A7106_Config(); //config A7106 chip
    A7106_WriteReg(CPC_REG, 0x57);    // RGC=1
    A7106_Cal();    //calibration IF,vco, vcoc
    A7106_RCO_Cal(); // calibration RC Osc (OPTION)
    //test_rf();
}

/************************************************************************
**  Reset_RF
************************************************************************/
void A7106_Reset(void)
{
    A7106_WriteReg(MODE_REG, 0x00); //reset RF chip
}
    Uint8 d1,d2,d3,d4;
/************************************************************************
**  WriteID
************************************************************************/
void A7106_WriteID(void)
{
    Uint8 i;


    SET_GPIO_L(CSCPROT);
    ByteSend(IDCODE_REG);
    for (i=0; i < 4; i++)
        ByteSend(ID_Tab[i]);
    SET_GPIO_H(CSCPROT);

    //for check
    SET_GPIO_L(CSCPROT);
    ByteSend(IDCODE_REG | 0x40);
    d1=ByteRead();
    d2=ByteRead();
    d3=ByteRead();
    d4=ByteRead();
    SET_GPIO_H(CSCPROT);

}

/************************************************************************
**  A7106_WriteReg
************************************************************************/
void A7106_WriteReg(Uint8 addr, Uint8 dataByte)
{
    Uint8 i;
    SET_GPIO_OUT(SDIOPROT);
    SET_GPIO_L(CSCPROT);
    for(i=0;i<8;i++)
    {
        SET_GPIO_H(SCKPROT);
        if(addr & 0x80)
            SET_GPIO_H(SDIOPROT);
        else
            SET_GPIO_L(SDIOPROT);
   

        SET_GPIO_L(SCKPROT);
        addr = addr << 1;
    }
    //send data byte
    for(i = 0; i < 8; i++)
    {
        SET_GPIO_H(SCKPROT);
        if(dataByte & 0x80)
            SET_GPIO_H(SDIOPROT);
        else
            SET_GPIO_L(SDIOPROT);


        SET_GPIO_L(SCKPROT);
        dataByte = dataByte<< 1;
    }
    SET_GPIO_H(CSCPROT);    
}

/************************************************************************
**  A7106_ReadReg
************************************************************************/
Uint8 A7106_ReadReg(Uint8 addr)
{
    Uint8 i;
    Uint8 tmp;
    SET_GPIO_OUT(SDIOPROT);
    SET_GPIO_L(CSCPROT);
    addr |= 0x40; //bit cmd=0,r/w=1
    for(i = 0; i < 8; i++)
    {
        SET_GPIO_H(SCKPROT);
        if(addr & 0x80)
            SET_GPIO_H(SDIOPROT);
        else
            SET_GPIO_L(SDIOPROT);

        SET_GPIO_L(SCKPROT);
        addr = addr << 1;
    }

    SET_GPIO_H(SDIOPROT);
    SET_GPIO_IN(SDIOPROT);
    
    //read data
    for(i = 0; i < 8; i++)
    {
        SET_GPIO_H(SCKPROT);
        //if(Read_GPIO(SDIOPROT))
        if(GPIO_ReadInputDataBit(SDIOPROT,SDIOPROT_Pin))
            tmp = (tmp << 1) | 0x01;
        else
            tmp = tmp << 1;

        
        SET_GPIO_L(SCKPROT);
    }
    SET_GPIO_H(CSCPROT);
    return tmp;
}

/************************************************************************
**  ByteSend
************************************************************************/
void ByteSend(Uint8 src)
{
    Uint8 i;

    for(i = 0; i < 8; i++)
    {
        SET_GPIO_H(SCKPROT);
        if(src & 0x80)
            SET_GPIO_H(SDIOPROT);
        else
            SET_GPIO_L(SDIOPROT);

       
        SET_GPIO_L(SCKPROT);
        src = src << 1;
    }
}
/************************************************************************
**  ByteRead
************************************************************************/
Uint8 ByteRead(void)
{
    Uint8 i,tmp;

    SET_GPIO_H(SDIOPROT);
    SET_GPIO_IN(SDIOPROT);

    for(i = 0; i < 8; i++)
    {
        SET_GPIO_H(SCKPROT);
        //if(Read_GPIO(SDIOPROT))
        if(GPIO_ReadInputDataBit(SDIOPROT,SDIOPROT_Pin))
            tmp = (tmp << 1) | 0x01;
        else
            tmp = tmp << 1;
        
        SET_GPIO_L(SCKPROT);
    }
    return tmp;
}
/*********************************************************************
** SetCH
*********************************************************************/
void SetCH(Uint8 ch)
{
    A7106_WriteReg(PLL1_REG, ch);
}
/*********************************************************************
** A7106_WriteFIFO
*********************************************************************/
void A7106_WriteFIFO(void)
{
    Uint8 i;

    SET_GPIO_L(CSCPROT);
    ByteSend(FIFO_REG);
    for(i=0; i <64; i++)
        ByteSend(PN9_Tab[i]);
    SET_GPIO_H(CSCPROT);
}
/*********************************************************************
** Strobe Command
*********************************************************************/
void StrobeCmd(Uint8 cmd)
{
    SET_GPIO_L(CSCPROT);
    ByteSend(cmd);
    SET_GPIO_H(CSCPROT);
}

/*********************************************************************
** RxPacket
*********************************************************************/
void RxPacket(void)
{
    Uint8 i;
    Uint8 recv;
    Uint8 tmp;

    RxCnt++;

    SET_GPIO_L(CSCPROT);
    ByteSend(FIFO_REG | 0x40);
    for(i=0; i <64; i++)
    {
        recv = ByteRead();
        tmpbuf[i]=recv;
        if((recv ^ PN9_Tab[i])!=0)
        {
            tmp = recv ^ PN9_Tab[i];
            Err_BitCnt += (BitCount_Tab[tmp>>4] + BitCount_Tab[tmp & 0x0F]);
        }
    }
    SET_GPIO_H(CSCPROT);
}
/*********************************************************************
** Err_State
*********************************************************************/
void Err_State(void)
{
    //ERR display
    //Error Proc...
    //...
    //while(1)
    {
        ;
    }
}
/*********************************************************************
** calibration
*********************************************************************/
void A7106_Cal(void)
{
    Uint8 tmp=0;
    Uint8 fb, vcb, vb, rh, rl;

    //==================================================
    // calibration IF, VB, VCB, RSSI
    StrobeCmd( CMD_STBY );
    A7106_WriteReg( CALIBRATION_REG, 0x0F );
    do
    {
        tmp = A7106_ReadReg( CALIBRATION_REG );
    } while ( tmp & 0x0F );

    tmp = A7106_ReadReg( IFCAL1_REG );
    if ( tmp & 0x10 )
        Err_State();
    fb = tmp & 0x0F;

    tmp = A7106_ReadReg( VCOCCAL_REG );
    if ( tmp & 0x10 )
        Err_State();
    vcb = tmp & 0x0F;

    tmp = A7106_ReadReg( VCOCAL1_REG );
    if ( tmp & 0x08 )
        Err_State();
    vb = tmp& 0x07;

    rh = A7106_ReadReg( RXGAIN2_REG );
    rl = A7106_ReadReg( RXGAIN3_REG );
}
/*********************************************************************
** A7106_RCO_Cal
*********************************************************************/
void A7106_RCO_Cal(void)
{
    Uint8 tmp, rcoc, rcot, retry, i;

    for ( rcot = 0; rcot <= 3; rcot++ )
    {
        for ( retry = 0; retry < 10; retry++ )
        {
            A7106_WriteReg( RCOSC3_REG, 0x00 );   // RCO oscillator disable
            A7106_WriteReg( RCOSC3_REG, (0x0C | (rcot<<4)) );   // RCOSC_E=1, CALW=1
            do
            {
                tmp = A7106_ReadReg( RCOSC1_REG ) & 0x80;
            } while( tmp );
            rcoc = A7106_ReadReg( RCOSC1_REG ) & 0x7F;
            if ( rcoc >= 20 )
            {
                return;
            }

            A7106_WriteReg( RCOSC3_REG, 0x00 );     // RCO oscillator disable
            A7106_WriteReg( RCOSC3_REG, (0x04 | (rcot<<4)) );   // RCOSC_E=1
            for ( i = 0; i<10*(retry+1); i++ )
            {
                A7106_WriteReg( CPC_REG, A7106Config[CPC_REG] | 0x80 );     // ROSCS=1
                A7106_WriteReg( CPC_REG, A7106Config[CPC_REG] & 0x7F );     // ROSCS=0
            }
            A7106_WriteReg( RCOSC3_REG, (0x0C | (rcot<<4)) );   // RCOSC_E=1, CALW=1

            do
            {
                tmp = A7106_ReadReg( RCOSC1_REG ) & 0x80;
            }
            while( tmp );
            rcoc = A7106_ReadReg( RCOSC1_REG ) & 0x7F;
            if ( rcoc >= 20 )
            {
                return;
            }
        }
    }

    Err_State(); // RCOC always too small
}

/*********************************************************************
** A7106_Config
*********************************************************************/
void A7106_Config(void)
{
    Uint8 i;

    //0x00 mode register, for reset
    //0x02 calibration register
    //0x05 fifo data register
    //0x06 id code register
    //0x23 IF calibration II, only read
    //0x32 filter test register

    for ( i=1; i<=0x33; i++ )
    {
        if ( (i==0x02) || (i==0x05) || (i==0x06) || (i==0x23) || (i==0x32) )
            continue;

        A7106_WriteReg( i, A7106Config[i] );
    }
}





