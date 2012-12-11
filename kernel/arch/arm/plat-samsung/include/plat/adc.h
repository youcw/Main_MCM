/* arch/arm/plat-samsung/include/plat/adc.h
 *
 * Copyright (c) 2008 Simtec Electronics
 *	http://armlinux.simnte.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C ADC driver information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_PLAT_ADC_H
#define __ASM_PLAT_ADC_H __FILE__

struct s3c_adc_client;

enum s3c_cpu_type {
	TYPE_S3C24XX,
	TYPE_S3C64XX,
	TYPE_S5PV210
};

struct s3c_adc_mach_info {
	/* if you need to use some platform data, add in here*/
	int delay;
	int presc;
	int resolution;
};
struct s3c_adc_client {
	struct platform_device	*pdev;//生成adc client的平台设备
	struct list_head	 pend;//用于管理ADC驱动中的多个client
	wait_queue_head_t	*wait;//多个client时的队列等待

	unsigned int		 nr_samples;//采样次数
	int			 result;//转换完成的结果
	int 			data_bit; //用于转换的数据位设置
	unsigned char		 is_ts;//指定client是否触摸设备
	unsigned char		 channel;//client所利用的通道
	//通道选择的回调函数
	void	(*select_cb)(struct s3c_adc_client *c, unsigned selected);
	//转换结束的回调函数
	void	(*convert_cb)(struct s3c_adc_client *c,
			      unsigned val1, unsigned val2,
			      unsigned *samples_left);
};

struct s3c_adc_request {
	/* for linked list */
	struct list_head *list;
	/* after finish ADC sampling, s3c_adc_request function call this function with three parameter */
	void (*callback)(int channel, unsigned long int param, unsigned short sample);
	/* for private data */
	unsigned long int param;
	/* selected channel for ADC sampling */
	int channel;
};

extern int s3c_adc_start(struct s3c_adc_client *client,
			 unsigned int channel, unsigned int nr_samples);

extern int s3c_adc_read(struct s3c_adc_client *client, unsigned int ch);

extern struct s3c_adc_client *
	s3c_adc_register(struct platform_device *pdev,
			 void (*select)(struct s3c_adc_client *client,
					unsigned selected),
			 void (*conv)(struct s3c_adc_client *client,
				      unsigned d0, unsigned d1,
				      unsigned *samples_left),
			 unsigned int is_ts);

extern void s3c_adc_release(struct s3c_adc_client *client);

#endif /* __ASM_PLAT_ADC_H */
