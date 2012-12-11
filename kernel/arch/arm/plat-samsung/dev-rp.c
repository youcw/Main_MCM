/* linux/arch/arm/plat-samsung/dev-rp.c
 *
 * Copyright 2009 by Maurus Cuelenaere <mcuelenaere@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * lhh add
 */

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/platform_device.h>

#include <mach/irqs.h>
#include <mach/map.h>

#include <plat/devs.h>

static struct resource s3c_rp_resource[] = {
};

struct platform_device s3c_device_rp = {
	.name		= "s5p-rp",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_rp_resource),
	.resource	= s3c_rp_resource,
};
EXPORT_SYMBOL(s3c_device_rp);
