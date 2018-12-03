使用内部16M晶振
20181010
新建stm8l demo工程
20181013
1、测试定时器中断正常
2、添加工程文件
3、添加串口驱动==测试成功
4、内部16M晶振误差太大，导致波特率不准，9600bps可以。要想使用115200，就用外部晶振吧。
5、串口中断收发正常
6、无串口中断超时处理流程，以后添加
7、添加RTC代码，测试ok
/****************
配置RTC时钟源

RTC时钟源可选HSE，LSE，HSI或LSI。 
为确保RTC精确工作，要求系统时钟（SYSCLK）必须等于或大于4*RTCCLK值。如果系统时钟（SYSCLK）为LSE或LSI，则RTC时钟必须等于系统时钟（SYSCLK），并且禁用RTC同步机制（置位RTC_CR1寄存器RATIO位）。

配置RTC时钟源为LSE，1分频，即32768Hz。 
1. 等待CLK_CRTCR:RTCSWBSY位复位，然后设置CLK_CRTCR值为0x10； 
2. 等待CLK_ECKCR:LSERDY位置位，标识LSE时钟源已稳定可用； 
3. 等待CLK_ECKCR:LSEON位置位，标识LSE时钟源已启用。

配置ck_spre时钟：ck_spre时钟可用于日历和定时唤醒时钟。

ck_spre时钟，即1Hz时钟。 
1. 设置7位异步预分频，RTC_APREG:PREDIVA，默认127； 
2. 设置13（Medium）或15位同步预分频，RTC_SPRERx:PREDIV_S，默认255。

fCK_SPRE=fRTCCLK(PREDIV_S+1)(PREDIV_A+1)fCK_SPRE=fRTCCLK(PREDIV_S+1)(PREDIV_A+1)

 
解除RTC寄存器保护

执行以下操作顺序： 
1. 写0xCA到寄存器RTC_WPR; 
2. 写0x53到寄存器RTC_WPR。

写其它值到RTC_WPR，则自动激活RTC寄存器保护功能。

****************/

添加fifo缓存机制
测试fifo ok
添加看门狗
添加低功耗halt模式通过RTC定时唤醒测试ok
添加文件注释
工程运行一段时间会重启，不知道什么原因


20181121
添加查表执行功能





