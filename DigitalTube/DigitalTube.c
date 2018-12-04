#include "DigitalTube.h"
#include "time.h"


      
#define CPL_BIT(value,bit)      (value^=(1<<bit))   //取反指定位
#define SET_BIT(value,bit)      (value|=(1<<bit))   //置位指定位
#define CLR_BIT(value,bit)      (value&=~(1<<bit))  //清零指定位
#define GET_BIT(value,bit)      (value&(1<<bit))    //读取指定位


char num;
unsigned char  Seg_mod[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void Digital_TubeInit()
{
  SET_GPIO_OUT(COM1);
  SET_GPIO_OUT2(COM2);
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
 
  SET_GPIO_L(COM1);
  SET_GPIO_L(COM2);
  SET_GPIO_L(COM3);
  SET_GPIO_L(COM4);
 
  SET_GPIO_H(COMA);
  SET_GPIO_H(COMB);
  SET_GPIO_H(COMC);
  SET_GPIO_H(COMD);
  SET_GPIO_H(COME);
  SET_GPIO_H(COMF);
  SET_GPIO_H(COMG);
  SET_GPIO_H(COMPint);
}
void test_delay(uint16_t num)
{
  uint16_t t;
  t = num;
  while(t--);
}
unsigned char temp[4]={0};
void num_test()
{
    num = 0;
    char flagg=1,i;
  while(1)
  {
    if(Time2.flag == TRUE)
    {
      Time2.flag = FALSE;
     
    temp[0] = num++;
    temp[1] = num++;
    temp[2] = num++;
    temp[3] = num++;
    for(i=0;i<50;i++)
    {
      show_qian(temp[0] % 10);
      test_delay(1000);
      show_bai(temp[1] % 10);
      test_delay(1000);
      show_shi(temp[2] % 10);
      test_delay(1000);
      show_ge(temp[3] % 10);
      test_delay(1000);
    }
    
     //Digital_show(num++);
    }
  }
}
void Digital_show(uint16_t x)
{
  unsigned char s[4];
  s[0]=x/1000;//四位数的 千位
  s[1]=x/100%10;//四位数的 百位
  s[2]=x/10%10;//四位数的 十位
  s[3]=x%10;//四位数的 个位
  
  show_qian(s[0]);
  show_bai(s[1]);
  show_shi(s[2]);
  show_ge(s[3]);

}

void show_qian(unsigned char qian)
{
    SET_GPIO_H(COM1);
    SET_GPIO_H(COM2);
    SET_GPIO_H(COM3);  
    SET_GPIO_H(COM4);
    show(qian);
    test_delay(20);
    SET_GPIO_L(COM1);
}

void show_bai(unsigned char bai)
{
    SET_GPIO_H(COM1);
    SET_GPIO_H(COM2);
    SET_GPIO_H(COM3);  
    SET_GPIO_H(COM4);
    show(bai);
    test_delay(20);
    SET_GPIO_L(COM2);

}
void show_shi(unsigned char shi)
{
    SET_GPIO_H(COM1);
    SET_GPIO_H(COM2);
    SET_GPIO_H(COM4);
    SET_GPIO_H(COM3);  
    show(shi);
    test_delay(20);
    SET_GPIO_L(COM3);
}
void show_ge(unsigned char ge)
{
    SET_GPIO_H(COM1);
    SET_GPIO_H(COM2);
    SET_GPIO_H(COM3);  
    SET_GPIO_H(COM4);   
    show(ge);
    test_delay(20);
    SET_GPIO_L(COM4);   
    test_delay(1000);
    SET_GPIO_H(COM4);

}
void show(unsigned char x)
{
  /*
  SET_GPIO_H(COMA);
  SET_GPIO_H(COMB);
  SET_GPIO_H(COMC);
  SET_GPIO_H(COMD);
  SET_GPIO_H(COME);
  SET_GPIO_H(COMF);
  SET_GPIO_H(COMG);
  SET_GPIO_H(COMPint);
  */
  (Seg_mod[x]&0x01)==0x01?SET_GPIO_L(COMA):SET_GPIO_H(COMA);
  (Seg_mod[x]&0x02)==0x02?SET_GPIO_L(COMB):SET_GPIO_H(COMB);
  (Seg_mod[x]&0x04)==0x04?SET_GPIO_L(COMC):SET_GPIO_H(COMC);
  (Seg_mod[x]&0x08)==0x08?SET_GPIO_L(COMD):SET_GPIO_H(COMD);
  (Seg_mod[x]&0x10)==0x10?SET_GPIO_L(COME):SET_GPIO_H(COME);
  (Seg_mod[x]&0x20)==0x20?SET_GPIO_L(COMF):SET_GPIO_H(COMF);
  (Seg_mod[x]&0x40)==0x40?SET_GPIO_L(COMG):SET_GPIO_H(COMG);
  
  (Seg_mod[x]&0x80)==0x80?SET_GPIO_L(COMPint):SET_GPIO_H(COMPint);
}


