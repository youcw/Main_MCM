/*************************************************
* 文件名:IIC.c
* 功能:	模拟IIC协议
* 日期:
*
*
*************************************************/
#include <common.h>
#ifdef CONFIG_CW210_IIC_PM_CHIP
#include "LPC901.h"

//延时5us
void IIC_delay(void)
{
	udelay(5);
}
//初始化
void IIC_init(void)
{

	SCL_HIGH();

	IIC_delay();

	SDA_HIGH();

	IIC_delay();

}

/*******************************************************************************
 * 函数名：IIC_start_signal
 * 功能：IIC起始信号函数
 * 形参1：无
 * 返回值：无
*******************************************************************************/
void IIC_start_signal(void)
{
	SDA_HIGH();

	IIC_delay();

	SCL_HIGH();

	IIC_delay();

	SDA_LOW();

	IIC_delay();		
}

/*******************************************************************************
 * 函数名：IIC_stop_signal
 * 功能：IIC终止信号函数
 * 形参1：无
 * 返回值：无
*******************************************************************************/
void IIC_stop_signal(void)
{
	SDA_LOW();	   //数据线拉高

	IIC_delay();
		
	SCL_HIGH();		   //时钟线拉高

	IIC_delay();

	SDA_HIGH();		   //数据线拉低

	IIC_delay();	
}

/*******************************************************************************
 * 函数名：IIC_ask_signal
 * 功能：IIC应答函数
 * 形参1：无
 * 返回值：无
*******************************************************************************/
void IIC_ask_signal(void)
{
	int count = 0;

	SCL_HIGH();

	IIC_delay();
	
	while ((get_sda_state() == 1) && (count < 300))
	{
		count++;
	}		  

	SCL_LOW();

	IIC_delay();	
}

/*******************************************************************************
 * 函数名：IIC_read_byte
 * 功能：IIC读字节函数
 * 形参1：无
 * 返回值：读出的字节
*******************************************************************************/
uchar IIC_read_byte(void)
{
	uchar ret=0;
	uchar i;

	SCL_LOW();			  //时钟线拉低，IIC等待

	IIC_delay();

	SDA_HIGH();		//释放数据总线

	IIC_delay();

	for (i = 0; i < 8; i++)
	{
		SCL_HIGH();
		IIC_delay();

		ret = ((ret<<1) | get_sda_state());
		
		SCL_LOW();
		IIC_delay();	
	}

	return (ret);
}

/*******************************************************************************
 * 函数名：IIC_write_byte
 * 功能：IIC写字节函数
 * 形参1：写入的字节
 * 返回值：无
*******************************************************************************/
void IIC_write_byte(uchar byte)
{
	uchar temp = byte;
	uchar i;

	SCL_LOW();

	for (i = 0; i < 8; i++)
	{

		SCL_LOW();			 //时钟线拉低时，才能改变数据线的状态
		
		IIC_delay();

		set_sda_state((temp & 0x80));
		temp = temp<<1;

		IIC_delay();

		SCL_HIGH();			  //时钟线拉高时，对数据进行读写

		IIC_delay();
		
	}

	SCL_LOW();			  //时钟线拉低，IIC等待

	IIC_delay();

	SDA_HIGH();		//释放数据总线

	IIC_delay();
}	 

/*******************************************************************************
 * 函数名：IIC_write_data
 * 功能：IIC写数据函数
 * 形参1：存储器地址
 * 形参2：待写入数据
 * 返回值：无
*******************************************************************************/

void IIC_write_data(uchar addr, uchar dat)
{
	IIC_start_signal();		//起始信号

	IIC_write_byte(0x5a);	   //写入器件地址



	IIC_ask_signal();			 //等待从设备应答



	IIC_write_byte(addr);		//写入寄存器地址

	IIC_ask_signal();


	IIC_write_byte(dat);	  //写入数据

	IIC_ask_signal();


	IIC_stop_signal();		 //停止信号
}					 
							
/*******************************************************************************
 * 函数名：IIC_read_data
 * 功能：IIC读数据函数
 * 形参：存储器地址
 * 返回值：读出的数据
*******************************************************************************/

uchar IIC_read_data(uchar addr)
{
	uchar ret=0;
	
	IIC_start_signal();	   //起始信号

	IIC_write_byte(0x5a);  //写入器件地址

	IIC_ask_signal();	   //等待从器件应答

	IIC_write_byte(addr);	 //写入eeprom存储器地址

	IIC_ask_signal();		  //等待从器件应答

	IIC_start_signal();		 //起始信号

	IIC_write_byte(0x5b);	  //写入器件地址

	IIC_ask_signal();		  //等待从器件应答

	ret = IIC_read_byte();	  //读eeprom存储器的内容

	IIC_stop_signal();		 //终止信号

	return ret;
}
#endif
