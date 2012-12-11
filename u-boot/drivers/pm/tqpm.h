/*************************************************
* 文件名:pm.h
* 功能:
* 日期:
*
*
*************************************************/
#ifndef __CW210_PM_H__
#define __CW210_PM_H__
#include "LPC901.h"

#define TRUE 1
#define FALSE 0

void delayms(unsigned int tim);
char IIC_set_reg(uchar addr, uchar dat);

#endif
