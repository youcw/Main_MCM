/*************************************************
* 文件名: option.c
* 功能:
* 日期:
*
*
*************************************************/
#include <common.h>
#ifdef CONFIG_CW210_IIC_PM_CHIP
#include "cwpm.h"



/*******************************************************************************
 * 函数名：delayms
 * 功能：毫秒延时函数
 * 形参：延时时间
 * 返回值：无
*******************************************************************************/
void delayms(unsigned int tim)
{
	unsigned int x;
	for (x = 0; x < tim; x++)
	{
		udelay(1000);
	}
}

/*******************************************************************************
 * 函数名：IIC_set_reg
 * 功能：设置寄存器
 * 形参1：寄存器地址
 * 形参2: 写入数据
 * 返回值：0失败；1成功
*******************************************************************************/

char IIC_set_reg(uchar addr, uchar dat)
{
	char ret = 1;
	uchar val =0 ;
	int i;

	for (i = 0; i < 500; i++)
	{

		IIC_init();
	
		IIC_write_data(addr, dat);

		delayms(10);//延时10ms左右

		val = IIC_read_data(addr);

		if (val == dat)
			break;

	}

	if (i >= 500)
	{
		return FALSE;
	}

	return TRUE;
}
#endif
