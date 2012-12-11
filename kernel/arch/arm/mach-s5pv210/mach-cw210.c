/* linux/arch/arm/mach-s5pv210/mach-cw210.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/gpio.h>
#include <linux/gpio_event.h>
#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/regulator/consumer.h>
#if defined(CONFIG_SMDKC110_REV03) || defined(CONFIG_SMDKV210_REV02)
#include <linux/mfd/max8998.h>
#else
#include <linux/mfd/max8698.h>
#endif
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/usb/ch9.h>
#include <linux/pwm_backlight.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_gpio.h>
#include <linux/clk.h>
#include <linux/usb/ch9.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/skbuff.h>
#include <linux/console.h>
#include <linux/gpio_keys.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/system.h>

#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-mem.h>
#include <mach/gpio.h>
#include <mach/gpio-smdkc110.h>
#include <mach/regs-gpio.h>
#include <mach/ts-s3c.h>
#include <mach/adc.h>
#include <mach/param.h>
#include <mach/system.h>

#ifdef CONFIG_S3C64XX_DEV_SPI
#include <plat/s3c64xx-spi.h>
#include <mach/spi-clocks.h>
#endif

#include <linux/usb/gadget.h>

#include <plat/media.h>
#include <mach/media.h>

#ifdef CONFIG_ANDROID_PMEM
#include <linux/android_pmem.h>
#include <plat/media.h>
#include <mach/media.h>
#endif

#ifdef CONFIG_S5PV210_POWER_DOMAIN
#include <mach/power-domain.h>
#endif

#ifdef CONFIG_VIDEO_S5K4BA
#include <media/s5k4ba_platform.h>
#undef	CAM_ITU_CH_A
#define	CAM_ITU_CH_B
#endif

#include <media/ov3640_platform.h>
#include <media/tvp5150.h>

#ifdef CONFIG_VIDEO_S5K4EA
#include <media/s5k4ea_platform.h>
#endif

#include <plat/regs-serial.h>
#include <plat/s5pv210.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <plat/fb.h>
#include <plat/mfc.h>
#include <plat/iic.h>
#include <plat/pm.h>

#include <plat/sdhci.h>
#include <plat/fimc.h>
#include <plat/csis.h>
#include <plat/jpeg.h>
#include <plat/clock.h>
#include <plat/regs-otg.h>
#include <../../../drivers/video/samsung/s3cfb.h>

/* Following are default values for UCON, ULCON and UFCON UART registers */
#define S5PV210_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#define S5PV210_ULCON_DEFAULT	S3C2410_LCON_CS8

#define S5PV210_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)
				 
#define CW210_LCD 1

