/*************************************************
* 文件名:IIC.h
* 功能:
* 日期:
*
*
*************************************************/
#ifndef __CW210_PM_IIC_H__
#define __CW210_PM_IIC_H__
#include <regs.h>
#define rGPH0CON	__REG(0xE0200C00)
#define rGPH0DAT	__REG(0xE0200C04)
#define rGPH0PUD	__REG(0xE0200C08)


#define rGPD1CON	__REG(0xE02000C0)
#define rGPD1DAT	__REG(0xE02000C4)
#define rGPD1PUD	__REG(0xE02000C8)


#define rGPJ2CON	__REG(0xE0200280)
#define rGPJ2DAT	__REG(0xE0200284)
#define rGPJ2PUD	__REG(0xE0200288)
#define uchar unsigned char
#define uint  unsigned int
//typedef unsigned int  uint 
//typedef unsigned char  uchar 
/*
sbit SDA = P3^1;
sbit SCL = P3^0;
sbit PWRHOLD = P1^2;
*/

//sbit SCLSR_EN1 = P0^5;
//sbit SDASR_EN2 = P0^4;


static inline uchar get_sda_state(void)
{
	rGPH0CON = (rGPD1CON & (~0xf<<0));//GPHD1_0
	if((rGPD1DAT & (0x1<<0)) != 0)//GPH0
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#define PWRHOLD_UP()	{rGPJ2CON = ((rGPJ2CON & (~0xf<<20)) | (0x1<<20)); rGPJ2DAT |= (0x1<<5);}	//GPJ2_5
#define PWRHOLD_DOWN()	{rGPJ2CON = ((rGPJ2CON & (~0xf<<20)) | (0x1<<20)); rGPJ2DAT &= ~(0x1<<5);}	//GPJ2_5
#define SDASR_EN2_UP	{rGPJ2CON = ((rGPJ2CON & (~0xf<<12)) | (0x1<<12));rGPJ2DAT |= (0x1<<3);}	//GPJ2_3
#define SDASR_EN2_DOWN	{rGPJ2CON = ((rGPJ2CON & (~0xf<<12)) | (0x1<<12));rGPJ2DAT &= ~(0x1<<3);}	//GPJ2_3
#define SCLSR_EN1_UP	{rGPJ2CON = ((rGPJ2CON & (~0xf<<16)) | (0x1<<16));rGPJ2DAT |= (0x1<<4);}	//GPJ2_4
#define SCLSR_EN1_DOWN	{rGPJ2CON = ((rGPJ2CON & (~0xf<<16)) | (0x1<<16));rGPJ2DAT &= ~(0x1<<4);}	//GPJ2_4

#define SDA_INP			rGPD1CON = (rGPD1CON & (~0xf<<0))					//GPD1_0	input
#define SDA_OUTP		rGPD1CON = ((rGPD1CON & (~0xf<<0)) | (0x1<<0))		//GPD1_0	output
#define SCL_INP			rGPD1CON = (rGPD1CON & (~0xf<<4))					//GPD1_1	input
#define SCL_OUTP		rGPD1CON = ((rGPD1CON & (~0xf<<4)) | (0x1<<4))		//GPD1_1	output

#define SDA_HIGH()		rGPD1DAT |= (0x1<<0)								//GPD1_0 1
#define SDA_LOW()		rGPD1DAT &= ~(0x1<<0)								//GPD1_0 0
#define SCL_HIGH()		rGPD1DAT |= (0x1<<1)								//GPD1_1 1
#define SCL_LOW()		rGPD1DAT &= ~(0x1<<1)								//GPD1_1 0


static inline void chip_init(void)
{

	//set rGPH0PUD ..............
//	PWRHOLD_UP();  //POWER ON
//	{rGPJ2CON = ((rGPJ2CON & (~0xf<<3)) | (0x1<<3));rGPJ2DAT |= (0x1<<3);}//GPJ2_3
//	{rGPJ2CON = ((rGPJ2CON & (~0xf<<4)) | (0x1<<4));rGPJ2DAT |= (0x1<<4);}//GPJ2_4
//	SCLSR_EN1 = 1;
//	SDASR_EN2 = 1;//使能加上
}



static inline void set_sda_state(uchar sta)
{
	if (sta != 0)
	{
		SDA_HIGH();
	}
	else
	{
		SDA_LOW();
	}
}


void IIC_init(void);
void IIC_write_data(uchar addr, uchar dat);
uchar IIC_read_data(uchar addr);

#endif
