//	头文件包含
#ifndef _DELAY_H
#define _DELAY_H
#include "system.h"

//-----------------------------------------------------------------

//  函数声明
extern void SysTick_clkconfig(u16 SYSCLK);
extern void delay_us(u32 nus);
extern void delay_ms(u16 nms);
#endif

// End Of File