static struct s3c2410_uartcfg smdkc110_uartcfgs[] __initdata = {
	{
		.hwport		= 0,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
	{
		.hwport		= 1,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
#ifndef CONFIG_FIQ_DEBUGGER
	{
		.hwport		= 2,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
#endif
	{
		.hwport		= 3,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
};

#define S5PV210_LCD_WIDTH 1024//800
#define S5PV210_LCD_HEIGHT 768//600

//#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0 (6144 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0 (24576 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC1 (9900 * SZ_1K)
//#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2 (6144 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2 (24576 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC0 (36864 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC1 (36864 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMD (S5PV210_LCD_WIDTH * \
					     S5PV210_LCD_HEIGHT * 4 * \
					     CONFIG_FB_S3C_NR_BUFFERS)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG (8192 * SZ_1K)

/* 1920 * 1080 * 4 (RGBA)
 * - framesize == 1080p : 1920 * 1080 * 2(16bpp) * 2(double buffer) = 8MB
 * - framesize <  1080p : 1080 *  720 * 4(32bpp) * 2(double buffer) = under 8MB
 **/
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_G2D (8192 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_TEXSTREAM (3000 * SZ_1K)
#define  S5PV210_ANDROID_PMEM_MEMSIZE_PMEM_GPU1 (3300 * SZ_1K)

static struct s5p_media_device smdkc110_media_devs[] = {
	[0] = {
		.id = S5P_MDEV_MFC,
		.name = "mfc",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC0,
		.paddr = 0,
	},
	[1] = {
		.id = S5P_MDEV_MFC,
		.name = "mfc",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC1,
		.paddr = 0,
	},
	[2] = {
		.id = S5P_MDEV_FIMC0,
		.name = "fimc0",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0,
		.paddr = 0,
	},
	[3] = {
		.id = S5P_MDEV_FIMC1,
		.name = "fimc1",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC1,
		.paddr = 0,
	},
	[4] = {
		.id = S5P_MDEV_FIMC2,
		.name = "fimc2",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2,
		.paddr = 0,
	},
	[5] = {
		.id = S5P_MDEV_JPEG,
		.name = "jpeg",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG,
		.paddr = 0,
	},
	[6] = {
		.id = S5P_MDEV_FIMD,
		.name = "fimd",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMD,
		.paddr = 0,
	},
	[7] = {
		.id = S5P_MDEV_TEXSTREAM,
		.name = "texstream",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_TEXSTREAM,
		.paddr = 0,
	},
	[8] = {
		.id = S5P_MDEV_PMEM_GPU1,
		.name = "pmem_gpu1",
		.bank = 0, /* OneDRAM */
		.memsize = S5PV210_ANDROID_PMEM_MEMSIZE_PMEM_GPU1,
		.paddr = 0,
	},
	[9] = {
		.id = S5P_MDEV_G2D,
		.name = "g2d",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_G2D,
		.paddr = 0,
	},
};

static struct regulator_consumer_supply ldo3_consumer[] = {
	REGULATOR_SUPPLY("pd_io", "s3c-usbgadget")
};

static struct regulator_consumer_supply ldo4_consumer[] = {
	{   .supply = "vddmipi", },
};

static struct regulator_consumer_supply ldo6_consumer[] = {
	{   .supply = "vddlcd", },
};

static struct regulator_consumer_supply ldo7_consumer[] = {
	{   .supply = "vddmodem", },
};

static struct regulator_consumer_supply ldo8_consumer[] = {
	REGULATOR_SUPPLY("pd_core", "s3c-usbgadget")
};

static struct regulator_consumer_supply buck1_consumer[] = {
	{   .supply = "vddarm", },
};

static struct regulator_consumer_supply buck2_consumer[] = {
	{   .supply = "vddint", },
};

static struct regulator_init_data smdkc110_ldo2_data = {
	.constraints	= {
		.name		= "VALIVE_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data smdkc110_ldo3_data = {
	.constraints	= {
		.name		= "VUOTG_D_1.1V/VUHOST_D_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo3_consumer),
	.consumer_supplies	= ldo3_consumer,
};

static struct regulator_init_data smdkc110_ldo4_data = {
	.constraints	= {
		.name		= "V_MIPI_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.always_on	= 1,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo4_consumer),
	.consumer_supplies	= ldo4_consumer,
};

static struct regulator_init_data smdkc110_ldo5_data = {
	.constraints	= {
		.name		= "VMMC_2.8V/VEXT_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data smdkc110_ldo6_data = {
	.constraints	= {
		.name		= "VCC_2.6V",
		.min_uV		= 2600000,
		.max_uV		= 2600000,
		.apply_uV	= 1,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
		.state_mem	 = {
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo6_consumer),
	.consumer_supplies	= ldo6_consumer,
};

static struct regulator_init_data smdkc110_ldo7_data = {
	.constraints	= {
		.name		= "VDAC_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.enabled = 1,
		},
	},
	.num_consumer_supplies  = ARRAY_SIZE(ldo7_consumer),
	.consumer_supplies  = ldo7_consumer,
};

static struct regulator_init_data smdkc110_ldo8_data = {
	.constraints	= {
		.name		= "VUOTG_A_3.3V/VUHOST_A_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.enabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo8_consumer),
	.consumer_supplies	= ldo8_consumer,
};

static struct regulator_init_data smdkc110_ldo9_data = {
	.constraints	= {
		.name		= "{VADC/VSYS/VKEY}_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data smdkc110_buck1_data = {
	.constraints	= {
		.name		= "VCC_ARM",
		.min_uV		= 750000,
		.max_uV		= 1500000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
				  REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.uV	= 1250000,
			.mode	= REGULATOR_MODE_NORMAL,
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(buck1_consumer),
	.consumer_supplies	= buck1_consumer,
};

static struct regulator_init_data smdkc110_buck2_data = {
	.constraints	= {
		.name		= "VCC_INTERNAL",
		.min_uV		= 950000,
		.max_uV		= 1200000,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
				  REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.uV	= 1100000,
			.mode	= REGULATOR_MODE_NORMAL,
			.disabled = 1,
		},
	},
	.num_consumer_supplies  = ARRAY_SIZE(buck2_consumer),
	.consumer_supplies  = buck2_consumer,
};

static struct regulator_init_data smdkc110_buck3_data = {
	.constraints	= {
		.name		= "VCC_MEM",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.always_on	= 1,
		.apply_uV	= 1,
		.state_mem	= {
			.uV	= 1800000,
			.mode	= REGULATOR_MODE_NORMAL,
			.enabled = 1,
		},
	},
};

#if defined(CONFIG_SMDKC110_REV03) || defined(CONFIG_SMDKV210_REV02)
static struct max8998_regulator_data smdkc110_regulators[] = {
	{ MAX8998_LDO2,  &smdkc110_ldo2_data },
	{ MAX8998_LDO3,  &smdkc110_ldo3_data },
	{ MAX8998_LDO4,  &smdkc110_ldo4_data },
	{ MAX8998_LDO5,  &smdkc110_ldo5_data },
	{ MAX8998_LDO6,  &smdkc110_ldo6_data },
	{ MAX8998_LDO7,  &smdkc110_ldo7_data },
	{ MAX8998_LDO8,  &smdkc110_ldo8_data },
	{ MAX8998_LDO9,  &smdkc110_ldo9_data },
	{ MAX8998_BUCK1, &smdkc110_buck1_data },
	{ MAX8998_BUCK2, &smdkc110_buck2_data },
	{ MAX8998_BUCK3, &smdkc110_buck3_data },
};

static struct max8998_platform_data max8998_pdata = {
	.num_regulators	= ARRAY_SIZE(smdkc110_regulators),
	.regulators	= smdkc110_regulators,
	.charger	= NULL,
};
#else
static struct max8698_regulator_data smdkc110_regulators[] = {
	{ MAX8698_LDO2,  &smdkc110_ldo2_data },
	{ MAX8698_LDO3,  &smdkc110_ldo3_data },
	{ MAX8698_LDO4,  &smdkc110_ldo4_data },
	{ MAX8698_LDO5,  &smdkc110_ldo5_data },
	{ MAX8698_LDO6,  &smdkc110_ldo6_data },
	{ MAX8698_LDO7,  &smdkc110_ldo7_data },
	{ MAX8698_LDO8,  &smdkc110_ldo8_data },
	{ MAX8698_LDO9,  &smdkc110_ldo9_data },
	{ MAX8698_BUCK1, &smdkc110_buck1_data },
	{ MAX8698_BUCK2, &smdkc110_buck2_data },
	{ MAX8698_BUCK3, &smdkc110_buck3_data },
};

static struct max8698_platform_data max8698_pdata = {
	.num_regulators = ARRAY_SIZE(smdkc110_regulators),
	.regulators     = smdkc110_regulators,

	/* 1GHz default voltage */
	.dvsarm1        = 0xa,  /* 1.25v */
	.dvsarm2        = 0x9,  /* 1.20V */
	.dvsarm3        = 0x6,  /* 1.05V */
	.dvsarm4        = 0x4,  /* 0.95V */
	.dvsint1        = 0x7,  /* 1.10v */
	.dvsint2        = 0x5,  /* 1.00V */

	.set1       = S5PV210_GPH1(6),
	.set2       = S5PV210_GPH1(7),
	.set3       = S5PV210_GPH0(4),
};
#endif

/*
* device for HS0038(ir receiver)
* added by YangChunyuan
* modified by Concenwit-lhh
*/
#ifdef CONFIG_KEYBOARD_HS0038
static struct gpio_keys_button cw210_hs0038[] = {
		{
			.gpio		= S5PV210_GPH0(6),/* 4(- + backspace enter) */
			.desc		= "hs0038",
		},
};

static struct gpio_keys_platform_data cw210_hs0038_data = {
	.buttons	= cw210_hs0038,
	.nbuttons	= ARRAY_SIZE(cw210_hs0038),
};

struct platform_device cw210_hs0038_device = {
	.name		= "cw210-hs0038",
	.id		= -1,
	.dev		= {
		.platform_data	= &cw210_hs0038_data,
	}
};
#endif

/******************************************************************************
 * keypad
 * KEY1 -- UP  KEY2 -- DOWN KEY3 -- LEFT  KEY4 -- RIGHT KEY5 -- ENTER
*  KEY6 -- BACK KEY7 -- MENU KEY8 POWER
 ******************************************************************************/
#ifdef CONFIG_KEYBOARD_S3C_GPIO
static struct gpio_keys_button gpio_buttons[] = {

	{
		.gpio		= S5PV210_GPH0(0),
		.code		= KEY_UP,
		.desc		= "KEY_UP",
		.active_low	= 1,
		.wakeup		= 1,
	},
	{
		.gpio		= S5PV210_GPH0(1),
		.code		= KEY_DOWN,
		.desc		= "KEY_DOWN",
		.active_low	= 1,
		.wakeup		= 1,
	},	

	{
		.gpio		= S5PV210_GPH0(2),
		.code		= KEY_LEFT,
		.desc		= "KEY_LEFT",
		.active_low	= 1,
		.wakeup		= 1,

	},
	{
		.gpio		= S5PV210_GPH0(3),
		.code		= KEY_RIGHT,
		.desc		= "KEY_RIGHT",
		.active_low	= 1,
		.wakeup		= 1,
	},
	{
		.gpio		= S5PV210_GPH0(4),
		.code		= 232,
		.desc		= "DPAD_CENTER",
		.active_low	= 1,
		.wakeup		= 1,
	},		
	{
		.gpio		= S5PV210_GPH0(5),
		.code		= 158,
		.desc		= "BACK",
		.active_low	= 1,
		.wakeup		= 1,
	},
	{
		.gpio		= S5PV210_GPH2(6),
		.code		= 139,
		.desc		= "KEY_MENU_SHARD",
		.active_low	= 1,
		.wakeup		= 1,
	},		
	{
		.gpio		= S5PV210_GPH2(7),
		.code		= 116,
		.desc		= "POWER",
		.active_low	= 1,
		.wakeup		= 1,
	},
};

static struct gpio_keys_platform_data gpio_button_data = {
	.buttons	= gpio_buttons,
	.nbuttons	= ARRAY_SIZE(gpio_buttons),
};

static struct platform_device s3c_device_gpio_button = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= {
		.platform_data	= &gpio_button_data,
	}
};
#endif
/*********************************************************************************************************/


static void __init smdkc110_setup_clocks(void)
{
	struct clk *pclk;
	struct clk *clk;

#ifdef CONFIG_S3C_DEV_HSMMC
	/* set MMC0 clock */
	clk = clk_get(&s3c_device_hsmmc0.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
				clk_get_rate(clk));
#endif

#ifdef CONFIG_S3C_DEV_HSMMC1
	/* set MMC1 clock */
	clk = clk_get(&s3c_device_hsmmc1.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
				clk_get_rate(clk));
#endif

#ifdef CONFIG_S3C_DEV_HSMMC2
	/* set MMC2 clock */
	clk = clk_get(&s3c_device_hsmmc2.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
				clk_get_rate(clk));
#endif

#ifdef CONFIG_S3C_DEV_HSMMC3
	/* set MMC3 clock */
	clk = clk_get(&s3c_device_hsmmc3.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
			 clk_get_rate(clk));
#endif
}

#if defined(CONFIG_TOUCHSCREEN_S3C)
static struct s3c_ts_mach_info s3c_ts_platform __initdata = {
	.delay                  = 10000,//20000 10000
	.presc                  = 49,//49
	.oversampling_shift     = 3,
	.resol_bit              = 10,
	.s3c_adc_con            = ADC_TYPE_2,
};

#define S3C_PA_ADC_1 S3C_PA_ADC+0x1000
/* Touch srcreen */
static struct resource s3c_ts_resource[] = {
	[0] = {
		.start = S3C_PA_ADC_1,
		.end   = S3C_PA_ADC_1 + SZ_4K - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_PENDN1,
		.end   = IRQ_PENDN1,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_ADC1,
		.end   = IRQ_ADC1,
		.flags = IORESOURCE_IRQ,
	}
};

struct platform_device s3c_device_ts = {
	.name		  = "s3c-ts",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s3c_ts_resource),
	.resource	  = s3c_ts_resource,
};

void __init s3c_ts_set_platdata(struct s3c_ts_mach_info *pd)
{
	struct s3c_ts_mach_info *npd;

	npd = kmalloc(sizeof(*npd), GFP_KERNEL);
	if (npd) {
		memcpy(npd, pd, sizeof(*npd));
		s3c_device_ts.dev.platform_data = npd;
	} else {
		pr_err("no memory for Touchscreen platform data\n");
	}
}
#endif

#if defined(CONFIG_KEYPAD_S3C) || defined(CONFIG_KEYPAD_S3C_MODULE)
#if defined(CONFIG_KEYPAD_S3C_MSM)
void s3c_setup_keypad_cfg_gpio(void)
{
	unsigned int gpio;
	unsigned int end;

	/* gpio setting for KP_COL0 */
	s3c_gpio_cfgpin(S5PV210_GPJ1(5), S3C_GPIO_SFN(3));
	s3c_gpio_setpull(S5PV210_GPJ1(5), S3C_GPIO_PULL_NONE);

	/* gpio setting for KP_COL1 ~ KP_COL7 and KP_ROW0 */
	end = S5PV210_GPJ2(8);
	for (gpio = S5PV210_GPJ2(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	/* gpio setting for KP_ROW1 ~ KP_ROW8 */
	end = S5PV210_GPJ3(8);
	for (gpio = S5PV210_GPJ3(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	/* gpio setting for KP_ROW9 ~ KP_ROW13 */
	end = S5PV210_GPJ4(5);
	for (gpio = S5PV210_GPJ4(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
#else
void s3c_setup_keypad_cfg_gpio(int rows, int columns)
{
	unsigned int gpio;
	unsigned int end;

	end = S5PV210_GPH3(rows);

	/* Set all the necessary GPH2 pins to special-function 0 */
	for (gpio = S5PV210_GPH3(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
	}

	end = S5PV210_GPH2(columns);

	/* Set all the necessary GPK pins to special-function 0 */
	for (gpio = S5PV210_GPH2(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
#endif /* if defined(CONFIG_KEYPAD_S3C_MSM)*/
EXPORT_SYMBOL(s3c_setup_keypad_cfg_gpio);
#endif

#ifdef CONFIG_DM9000
static void __init smdkc110_dm9000_set(void)
{
	unsigned int tmp;

	tmp = ((0<<28)|(3<<24)|(7<<16)|(1<<12)|(3<<8)|(6<<4)|(0<<0));
	__raw_writel(tmp, (S5P_SROM_BW+0x08));//Bc1
	
	tmp = __raw_readl(S5P_SROM_BW);
	tmp &= ~(0xf << 4);
	

	tmp |= (0x1 << 4);
	tmp |= (0x2 << 4);

	__raw_writel(tmp, S5P_SROM_BW);

	tmp = __raw_readl(S5PV210_MP01CON);
	tmp &= ~(0xf << 4);
	tmp |= (2 << 4);

	__raw_writel(tmp, S5PV210_MP01CON);
}
#endif

#define S5PV210_GPD_0_0_TOUT_0  (0x2)
#define S5PV210_GPD_0_1_TOUT_1  (0x2 << 4)
#define S5PV210_GPD_0_2_TOUT_2  (0x2 << 8)
#define S5PV210_GPD_0_3_TOUT_3  (0x2 << 12)

#ifdef CONFIG_FB_S3C
#ifdef CONFIG_FB_S3C_LTE480WV
static struct s3cfb_lcd lte480wv = {
	#if 1
	.width	= 800,
	.height	= 480,
	.bpp	= 16,
	.freq	= 70,

	.timing = {
		.h_fp	= 210,
		.h_bp	= 16,
		.h_sw	= 30,
		.v_fp	= 22,
		.v_fpe	= 1,
		.v_bp	= 10,
		.v_bpe	= 1,
		.v_sw	= 13,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
	#endif
};
#elif defined(CONFIG_FB_S3C_LCD800480)
static struct s3cfb_lcd lte480wv = {
	.width	= 800,//800
	.height	= 480,//480
	.bpp	= 24,//24位
	.freq	= 60,//70 60

	.timing = {
		.h_fp	= 40,
		.h_bp	= 40,
		.h_sw	= 48,
		.v_fp	= 14,
		.v_fpe	= 1,
		.v_bp	= 29,
		.v_bpe	= 1,
		.v_sw	= 3,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#elif defined(CONFIG_FB_S3C_LCD800600)
static struct s3cfb_lcd lte480wv = {
	.width	= 800,//800
	.height	= 600,//480
	.bpp	= 24,//24位
	.freq	= 60,//70 60

	.timing = {
		.h_fp	= 15,
		.h_bp	= 47,
		.h_sw	= 95,
		.v_fp	= 12,//12
		.v_fpe	= 1,
		.v_bp	= 16,
		.v_bpe	= 1,//1
		.v_sw	= 4,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#elif defined(CONFIG_FB_AT070TN92)
static struct s3cfb_lcd lte480wv = {
	.width		= 800,
	.height	= 480,
	.bpp		= 24,
	.freq		= 28,
	.clkval_f	= 6,//3
//		27,//HBPD
//		14,//HFPD	
//		20,//10,//HSPW	
	.timing = {
		.h_fp	= 14,//210,
		.h_bp	= 27,//16,
		.h_sw	= 20,//30,
		.v_fp	= 22,
		.v_fpe	= 1,
		.v_bp	= 10,
		.v_bpe	= 1,
		.v_sw	= 13,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#elif defined(CONFIG_FB_S3C_VGA1024768)
static struct s3cfb_lcd lte480wv = {
	.width	= 1024,//800
	.height	= 768,//480
	.bpp	= 24,//24位
	.freq	= 45,//70 60

	.timing = {
		.h_fp	= 60,
		.h_bp	= 120,
		.h_sw	= 50,
		.v_fp	= 3,
		.v_fpe	= 1,
		.v_bp	= 4,
		.v_bpe	= 1,
		.v_sw	= 3,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};

#elif defined(CONFIG_FB_S3C_LCD640480)
static struct s3cfb_lcd lte480wv = {
	.width	= 640,//800
	.height	= 480,//480
	.bpp	= 24,//24位
	.freq	= 60,//70 60

	.timing = {
		.h_fp	= 16,
		.h_bp	= 144,
		.h_sw	= 10,
		.v_fp	= 32,
		.v_fpe	= 1,
		.v_bp	= 13,
		.v_bpe	= 1,
		.v_sw	= 2,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#elif defined(CONFIG_FB_S3C_VGA640480)
static struct s3cfb_lcd lte480wv = {
	.width	= 800,//
	.height	= 600,//
	.bpp	= 24,//24位
	.freq	= 70,//65,//70 60
	.timing = {
		.h_fp	= 37,
		.h_bp	= 85,
		.h_sw	= 128,
		.v_fp	= 1,
		.v_fpe	= 1,
		.v_bp	= 21,
		.v_bpe	= 1,
		.v_sw	= 4,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
#if 0
	.width	= 600,//
	.height	= 480,//
	.bpp	= 24,//24位
	.freq	= 60,//70 60

	.timing = {
		.h_fp	= 13,
		.h_bp	= 45,
		.h_sw	= 96,
		.v_fp	= 9,
		.v_fpe	= 1,
		.v_bp	= 30,
		.v_bpe	= 1,
		.v_sw	= 15,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
#endif

};
#elif defined(CONFIG_FB_S3C_LCD480272)
static struct s3cfb_lcd lte480wv = {
	.width	= 480,//800
	.height	= 272,//480
	.bpp	= 24,//24位
	.freq	= 60,//70 60

	.timing = {
		.h_fp	= 2,
		.h_bp	= 2,
		.h_sw	= 41,
		.v_fp	= 3,
		.v_fpe	= 1,
		.v_bp	= 2,
		.v_bpe	= 1,
		.v_sw	= 10,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#endif

static void lte480wv_cfg_gpio(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF0(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF0(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF1(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF1(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF2(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF2(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 4; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF3(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF3(i), S3C_GPIO_PULL_NONE);
	}

	/* mDNIe SEL: why we shall write 0x2 ? */
	writel(0x2, S5P_MDNIE_SEL);

	/* drive strength to max */
	writel(0xffffffff, S5PV210_GPF0_BASE + 0xc);
	writel(0xffffffff, S5PV210_GPF1_BASE + 0xc);
	writel(0xffffffff, S5PV210_GPF2_BASE + 0xc);
	writel(0x000000ff, S5PV210_GPF3_BASE + 0xc);
}


static int lte480wv_backlight_on(struct platform_device *pdev)
{
	int err;

	err = gpio_request(S5PV210_GPD0(0), "GPD0");

	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}
	gpio_direction_output(S5PV210_GPD0(0), 1);
#if defined(CONFIG_FB_S3C_VGA640480) || defined(CONFIG_FB_AT070TN92) || defined(CONFIG_FB_S3C_VGA800600)
	s3c_gpio_cfgpin(S5PV210_GPD0(0), /*S5PV210_GPD_0_0_TOUT_0*/1);
#else
	s3c_gpio_cfgpin(S5PV210_GPD0(0), S5PV210_GPD_0_0_TOUT_0);
#endif
	gpio_free(S5PV210_GPD0(0));

	return 0;
}

static int lte480wv_backlight_off(struct platform_device *pdev, int onoff)
{
	int err;

	err = gpio_request(S5PV210_GPD0(0), "GPD0");
	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
				"lcd backlight control\n");
		return err;
	}

	gpio_direction_output(S5PV210_GPD0(0), 0);

	gpio_free(S5PV210_GPD0(0));
	return 0;
}

static int lte480wv_reset_lcd(struct platform_device *pdev)
{
	return 0;
}

static struct s3c_platform_fb lte480wv_fb_data __initdata = {
	.hw_ver	= 0x62,
	.nr_wins = 5,
	.default_win = CONFIG_FB_S3C_DEFAULT_WINDOW,
	.swap = FB_SWAP_WORD | FB_SWAP_HWORD,

	.lcd = &lte480wv,
	.cfg_gpio	= lte480wv_cfg_gpio,
	.backlight_on	= lte480wv_backlight_on,
	.backlight_onoff    = lte480wv_backlight_off,
	.reset_lcd	= lte480wv_reset_lcd,
};
#endif


#ifdef CONFIG_CW210_VGA
static struct s3cfb_lcd vga = {
	.width	= 800,
	.height	= 600,
	.bpp	= 24,
	.freq	= 60,

	.timing = {
		.h_fp	= 10,
		.h_bp	= 20,
		.h_sw	= 10,
		.v_fp	= 10,
		.v_fpe	= 1,
		.v_bp	= 20,
		.v_bpe	= 1,
		.v_sw	= 10,
	},

	.polarity = {
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};

static void vga_cfg_gpio(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF0(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF0(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF1(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF1(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF2(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF2(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 4; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF3(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF3(i), S3C_GPIO_PULL_NONE);
	}

	/* mDNIe SEL: why we shall write 0x2 ? */
	writel(0x2, S5P_MDNIE_SEL);

	/* drive strength to max */
	writel(0xffffffff, S5PV210_GPF0_BASE + 0xc);
	writel(0xffffffff, S5PV210_GPF1_BASE + 0xc);
	writel(0xffffffff, S5PV210_GPF2_BASE + 0xc);
	writel(0x000000ff, S5PV210_GPF3_BASE + 0xc);
}


static int vga_backlight_on(struct platform_device *pdev)
{
	return 0;
}

static int vga_backlight_off(struct platform_device *pdev, int onoff)
{

}

static int vga_reset_lcd(struct platform_device *pdev)
{

	return 0;
}

static struct s3c_platform_fb vga_fb_data __initdata = {
	.hw_ver	= 0x62,
	.nr_wins = 5,
	.default_win = CONFIG_FB_S3C_DEFAULT_WINDOW,
	.swap = FB_SWAP_WORD | FB_SWAP_HWORD,

	.lcd = &vga,
	.cfg_gpio	= vga_cfg_gpio,
	.backlight_on	= vga_backlight_on,
	.backlight_onoff    = vga_backlight_off,
	.reset_lcd	= vga_reset_lcd,
};
#endif

#ifdef CONFIG_S3C64XX_DEV_SPI

#define SMDK_MMCSPI_CS 0
static struct s3c64xx_spi_csinfo smdk_spi0_csi[] = {
	[SMDK_MMCSPI_CS] = {
		.line = S5PV210_GPB(1),
		.set_level = gpio_set_value,
		.fb_delay = 0x0,
	},
};

static struct s3c64xx_spi_csinfo smdk_spi1_csi[] = {
	[SMDK_MMCSPI_CS] = {
		.line = S5PV210_GPB(5),
		.set_level = gpio_set_value,
		.fb_delay = 0x0,
	},
};

static struct spi_board_info s3c_spi_devs[] __initdata = {
	[0] = {
		.modalias        = "spidev",	/* device node name */
		.mode            = SPI_MODE_0,	/* CPOL=0, CPHA=0 */
		.max_speed_hz    = 10000000,
		/* Connected to SPI-0 as 1st Slave */
		.bus_num         = 0,
		.irq             = IRQ_SPI0,
		.chip_select     = 0,
		.controller_data = &smdk_spi0_csi[SMDK_MMCSPI_CS],
	},
	[1] = {
		.modalias        = "spidev",	/* device node name */
		.mode            = SPI_MODE_0,	/* CPOL=0, CPHA=0 */
		.max_speed_hz    = 10000000,
		/* Connected to SPI-1 as 1st Slave */
		.bus_num         = 1,
		.irq             = IRQ_SPI1,
		.chip_select     = 0,
		.controller_data = &smdk_spi1_csi[SMDK_MMCSPI_CS],
	},
};
#endif

#ifdef CONFIG_HAVE_PWM
struct s3c_pwm_data {
	/* PWM output port */
	unsigned int gpio_no;
	const char  *gpio_name;
	unsigned int gpio_set_value;
};

struct s3c_pwm_data pwm_data[] = {
	{
		.gpio_no    = S5PV210_GPD0(0),
		.gpio_name  = "GPD",
#if defined(CONFIG_FB_S3C_VGA640480) || defined(CONFIG_FB_AT070TN92) || defined(CONFIG_FB_S3C_VGA800600)
		.gpio_set_value = 1,
#else
		.gpio_set_value = S5PV210_GPD_0_0_TOUT_0,
#endif
	},{
		.gpio_no    = S5PV210_GPD0(1),
		.gpio_name  = "GPD",
		.gpio_set_value = S5PV210_GPD_0_1_TOUT_1,
	}, {
		.gpio_no    = S5PV210_GPD0(2),
		.gpio_name      = "GPD",
		.gpio_set_value = S5PV210_GPD_0_2_TOUT_2,
	}, {
		.gpio_no    = S5PV210_GPD0(3),
		.gpio_name      = "GPD",
		.gpio_set_value = S5PV210_GPD_0_3_TOUT_3,
	}
};
#endif

#if defined(CONFIG_BACKLIGHT_PWM)
static struct platform_pwm_backlight_data smdk_backlight_data = {
	.pwm_id  = 0,
	.max_brightness = 255,
	.dft_brightness = 255,
	.pwm_period_ns  = 50000,//25000,由于背光频率太高，这个IO端口长度不行
};

static struct platform_device smdk_backlight_device = {
	.name      = "pwm-backlight",
	.id        = -1,
	.dev        = {
		.parent = &s3c_device_timer[0].dev,
		.platform_data = &smdk_backlight_data,
	},
};

static void __init smdk_backlight_register(void)
{
	int ret;
#ifdef CONFIG_HAVE_PWM
	int i, ntimer;

	/* Timer GPIO Set */
	ntimer = ARRAY_SIZE(pwm_data);
	for (i = 0; i < ntimer; i++) {
		if (gpio_is_valid(pwm_data[i].gpio_no)) {
			ret = gpio_request(pwm_data[i].gpio_no,
				pwm_data[i].gpio_name);
			if (ret) {
				printk(KERN_ERR "failed to get GPIO for PWM\n");
				return;
			}
			s3c_gpio_cfgpin(pwm_data[i].gpio_no,
				pwm_data[i].gpio_set_value);

			gpio_free(pwm_data[i].gpio_no);
		}
	}
#endif
	ret = platform_device_register(&smdk_backlight_device);
	if (ret)
		printk(KERN_ERR "smdk: failed to register backlight device: %d\n", ret);
}
#endif

#ifdef CONFIG_S5P_ADC
static struct s3c_adc_mach_info s3c_adc_platform __initdata = {
	/* s5pc110 support 12-bit resolution */
	.delay  = 10000,
	.presc  = 49,
	.resolution = 12,
};
#endif

#define BOARD_VER  3

#if(BOARD_VER == 1)
#define GPIO_CAM0_RST		S5PV210_GPC1(1)
#define GPIO_CAM1_RST		S5PV210_GPC1(1)
#define GPIO_CAM0_POWERDOWN	S5PV210_GPE1(4)		//
#define GPIO_CAM1_POWERDOWN	S5PV210_GPC1(0)
#elif(BOARD_VER == 2)
#define GPIO_CAM0_RST		S5PV210_GPH3(6)
#define GPIO_CAM1_RST		S5PV210_GPJ3(5)
#define GPIO_CAM0_POWERDOWN	S5PV210_GPE1(4)		//
#define GPIO_CAM1_POWERDOWN	S5PV210_GPC1(0)
#elif(BOARD_VER == 3) 
#define GPIO_CAM0_RST		S5PV210_GPH3(6)
#define GPIO_CAM1_RST		S5PV210_GPH3(7)
#define GPIO_CAM0_POWERDOWN	S5PV210_GPE1(4)		//
#define GPIO_CAM1_POWERDOWN	S5PV210_GPE1(4)
#endif
#define GPIO_RST_9650		GPIO_CAM0_RST
#define GPIO_PWD_9650		GPIO_CAM0_POWERDOWN
#define GPIO_RST_3640		GPIO_CAM0_RST
#define GPIO_PWD_3640		GPIO_CAM0_POWERDOWN
#define GPIO_RST_7113		GPIO_CAM0_RST
#define GPIO_PWD_7113		GPIO_CAM0_POWERDOWN
#define GPIO_RST_5150		GPIO_CAM0_RST
#define GPIO_PWD_5150		GPIO_CAM0_POWERDOWN

#define IIC_NUM_CAM_USED		6


void gpio_cam_rst_cfg(unsigned int gpio_rst,int rst_statue)
{
	int err;


	err = gpio_request(gpio_rst, "CAM_RST");
	if (err)
		printk(KERN_ERR "#### failed to request GP_RST\n");	
	s3c_gpio_cfgpin(gpio_rst, S3C_GPIO_SFN(1));

	s3c_gpio_cfgpin(gpio_rst, S3C_GPIO_SFN(1));
	s3c_gpio_setpull(gpio_rst, S3C_GPIO_PULL_NONE);

	if(rst_statue != 0)
		gpio_direction_output(gpio_rst, 1);
	else 
		gpio_direction_output(gpio_rst, 0);
	gpio_free(gpio_rst);
	mdelay(1);
}

void gpio_cam_pwd_cfg(unsigned int gpio_pwd,int pwd_statue)
{
	int err;

	err = gpio_request(gpio_pwd, "CAM_PWD");
	if (err)
		printk(KERN_ERR "#### failed to request GP_PWD\n");	

	s3c_gpio_cfgpin(gpio_pwd, S3C_GPIO_SFN(1));
	s3c_gpio_setpull(gpio_pwd, S3C_GPIO_PULL_NONE);
	if(pwd_statue != 0)
		gpio_direction_output(gpio_pwd, 1);
	else 
		gpio_direction_output(gpio_pwd, 0);
	gpio_free(GPIO_CAM0_POWERDOWN);
	mdelay(1);
}

#ifdef CONFIG_CAMERA_TVP5150

/*
 * External camera reset
 * Because the most of cameras take i2c bus signal, so that
 * you have to reset at the boot time for other i2c slave devices.
 * This function also called at fimc_init_camera()
 * Do optimization for cameras on your platform.
*/
static int tvp5150_power(int onoff)//low_reset GPE1_4
{
#if 1
	if(onoff != 0)		//on
	{
		gpio_cam_pwd_cfg(GPIO_PWD_5150,0);					//cam0 on
		mdelay(1);		
		gpio_cam_pwd_cfg(GPIO_PWD_5150,1);
		mdelay(1);
		gpio_cam_rst_cfg(GPIO_RST_5150,0);						//cam0 on
		mdelay(1);
		gpio_cam_rst_cfg(GPIO_RST_5150,1);						//cam0 on
		printk("5150_poweron \n");
	}
	else											//cam1 not refrect 
	{	
		gpio_cam_rst_cfg(GPIO_RST_5150,0);						//cam0 off
		gpio_cam_pwd_cfg(GPIO_PWD_5150,0);					//cam0 off
		printk("5150_poweroff \n");
	}
#elif 1
	int err;
	err = gpio_request(S5PV210_GPE1(4), "GPE1_4");
	if (err)
		printk(KERN_ERR "#### failed to request GPE1_4 for RESET\n");	

	s3c_gpio_setpull(S5PV210_GPE1(4), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV210_GPE1(4), 0);
	mdelay(50);
	gpio_direction_output(S5PV210_GPE1(4), 1);
	gpio_free(S5PV210_GPE1(4));
#endif
	return 0;
}

static struct tvp5150_platform_data tvp5150_plat =
{
	.default_width = 720,
	.default_height = 288,
	.pixelformat = V4L2_PIX_FMT_VYUY,
	.freq = 27000000,
	.is_mipi = 0,
};

static struct i2c_board_info  tvp5150_i2c_info = 
{
	I2C_BOARD_INFO("tvp5150", 0xB8>>1),
	.platform_data = &tvp5150_plat,
};

static struct s3c_platform_camera tvp5150 = {
	.id		= CAMERA_PAR_A,	
	.type		= CAM_TYPE_ITU,
	.fmt		= ITU_656_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= IIC_NUM_CAM_USED,
	.info		= &tvp5150_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_VYUY,
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_cam0",
	.clk_rate	= 27000000,
	.width		= 720,
	.height		= 288,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 720,
		.height	= 288,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,

	.cam_power	= tvp5150_power,

};
#endif

#ifdef CONFIG_CAMERA_OV3640

static int smdkv210_OV3640_power(int onoff)//low_reset GPE1_4
{
	if(onoff != 0)		//on
	{
		gpio_cam_rst_cfg(GPIO_RST_3640,1);						//cam0 on
		gpio_cam_pwd_cfg(GPIO_PWD_3640,0);					//cam0 on
		printk("3640_poweron \n");
	}
	else											//cam1 not refrect 
	{	
		gpio_cam_rst_cfg(GPIO_RST_3640,0);						//cam0 off
		gpio_cam_pwd_cfg(GPIO_PWD_3640,1);					//cam0 off
		printk("3640_poweroff \n");
	}

	return 0;

}

static struct ov3640_platform_data ov3640_plat =
{
	.default_width = 640,
	.default_height = 480,
	.pixelformat = V4L2_PIX_FMT_VYUY,
	.freq = 40000000,
	.is_mipi = 0,
};

static struct i2c_board_info  ov3640_i2c_info = 
{
	I2C_BOARD_INFO("OV3640", 0x78>>1),
	.platform_data = &ov3640_plat,
};

static struct s3c_platform_camera ov3640 = {
	.id		= CAMERA_PAR_A,
	.type		= CAM_TYPE_ITU,
	.fmt		= ITU_601_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_YCBYCR,
	.i2c_busnum	= IIC_NUM_CAM_USED,
	.info		= &ov3640_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_VYUY,
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_cam0",
	.clk_rate	= 40000000,
	.line_length	= 640,
	.width		= 640,
	.height		= 480,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 640,
		.height	= 480,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 0,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,

	.cam_power	= smdkv210_OV3640_power,

};
#endif

#ifdef CONFIG_CAMERA_OV9650
static int tqcam_OV9650_power(int onoff)//low_reset GPE1_4
{
	if(onoff != 0)		//on
	{
		gpio_cam_rst_cfg(GPIO_RST_9650,0);						//cam0 on
		gpio_cam_pwd_cfg(GPIO_PWD_9650,0);					//cam0 on
		printk("9650_poweron \n");
	}
	else											//cam1 not refrect 
	{	
		gpio_cam_rst_cfg(GPIO_RST_9650,1);						//cam0 off
		gpio_cam_pwd_cfg(GPIO_PWD_9650,0);					//cam0 off
		printk("9650_poweroff \n");
	}

	return 0;
}

static struct ov3640_platform_data ov9650_plat =
{
	.default_width = 640,
	.default_height = 480,
	.pixelformat = V4L2_PIX_FMT_VYUY,
	.freq = 24000000,
	.is_mipi = 0,
};

static struct i2c_board_info  ov9650_i2c_info = 
{
	I2C_BOARD_INFO("OV9650", 0x60>>1),
	.platform_data = &ov9650_plat,
};

static struct s3c_platform_camera ov9650 = {
	.id			= CAMERA_PAR_A,
	.type		= CAM_TYPE_ITU,
	.fmt		= ITU_601_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= IIC_NUM_CAM_USED,
	.info		= &ov9650_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_VYUY,
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_cam0",
	.clk_rate	= 24000000,
//	.line_length	= 640,
	.line_length	= 1920,
	.width		= 640,
	.height	= 480,
	.window	= {
		.left	= 0,
		.top	= 0,
		.width	= 640,
		.height= 480,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 0,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,

//	.cam_power	= smdkv210_OV9650_power,
	.cam_power	= tqcam_OV9650_power,

};
#endif

#ifdef CONFIG_CAMERA_SAA7113

#define SRC_H	720
#define SRC_V	288
#define FREQ 27000000

static int tqcam_SAA7113_power(int onoff)//low_reset GPE1_4
{
	int err;
	if(onoff != 0)		//on
	{
		gpio_cam_rst_cfg(GPIO_RST_7113,0);						//cam0 on
		gpio_cam_pwd_cfg(GPIO_PWD_7113,1);					//cam0 on
		printk("7113_poweron \n");
	}
	else											//cam1 not refrect 
	{	
		gpio_cam_rst_cfg(GPIO_RST_7113,1);						//cam0 off
		gpio_cam_pwd_cfg(GPIO_PWD_7113,0);					//cam0 off
		printk("7113_poweroff \n");
	}	
	return 0;
}

static struct ov3640_platform_data saa7113_plat =
{
	.default_width = SRC_H,//
	.default_height = SRC_V,//
	.pixelformat = V4L2_PIX_FMT_VYUY,
	.freq = FREQ,//
	.is_mipi = 0,//
};

static struct i2c_board_info  saa7113_i2c_info = 
{
	I2C_BOARD_INFO("SAA7113", 0x4A>>1),
	.platform_data = &saa7113_plat,
};



static struct s3c_platform_camera saa7113 = {
	.id		= CAMERA_PAR_A,	//					//arch/arm/plat-s5p/include/fimc.h
	.type		= CAM_TYPE_ITU,//
//	.fmt		= ITU_601_YCBCR422_8BIT,//
	.fmt		= ITU_656_YCBCR422_8BIT,//
	.order422	= CAM_ORDER422_8BIT_CBYCRY,//
	.i2c_busnum	= IIC_NUM_CAM_USED,//
	.info		= &saa7113_i2c_info,//
	.pixelformat	= V4L2_PIX_FMT_VYUY,
	.srclk_name	= "mout_mpll",//"mout_mpll", "xusbxti",
	.clk_name	= "sclk_cam0",//"sclk_cam0","sclk_cam",	//arch/arm/mach-s5pv210/clock.c
	.clk_rate	= FREQ,
	.line_length	= SRC_H*2,
	.width		= SRC_H,
	.height	= SRC_V,
	.window	= {
		.left	= 0,
		.top	= 0,
		.width	= 640,
		.height= 480,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
	.cam_power	= tqcam_SAA7113_power,
};
#endif

/* Interface setting */
static struct s3c_platform_fimc fimc_plat_lsi = {
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_fimc",
	.lclk_name	= "sclk_fimc_lclk",
	.clk_rate	= 166750000,
	.default_cam	= CAMERA_PAR_A,
	.camera		= {
#ifdef CONFIG_CAMERA_OV3640
		&ov3640,
#endif
#ifdef CONFIG_CAMERA_OV9650
		&ov9650,
#endif
#ifdef CONFIG_CAMERA_SAA7113
		&saa7113,
#endif	
#ifdef CONFIG_CAMERA_TVP5150
		&tvp5150,
#endif	
	},
	.hw_ver		= 0x43,
};



#ifdef CONFIG_VIDEO_JPEG_V2
static struct s3c_platform_jpeg jpeg_plat __initdata = {
	.max_main_width	= 800,
	.max_main_height	= 480,
	.max_thumb_width	= 320,
	.max_thumb_height	= 240,
};
#endif
#if defined(CONFIG_TOUCHSCREEN_S3C_GX801)
void s3c_gx801_cfg_gpio(struct platform_device *dev)
{
}

static struct s3c2410_platform_i2c cw210_gt801_pdata __initdata = {
   .flags        = 0,
   .slave_addr    = 0xaa>>1,
   .frequency    = 1000*100,
   .sda_delay    =  10,
   .cfg_gpio = s3c_gx801_cfg_gpio,
};
#endif
#ifdef CONFIG_SND_SOC_WM8960_CW210
#include <sound/wm8960.h>
static struct wm8960_data wm8960_pdata = {
	.capless		= 0,
	.dres			= WM8960_DRES_400R,
};
#endif

static struct i2c_board_info i2c_dev[] __initdata = {
	{
		I2C_BOARD_INFO("at24cxx", 0x50)
	}
};

/* I2C0 */
static struct i2c_board_info i2c_devs0[] __initdata = {
#ifdef CONFIG_SND_SOC_WM8960_CW210
	{
		I2C_BOARD_INFO("wm8960", 0x1a),
		.platform_data  = &wm8960_pdata,
	},
#endif
#ifdef CONFIG_SND_SOC_WM8580
	{
		I2C_BOARD_INFO("wm8580", 0x1b),
	},
#endif

};

/* I2C1 */
static struct i2c_board_info i2c_devs1[] __initdata = {
#ifdef CONFIG_VIDEO_TV20
	{
		I2C_BOARD_INFO("s5p_ddc", (0x74>>1)),
	},
#endif
};

/* I2C2 */
static struct i2c_board_info i2c_devs2[] __initdata = {

};
/*I2C5*/
static struct i2c_gpio_platform_data i2c5_platdata = {
#if 0
        .sda_pin                = S5PV210_GPD1(0),//IIC0
	    .scl_pin                = S5PV210_GPD1(1),
#else
        .sda_pin                = S5PV210_GPD1(4),//IIC2
        .scl_pin                = S5PV210_GPD1(5),
#endif
        .udelay                 = 2,
        .sda_is_open_drain      = 0,
        .scl_is_open_drain      = 0,
        .scl_is_output_only     = 0.
};

//------------------------------------------------------------------------------
#include <linux/i2c-gpio.h>
#if 0
#define GPIO_SCK5		S5PV210_GPD1(3)//S5PV210_GPG2(5)
#define GPIO_SDA5		S5PV210_GPD1(2)//S5PV210_GPG2(6)
#elif 1
#define GPIO_SCK6		S5PV210_GPG2(5)
#define GPIO_SDA6		S5PV210_GPG2(6)
#endif 

static struct i2c_gpio_platform_data i2c6_platdata = {
	.sda_pin                = GPIO_SDA6,
	.scl_pin                = GPIO_SCK6,

};

static struct platform_device s3c_device_i2c6 = {
	.name                   = "i2c-gpio",
	.id                     = 6,
	.dev = {
		.platform_data  = &i2c6_platdata,
	},
 };


struct platform_device   s3c_device_i2c5 = {
        .name                   = "i2c-gpio",
        .id                     = 5,
        .dev.platform_data      = &i2c5_platdata,
};

static struct i2c_board_info i2c_devs5[] __initdata = {
#if defined(CONFIG_TOUCHSCREEN_S3C_GX801)
	{ I2C_BOARD_INFO("gx801", 0xaa>>1),
	  .irq = IRQ_EINT(14),
	  .platform_data  = &cw210_gt801_pdata,	
	},
#endif
};

#define S5PV210_PS_HOLD_CONTROL_REG (S3C_VA_SYS+0xE81C)
static void smdkc110_power_off(void)
{
	/* PS_HOLD output High --> Low */
	writel(readl(S5PV210_PS_HOLD_CONTROL_REG) & 0xFFFFFEFF,
			S5PV210_PS_HOLD_CONTROL_REG);

	while (1);
}

#ifdef CONFIG_BATTERY_S3C
struct platform_device sec_device_battery = {
	.name   = "sec-fake-battery",
	.id = -1,
};
#endif

#ifdef CONFIG_ANDROID_PMEM
static struct android_pmem_platform_data pmem_gpu1_pdata = {
	.name = "pmem_gpu1",
	.no_allocator = 1,
	.cached = 1,
	.buffered = 1,
	.start = 0,
	.size = 0,
};

static struct platform_device pmem_gpu1_device = {
	.name = "android_pmem",
	.id = 1,
	.dev = { .platform_data = &pmem_gpu1_pdata },
};

static void __init android_pmem_set_platdata(void)
{
	pmem_gpu1_pdata.start =
		(u32)s5p_get_media_memory_bank(S5P_MDEV_PMEM_GPU1, 0);
	pmem_gpu1_pdata.size =
		(u32)s5p_get_media_memsize_bank(S5P_MDEV_PMEM_GPU1, 0);
}
#endif

static struct platform_device *smdkc110_devices[] __initdata = {
#ifdef CONFIG_FIQ_DEBUGGER
	&s5pv210_device_fiqdbg_uart2,
#endif
#ifdef CONFIG_MTD_ONENAND
	&s5pc110_device_onenand,
#endif
#ifdef CONFIG_MTD_NAND
	&s3c_device_nand,
#endif
	&s5p_device_rtc,
#ifdef CONFIG_SND_S3C64XX_SOC_I2S_V4
//	&s5pv210_device_iis0,
#endif
	&s5pv210_device_iis0,
	&s5pv210_device_iis1, //lhh add test
#ifdef CONFIG_SND_S3C_SOC_AC97
	&s5pv210_device_ac97,
#endif
#ifdef CONFIG_SND_S3C_SOC_PCM
	&s5pv210_device_pcm0,
#endif
#ifdef CONFIG_SND_SOC_SPDIF
	&s5pv210_device_spdif,
#endif
	&s3c_device_wdt,

#ifdef CONFIG_FB_S3C
	&s3c_device_fb,
#endif
#ifdef CONFIG_DM9000
	&s5p_device_dm9000,
#endif
 
#ifdef CONFIG_VIDEO_MFC50
	&s3c_device_mfc,
#endif
#ifdef CONFIG_TOUCHSCREEN_S3C
	&s3c_device_ts,
#endif
	&s3c_device_keypad,
#ifdef CONFIG_S5P_ADC
//	&s3c_device_adc,
#endif
#ifdef CONFIG_VIDEO_FIMC
	&s3c_device_fimc0,
	&s3c_device_fimc1,
	&s3c_device_fimc2,
#endif
#ifdef CONFIG_VIDEO_FIMC_MIPI
	&s3c_device_csis,
#endif
#ifdef CONFIG_VIDEO_JPEG_V2
	&s3c_device_jpeg,
#endif
#ifdef CONFIG_VIDEO_G2D
	&s3c_device_g2d,
#endif
#ifdef CONFIG_VIDEO_TV20
	&s5p_device_tvout,
	&s5p_device_cec,
	&s5p_device_hpd,
#endif

	&s3c_device_g3d,
	&s3c_device_lcd,

	&s3c_device_i2c0,
#ifdef CONFIG_S3C_DEV_I2C1
	&s3c_device_i2c1,
#endif
#ifdef CONFIG_S3C_DEV_I2C2
	&s3c_device_i2c2,
#endif
	&s3c_device_i2c5,
	&s3c_device_i2c6,

#ifdef CONFIG_USB_EHCI_HCD
	&s3c_device_usb_ehci,
#endif
#ifdef CONFIG_USB_OHCI_HCD
	&s3c_device_usb_ohci,
#endif

#ifdef CONFIG_USB_GADGET
	&s3c_device_usbgadget,
#endif
#ifdef CONFIG_USB_ANDROID
	&s3c_device_android_usb,
#ifdef CONFIG_USB_ANDROID_MASS_STORAGE
	&s3c_device_usb_mass_storage,
#endif
#ifdef CONFIG_USB_ANDROID_RNDIS
	&s3c_device_rndis,
#endif
#endif
#ifdef CONFIG_BATTERY_S3C
	&sec_device_battery,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC
	&s3c_device_hsmmc0,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
	&s3c_device_hsmmc1,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
	&s3c_device_hsmmc2,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
	&s3c_device_hsmmc3,
#endif

#ifdef CONFIG_S3C64XX_DEV_SPI
	&s5pv210_device_spi0,
	&s5pv210_device_spi1,
#endif
#ifdef CONFIG_S5PV210_POWER_DOMAIN
	&s5pv210_pd_audio,
	&s5pv210_pd_cam,
	&s5pv210_pd_tv,
	&s5pv210_pd_lcd,
	&s5pv210_pd_g3d,
	&s5pv210_pd_mfc,
#endif
#ifdef CONFIG_SND_S5P_RP
	&s3c_device_rp, 
#endif
#ifdef CONFIG_HAVE_PWM
	&s3c_device_timer[0],
	&s3c_device_timer[1],
	&s3c_device_timer[2],
	&s3c_device_timer[3],
#endif
#ifdef CONFIG_KEYBOARD_S3C_GPIO
	&s3c_device_gpio_button,
#endif
#ifdef CONFIG_KEYBOARD_HS0038
	&cw210_hs0038_device,
#endif
};

static void __init smdkc110_map_io(void)
{
	s5p_init_io(NULL, 0, S5P_VA_CHIPID);
	s3c24xx_init_clocks(24000000);
	s5pv210_gpiolib_init();
	s3c24xx_init_uarts(smdkc110_uartcfgs, ARRAY_SIZE(smdkc110_uartcfgs));
	s5p_reserve_bootmem(smdkc110_media_devs, ARRAY_SIZE(smdkc110_media_devs));
#ifdef CONFIG_MTD_ONENAND
	s5pc110_device_onenand.name = "s5pc110-onenand";
#endif
#ifdef CONFIG_MTD_NAND
	s3c_device_nand.name = "s5pv210-nand";
#endif
	s5p_device_rtc.name = "smdkc110-rtc";
}

unsigned int pm_debug_scratchpad;

static void __init sound_init(void)
{
	u32 reg;

	reg = __raw_readl(S5P_CLK_OUT);
	reg &= ~(0x1f << 12);
	reg &= ~(0xf << 20);
	reg |= 0x12 << 12;
	reg |= 0x1  << 20;
	__raw_writel(reg, S5P_CLK_OUT);

	reg = __raw_readl(S5P_OTHERS);
	reg &= ~(0x3 << 8);
	reg |= 0x0 << 8;
	__raw_writel(reg, S5P_OTHERS);
}

#ifdef CONFIG_VIDEO_TV20
static void s3c_set_qos(void)
{
	/* VP QoS */
	__raw_writel(0x00400001, S5P_VA_DMC0 + 0xC8);
	__raw_writel(0x387F0022, S5P_VA_DMC0 + 0xCC);
	/* MIXER QoS */
	__raw_writel(0x00400001, S5P_VA_DMC0 + 0xD0);
	__raw_writel(0x3FFF0062, S5P_VA_DMC0 + 0xD4);
	/* LCD1 QoS */
	__raw_writel(0x00800001, S5P_VA_DMC1 + 0x90);
	__raw_writel(0x3FFF005B, S5P_VA_DMC1 + 0x94);
	/* LCD2 QoS */
	__raw_writel(0x00800001, S5P_VA_DMC1 + 0x98);
	__raw_writel(0x3FFF015B, S5P_VA_DMC1 + 0x9C);
	/* VP QoS */
	__raw_writel(0x00400001, S5P_VA_DMC1 + 0xC8);
	__raw_writel(0x387F002B, S5P_VA_DMC1 + 0xCC);
	/* DRAM Controller QoS */
	__raw_writel(((__raw_readl(S5P_VA_DMC0)&~(0xFFF<<16))|(0x100<<16)),
			S5P_VA_DMC0 + 0x0);
	__raw_writel(((__raw_readl(S5P_VA_DMC1)&~(0xFFF<<16))|(0x100<<16)),
			S5P_VA_DMC1 + 0x0);
	/* BUS QoS AXI_DSYS Control */
	__raw_writel(0x00000007, S5P_VA_BUS_AXI_DSYS + 0x400);
	__raw_writel(0x00000007, S5P_VA_BUS_AXI_DSYS + 0x420);
	__raw_writel(0x00000030, S5P_VA_BUS_AXI_DSYS + 0x404);
	__raw_writel(0x00000030, S5P_VA_BUS_AXI_DSYS + 0x424);
}
#endif

static bool console_flushed;

static void flush_console(void)
{
	if (console_flushed)
		return;

	console_flushed = true;

	printk("\n");
	pr_emerg("Restarting %s\n", linux_banner);
	if (!try_acquire_console_sem()) {
		release_console_sem();
		return;
	}

	mdelay(50);

	local_irq_disable();
	if (try_acquire_console_sem())
		pr_emerg("flush_console: console was locked! busting!\n");
	else
		pr_emerg("flush_console: console was locked!\n");
	release_console_sem();
}

static void smdkc110_pm_restart(char mode, const char *cmd)
{
	flush_console();
	arm_machine_restart(mode, cmd);
}

static void __init smdkc110_machine_init(void)
{
	arm_pm_restart = smdkc110_pm_restart;

	s3c_usb_set_serial();
	platform_add_devices(smdkc110_devices, ARRAY_SIZE(smdkc110_devices));
#ifdef CONFIG_ANDROID_PMEM
	platform_device_register(&pmem_gpu1_device);
#endif
	pm_power_off = smdkc110_power_off ;

#ifdef CONFIG_ANDROID_PMEM
	android_pmem_set_platdata();
#endif
	/* i2c */
	s3c_i2c0_set_platdata(NULL);
	s3c_i2c1_set_platdata(NULL);
	s3c_i2c2_set_platdata(NULL);

	sound_init();

	i2c_register_board_info(0, i2c_dev, ARRAY_SIZE(i2c_dev));
	i2c_register_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));
	i2c_register_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));
	i2c_register_board_info(2, i2c_devs2, ARRAY_SIZE(i2c_devs2));
	i2c_register_board_info(5, i2c_devs5, ARRAY_SIZE(i2c_devs5));

#ifdef CONFIG_DM9000
	smdkc110_dm9000_set();
#endif

#if defined(CONFIG_FB_S3C_LTE480WV)||defined(CONFIG_FB_S3C_LCD800480)||defined(CONFIG_FB_S3C_LCD800600)||defined(CONFIG_FB_S3C_VGA1024768)||defined(CONFIG_FB_S3C_LCD640480)||defined(CONFIG_FB_S3C_LCD480272)||defined(CONFIG_FB_AT070TN92) ||defined (CONFIG_FB_S3C_VGA640480)
	s3cfb_set_platdata(&lte480wv_fb_data);
#endif
#ifdef CONFIG_CW210_VGA
	s3cfb_set_platdata(&vga_fb_data);
#endif

	/* spi */
#ifdef CONFIG_S3C64XX_DEV_SPI
	if (!gpio_request(S5PV210_GPB(1), "SPI_CS0")) {
		gpio_direction_output(S5PV210_GPB(1), 1);
		s3c_gpio_cfgpin(S5PV210_GPB(1), S3C_GPIO_SFN(1));
		s3c_gpio_setpull(S5PV210_GPB(1), S3C_GPIO_PULL_UP);
		s5pv210_spi_set_info(0, S5PV210_SPI_SRCCLK_PCLK,
			ARRAY_SIZE(smdk_spi0_csi));
	}
	if (!gpio_request(S5PV210_GPB(5), "SPI_CS1")) {
		gpio_direction_output(S5PV210_GPB(5), 1);
		s3c_gpio_cfgpin(S5PV210_GPB(5), S3C_GPIO_SFN(1));
		s3c_gpio_setpull(S5PV210_GPB(5), S3C_GPIO_PULL_UP);
		s5pv210_spi_set_info(1, S5PV210_SPI_SRCCLK_PCLK,
			ARRAY_SIZE(smdk_spi1_csi));
	}
	spi_register_board_info(s3c_spi_devs, ARRAY_SIZE(s3c_spi_devs));
#endif

#if defined(CONFIG_TOUCHSCREEN_S3C)
	s3c_ts_set_platdata(&s3c_ts_platform);
#endif

#if defined(CONFIG_S5P_ADC)
	s3c_adc_set_platdata(&s3c_adc_platform);
#endif

#if defined(CONFIG_PM)
	s3c_pm_init();
#endif

#ifdef CONFIG_VIDEO_FIMC
	/* fimc */
	s3c_fimc0_set_platdata(&fimc_plat_lsi);
	s3c_fimc1_set_platdata(&fimc_plat_lsi);
	s3c_fimc2_set_platdata(&fimc_plat_lsi);
	/* external camera */
	/* smdkv210_cam0_power(1); */
	/* smdkv210_cam1_power(1); */
#endif

#ifdef CONFIG_VIDEO_FIMC_MIPI
	s3c_csis_set_platdata(NULL);
#endif

#ifdef CONFIG_VIDEO_JPEG_V2
	s3c_jpeg_set_platdata(&jpeg_plat);
#endif

#ifdef CONFIG_VIDEO_MFC50
	/* mfc */
	s3c_mfc_set_platdata(NULL);
#endif

#ifdef CONFIG_VIDEO_TV20
	s3c_set_qos();
#endif

#ifdef CONFIG_S3C_DEV_HSMMC
	s5pv210_default_sdhci0();
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
	s5pv210_default_sdhci1();
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
	s5pv210_default_sdhci2();
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
	s5pv210_default_sdhci3();
#endif
#ifdef CONFIG_S5PV210_SETUP_SDHCI
	s3c_sdhci_set_platdata();
#endif

#ifdef CONFIG_BACKLIGHT_PWM
	smdk_backlight_register();
#endif

	regulator_has_full_constraints();

	smdkc110_setup_clocks();
}

#ifdef CONFIG_USB_SUPPORT
/* Initializes OTG Phy. */
void otg_phy_init(void)
{
//	printk("otg_phy_init\n\n");
	/* USB PHY0 Enable */
	writel(readl(S5P_USB_PHY_CONTROL) | (0x1<<0),
			S5P_USB_PHY_CONTROL);
	writel((readl(S3C_USBOTG_PHYPWR) & ~(0x3<<3) & ~(0x1<<0)) | (0x1<<5),
			S3C_USBOTG_PHYPWR);
	writel((readl(S3C_USBOTG_PHYCLK) & ~(0x5<<2)) | (0x3<<0),
			S3C_USBOTG_PHYCLK);
	writel((readl(S3C_USBOTG_RSTCON) & ~(0x3<<1)) | (0x1<<0),
			S3C_USBOTG_RSTCON);
	msleep(1);
	writel(readl(S3C_USBOTG_RSTCON) & ~(0x7<<0),
			S3C_USBOTG_RSTCON);
	msleep(1);

	/* rising/falling time */
	writel(readl(S3C_USBOTG_PHYTUNE) | (0x1<<20),
			S3C_USBOTG_PHYTUNE);

	/* set DC level as 6 (6%) */
	writel((readl(S3C_USBOTG_PHYTUNE) & ~(0xf)) | (0x1<<2) | (0x1<<1),
			S3C_USBOTG_PHYTUNE);
}
EXPORT_SYMBOL(otg_phy_init);

/* USB Control request data struct must be located here for DMA transfer */
struct usb_ctrlrequest usb_ctrl __attribute__((aligned(64)));

/* OTG PHY Power Off */
void otg_phy_off(void)
{
	writel(readl(S3C_USBOTG_PHYPWR) | (0x3<<3),
			S3C_USBOTG_PHYPWR);
	writel(readl(S5P_USB_PHY_CONTROL) & ~(1<<0),
			S5P_USB_PHY_CONTROL);
}
EXPORT_SYMBOL(otg_phy_off);

void usb_host_phy_init(void)
{
	struct clk *otg_clk;
//	printk("usb_host_phy_init\n\n");

	otg_clk = clk_get(NULL, "otg");
	clk_enable(otg_clk);
//	printk("otg_clk = %d \n",clk_get_rate(otg_clk));

	if (readl(S5P_USB_PHY_CONTROL) & (0x1<<1))
		return;
		
	s3c_gpio_setpull(S5PV210_ETC2(7), S3C_GPIO_PULL_DOWN);		

	__raw_writel(__raw_readl(S5P_USB_PHY_CONTROL) | (0x1<<1),
			S5P_USB_PHY_CONTROL);
	__raw_writel((__raw_readl(S3C_USBOTG_PHYPWR)
			& ~(0x1<<7) & ~(0x1<<6)) | (0x1<<8) | (0x1<<5),
			S3C_USBOTG_PHYPWR);
	__raw_writel((__raw_readl(S3C_USBOTG_PHYCLK) & ~(0x1<<7)) | (0x3<<0),
			S3C_USBOTG_PHYCLK);
	__raw_writel((__raw_readl(S3C_USBOTG_RSTCON)) | (0x1<<4) | (0x1<<3),
			S3C_USBOTG_RSTCON);
	__raw_writel(__raw_readl(S3C_USBOTG_RSTCON) & ~(0x1<<4) & ~(0x1<<3),
			S3C_USBOTG_RSTCON);
}
EXPORT_SYMBOL(usb_host_phy_init);

void usb_host_phy_off(void)
{
	__raw_writel(__raw_readl(S3C_USBOTG_PHYPWR) | (0x1<<7)|(0x1<<6),
			S3C_USBOTG_PHYPWR);
	__raw_writel(__raw_readl(S5P_USB_PHY_CONTROL) & ~(1<<1),
			S5P_USB_PHY_CONTROL);
}
EXPORT_SYMBOL(usb_host_phy_off);
#endif

void s3c_setup_uart_cfg_gpio(unsigned char port)
{
}
EXPORT_SYMBOL(s3c_setup_uart_cfg_gpio);

#ifdef CONFIG_MACH_SMDKC110
MACHINE_START(SMDKC110, "SMDKC110")
#elif CONFIG_MACH_SMDKV210
MACHINE_START(SMDKV210, "SMDKV210")
#endif
	/* Maintainer: Kukjin Kim <kgene.kim@samsung.com> */
	.phys_io	= S3C_PA_UART & 0xfff00000,
	.io_pg_offst	= (((u32)S3C_VA_UART) >> 18) & 0xfffc,
	.boot_params	= S5P_PA_SDRAM + 0x100,
	.init_irq	= s5pv210_init_irq,
	.map_io		= smdkc110_map_io,
	.init_machine	= smdkc110_machine_init,
	.timer		= &s5p_systimer,
MACHINE_END
