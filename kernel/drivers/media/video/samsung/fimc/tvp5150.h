/* linux/drivers/media/video/tvp5150.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *	         http://www.samsung.com/
 *
 * Driver for TVP5150 (UXGA camera) from Samsung Electronics
 * 1/4" 2.0Mp CMOS Image Sensor SoC with an Embedded Image Processor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __TVP5150_H__
#define __TVP5150_H__

struct tvp5150_reg {
	unsigned char addr;
	unsigned char val;
};

struct tvp5150_regset_type {
	unsigned char *regset;
	int len;
};

/*
 * Macro
 */
#define REGSET_LENGTH(x)	(sizeof(x)/sizeof(tvp5150_reg))

/*
 * User defined commands
 */
/* S/W defined features for tune */
#define REG_DELAY	0xFF00	/* in ms */
#define REG_CMD		0xFFFF	/* Followed by command */

/* Following order should not be changed */
enum image_size_tvp5150 {
	/* This SoC supports upto UXGA (1600*1200) */
	QQVGA,	/* 160*120 */
	QCIF,	/* 176*144 */
	QVGA,	/* 320*240 */
	CIF,	/* 352*288 */
	VGA,	/* 640*480 */
	SVGA,	/* 800*600 */
	HD720P,	/* 1280*720 */
	SXGA,	/* 1280*1024 */
	UXGA,	/* 1600*1200 */
};

/*
 * Following values describe controls of camera
 * in user aspect and must be match with index of tvp5150_regset[]
 * These values indicates each controls and should be used
 * to control each control
 */
enum tvp5150_control {
	TVP5150_INIT,
	TVP5150_EV,
	TVP5150_AWB,
	TVP5150_MWB,
	TVP5150_EFFECT,
	TVP5150_CONTRAST,
	TVP5150_SATURATION,
	TVP5150_SHARPNESS,
};

#define TVP5150_REGSET(x)	{	\
	.regset = x,			\
	.len = sizeof(x)/sizeof(tvp5150_reg),}


/*
 * User tuned register setting values
 */
#if 1
//656
unsigned char tvp5150_init_reg[][2]={{0x03,0xaf}, {0x04,0x00}, {0x0d,0x07}, 
					{0x08,0x40}, {0x19,0x02}, {0x0f,0x0a}};
#elif 1
//601
unsigned char tvp5150_init_reg[][2]={{0x03,0xaf}, {0x04,0x00}, {0x0d,0x00}, 
						{0x08,0x40}, {0x19,0x02}, {0x0f,0x0a}};

#elif 1
static unsigned char tvp5150_init_reg[][2] = {
  {0x0a, 0xa0}, //color saturation control		//gavin 09-09-26 璁剧疆鑹查ケ鍜屽垵鍊?  {0x0c, 0xBE},//contrast control				//gavin 09-09-26 璁剧疆瀵规瘮搴﹀垵鍊?  {0x03, 0x0D},	

  {0x12, 0x00},
#if defined(CONFIG_AIP1B)
  {0x00, 0x02},		// CVBS-CH2
#else
  {0x00, 0x00},		// CVBS-CH1	
#endif			
  {0x28, 0x00},				
  {0x0F, 0x0A},		// set pin 27 = GPCL for v02.03
  {0x03, 0x6F},		// GPCL HIGH FOR ANALOG SW to CVBS, YUV output enable
  {0x15, 0x05},		// 0x05: ADI RTC mode
  {0xC8, 0x80},		// BuffThresh			set to trigger int when 1 transaction is stored
	{0xCA, 0x8C},		// IntLineNo			enable odd field, set to line 12
	{0xCE, 0x01},		// VidStandard			set 601 sampling
	{0xCF, 0x00},		// Full field enable    disable
	{0xEE, 0xE7},		// Line21 (Field 1)- CC NTSC, was 0xE7/0xC7
	{0xEF, 0xE7},		// Line21 (Field 2)- CC NTSC, was 0xE7/0xC7 
	{0xCB, 0x4E},		// Set Pixel Alignment [7:0] to 4Eh
	{0xCC, 0x00},		// Set pixel Alignment [9:8] to 0
	{0xCD, 0x00},		// Disable Host access VBI FIFO: FIFO outputs to 656 port
	{0xC9, 0x00},		// Reset FIFO
};
#elif 1
static unsigned char tvp5150_init_reg[][2] = {
  {0x03, 0x0f},	
//  {0x03, 0x0D},	
#if 0
  {0x0a, 0xa0}, //color saturation control		//gavin 09-09-26 设置色饱和初值
  {0x0c, 0xBE},//contrast control				//gavin 09-09-26 设置对比度初值
  {0x12, 0x00},
  {0x00, 0x00},		// CVBS-CH1	
		
  {0x28, 0x00},				
  {0x0F, 0x0A},		// set pin 27 = GPCL for v02.03
  {0x03, 0x6F},		// GPCL HIGH FOR ANALOG SW to CVBS, YUV output enable
  {0x15, 0x05},		// 0x05: ADI RTC mode
  {0xC8, 0x80},		// BuffThresh			set to trigger int when 1 transaction is stored
	{0xCA, 0x8C},		// IntLineNo			enable odd field, set to line 12
	{0xCE, 0x01},		// VidStandard			set 601 sampling
	{0xCF, 0x00},		// Full field enable    disable
	{0xEE, 0xE7},		// Line21 (Field 1)- CC NTSC, was 0xE7/0xC7
	{0xEF, 0xE7},		// Line21 (Field 2)- CC NTSC, was 0xE7/0xC7 
	{0xCB, 0x4E},		// Set Pixel Alignment [7:0] to 4Eh
	{0xCC, 0x00},		// Set pixel Alignment [9:8] to 0
	{0xCD, 0x00},		// Disable Host access VBI FIFO: FIFO outputs to 656 port
	{0xC9, 0x00},		// Reset FIFO
#endif
};
#endif

#define TVP5150_INIT_REGS	\
	(sizeof(tvp5150_init_reg) / sizeof(tvp5150_init_reg[0]))

/*
 * EV bias
 */


#define TVP5150_VD_IN_SRC_SEL_1      0x00 /* Video input source selection #1 */
#define TVP5150_ANAL_CHL_CTL         0x01 /* Analog channel controls */
#define TVP5150_OP_MODE_CTL          0x02 /* Operation mode controls */
#define TVP5150_MISC_CTL             0x03 /* Miscellaneous controls */
#define TVP5150_AUTOSW_MSK           0x04 /* Autoswitch mask: TVP5150A / TVP5150AM */

/* Reserved 05h */

#define TVP5150_COLOR_KIL_THSH_CTL   0x06 /* Color killer threshold control */
#define TVP5150_LUMA_PROC_CTL_1      0x07 /* Luminance processing control #1 */
#define TVP5150_LUMA_PROC_CTL_2      0x08 /* Luminance processing control #2 */
#define TVP5150_BRIGHT_CTL           0x09 /* Brightness control */
#define TVP5150_SATURATION_CTL       0x0a /* Color saturation control */
#define TVP5150_HUE_CTL              0x0b /* Hue control */
#define TVP5150_CONTRAST_CTL         0x0c /* Contrast control */
#define TVP5150_DATA_RATE_SEL        0x0d /* Outputs and data rates select */
#define TVP5150_LUMA_PROC_CTL_3      0x0e /* Luminance processing control #3 */
#define TVP5150_CONF_SHARED_PIN      0x0f /* Configuration shared pins */

/* Reserved 10h */

#define TVP5150_ACT_VD_CROP_ST_MSB   0x11 /* Active video cropping start MSB */
#define TVP5150_ACT_VD_CROP_ST_LSB   0x12 /* Active video cropping start LSB */
#define TVP5150_ACT_VD_CROP_STP_MSB  0x13 /* Active video cropping stop MSB */
#define TVP5150_ACT_VD_CROP_STP_LSB  0x14 /* Active video cropping stop LSB */
#define TVP5150_GENLOCK              0x15 /* Genlock/RTC */
#define TVP5150_HORIZ_SYNC_START     0x16 /* Horizontal sync start */

/* Reserved 17h */

#define TVP5150_VERT_BLANKING_START 0x18 /* Vertical blanking start */
#define TVP5150_VERT_BLANKING_STOP  0x19 /* Vertical blanking stop */
#define TVP5150_CHROMA_PROC_CTL_1   0x1a /* Chrominance processing control #1 */
#define TVP5150_CHROMA_PROC_CTL_2   0x1b /* Chrominance processing control #2 */
#define TVP5150_INT_RESET_REG_B     0x1c /* Interrupt reset register B */
#define TVP5150_INT_ENABLE_REG_B    0x1d /* Interrupt enable register B */
#define TVP5150_INTT_CONFIG_REG_B   0x1e /* Interrupt configuration register B */

/* Reserved 1Fh-27h */

#define TVP5150_VIDEO_STD           0x28 /* Video standard */

/* Reserved 29h-2bh */

#define TVP5150_CB_GAIN_FACT        0x2c /* Cb gain factor */
#define TVP5150_CR_GAIN_FACTOR      0x2d /* Cr gain factor */
#define TVP5150_MACROVISION_ON_CTR  0x2e /* Macrovision on counter */
#define TVP5150_MACROVISION_OFF_CTR 0x2f /* Macrovision off counter */
#define TVP5150_REV_SELECT          0x30 /* revision select (TVP5150AM1 only) */

/* Reserved	31h-7Fh */

#define TVP5150_MSB_DEV_ID          0x80 /* MSB of device ID */
#define TVP5150_LSB_DEV_ID          0x81 /* LSB of device ID */
#define TVP5150_ROM_MAJOR_VER       0x82 /* ROM major version */
#define TVP5150_ROM_MINOR_VER       0x83 /* ROM minor version */
#define TVP5150_VERT_LN_COUNT_MSB   0x84 /* Vertical line count MSB */
#define TVP5150_VERT_LN_COUNT_LSB   0x85 /* Vertical line count LSB */
#define TVP5150_INT_STATUS_REG_B    0x86 /* Interrupt status register B */
#define TVP5150_INT_ACTIVE_REG_B    0x87 /* Interrupt active register B */
#define TVP5150_STATUS_REG_1        0x88 /* Status register #1 */
#define TVP5150_STATUS_REG_2        0x89 /* Status register #2 */
#define TVP5150_STATUS_REG_3        0x8a /* Status register #3 */
#define TVP5150_STATUS_REG_4        0x8b /* Status register #4 */
#define TVP5150_STATUS_REG_5        0x8c /* Status register #5 */
/* Reserved	8Dh-8Fh */
 /* Closed caption data registers */
#define TVP5150_CC_DATA_INI         0x90
#define TVP5150_CC_DATA_END         0x93

 /* WSS data registers */
#define TVP5150_WSS_DATA_INI        0x94
#define TVP5150_WSS_DATA_END        0x99

/* VPS data registers */
#define TVP5150_VPS_DATA_INI        0x9a
#define TVP5150_VPS_DATA_END        0xa6

/* VITC data registers */
#define TVP5150_VITC_DATA_INI       0xa7
#define TVP5150_VITC_DATA_END       0xaf

#define TVP5150_VBI_FIFO_READ_DATA  0xb0 /* VBI FIFO read data */

/* Teletext filter 1 */
#define TVP5150_TELETEXT_FIL1_INI  0xb1
#define TVP5150_TELETEXT_FIL1_END  0xb5

/* Teletext filter 2 */
#define TVP5150_TELETEXT_FIL2_INI  0xb6
#define TVP5150_TELETEXT_FIL2_END  0xba

#define TVP5150_TELETEXT_FIL_ENA    0xbb /* Teletext filter enable */
/* Reserved	BCh-BFh */
#define TVP5150_INT_STATUS_REG_A    0xc0 /* Interrupt status register A */
#define TVP5150_INT_ENABLE_REG_A    0xc1 /* Interrupt enable register A */
#define TVP5150_INT_CONF            0xc2 /* Interrupt configuration */
#define TVP5150_VDP_CONF_RAM_DATA   0xc3 /* VDP configuration RAM data */
#define TVP5150_CONF_RAM_ADDR_LOW   0xc4 /* Configuration RAM address low byte */
#define TVP5150_CONF_RAM_ADDR_HIGH  0xc5 /* Configuration RAM address high byte */
#define TVP5150_VDP_STATUS_REG      0xc6 /* VDP status register */
#define TVP5150_FIFO_WORD_COUNT     0xc7 /* FIFO word count */
#define TVP5150_FIFO_INT_THRESHOLD  0xc8 /* FIFO interrupt threshold */
#define TVP5150_FIFO_RESET          0xc9 /* FIFO reset */
#define TVP5150_LINE_NUMBER_INT     0xca /* Line number interrupt */
#define TVP5150_PIX_ALIGN_REG_LOW   0xcb /* Pixel alignment register low byte */
#define TVP5150_PIX_ALIGN_REG_HIGH  0xcc /* Pixel alignment register high byte */
#define TVP5150_FIFO_OUT_CTRL       0xcd /* FIFO output control */
/* Reserved	CEh */
#define TVP5150_FULL_FIELD_ENA      0xcf /* Full field enable 1 */

/* Line mode registers */
#define TVP5150_LINE_MODE_INI       0xd0
#define TVP5150_LINE_MODE_END       0xfb

#define TVP5150_FULL_FIELD_MODE_REG 0xfc /* Full field mode register */

static const struct tvp5150_reg tvp5150_ev_m6[] = {
};

static const struct tvp5150_reg tvp5150_ev_m5[] = {
};

static const struct tvp5150_reg tvp5150_ev_m4[] = {
};

static const struct tvp5150_reg tvp5150_ev_m3[] = {
};

static const struct tvp5150_reg tvp5150_ev_m2[] = {
};

static const struct tvp5150_reg tvp5150_ev_m1[] = {
};

static const struct tvp5150_reg tvp5150_ev_default[] = {
};

static const struct tvp5150_reg tvp5150_ev_p1[] = {
};

static const struct tvp5150_reg tvp5150_ev_p2[] = {
};

static const struct tvp5150_reg tvp5150_ev_p3[] = {
};

static const struct tvp5150_reg tvp5150_ev_p4[] = {
};

static const struct tvp5150_reg tvp5150_ev_p5[] = {
};

static const struct tvp5150_reg tvp5150_ev_p6[] = {
};

/* Order of this array should be following the querymenu data */
static const unsigned char *tvp5150_regs_ev_bias[] = {
	(unsigned char *)tvp5150_ev_m6, (unsigned char *)tvp5150_ev_m5,
	(unsigned char *)tvp5150_ev_m4, (unsigned char *)tvp5150_ev_m3,
	(unsigned char *)tvp5150_ev_m2, (unsigned char *)tvp5150_ev_m1,
	(unsigned char *)tvp5150_ev_default, (unsigned char *)tvp5150_ev_p1,
	(unsigned char *)tvp5150_ev_p2, (unsigned char *)tvp5150_ev_p3,
	(unsigned char *)tvp5150_ev_p4, (unsigned char *)tvp5150_ev_p5,
	(unsigned char *)tvp5150_ev_p6,
};

/*
 * Auto White Balance configure
 */
static const struct tvp5150_reg tvp5150_awb_off[] = {
};

static const struct tvp5150_reg tvp5150_awb_on[] = {
};

static const unsigned char *tvp5150_regs_awb_enable[] = {
	(unsigned char *)tvp5150_awb_off,
	(unsigned char *)tvp5150_awb_on,
};

/*
 * Manual White Balance (presets)
 */
static const struct tvp5150_reg tvp5150_wb_tungsten[] = {

};

static const struct tvp5150_reg tvp5150_wb_fluorescent[] = {

};

static const struct tvp5150_reg tvp5150_wb_sunny[] = {

};

static const struct tvp5150_reg tvp5150_wb_cloudy[] = {

};

/* Order of this array should be following the querymenu data */
static const unsigned char *tvp5150_regs_wb_preset[] = {
	(unsigned char *)tvp5150_wb_sunny,
	(unsigned char *)tvp5150_wb_cloudy,
	(unsigned char *)tvp5150_wb_tungsten,
	(unsigned char *)tvp5150_wb_fluorescent,
};

/*
 * Color Effect (COLORFX)
 */
static const struct tvp5150_reg tvp5150_color_normal[] = {
};

static const struct tvp5150_reg tvp5150_color_monochrome[] = {
};

static const struct tvp5150_reg tvp5150_color_sepia[] = {
};

static const struct tvp5150_reg tvp5150_color_aqua[] = {
};

static const struct tvp5150_reg tvp5150_color_negative[] = {
};

static const struct tvp5150_reg tvp5150_color_sketch[] = {
};

/* Order of this array should be following the querymenu data */
static const unsigned char *tvp5150_regs_color_effect[] = {
	(unsigned char *)tvp5150_color_normal,
	(unsigned char *)tvp5150_color_monochrome,
	(unsigned char *)tvp5150_color_sepia,
	(unsigned char *)tvp5150_color_aqua,
	(unsigned char *)tvp5150_color_sketch,
	(unsigned char *)tvp5150_color_negative,
};

/*
 * Contrast bias
 */
static const struct tvp5150_reg tvp5150_contrast_m2[] = {
};

static const struct tvp5150_reg tvp5150_contrast_m1[] = {
};

static const struct tvp5150_reg tvp5150_contrast_default[] = {
};

static const struct tvp5150_reg tvp5150_contrast_p1[] = {
};

static const struct tvp5150_reg tvp5150_contrast_p2[] = {
};

static const unsigned char *tvp5150_regs_contrast_bias[] = {
	(unsigned char *)tvp5150_contrast_m2,
	(unsigned char *)tvp5150_contrast_m1,
	(unsigned char *)tvp5150_contrast_default,
	(unsigned char *)tvp5150_contrast_p1,
	(unsigned char *)tvp5150_contrast_p2,
};

/*
 * Saturation bias
 */
static const struct tvp5150_reg tvp5150_saturation_m2[] = {
};

static const struct tvp5150_reg tvp5150_saturation_m1[] = {
};

static const struct tvp5150_reg tvp5150_saturation_default[] = {
};

static const struct tvp5150_reg tvp5150_saturation_p1[] = {
};

static const struct tvp5150_reg tvp5150_saturation_p2[] = {
};

static const unsigned char *tvp5150_regs_saturation_bias[] = {
	(unsigned char *)tvp5150_saturation_m2,
	(unsigned char *)tvp5150_saturation_m1,
	(unsigned char *)tvp5150_saturation_default,
	(unsigned char *)tvp5150_saturation_p1,
	(unsigned char *)tvp5150_saturation_p2,
};

/*
 * Sharpness bias
 */
static const struct tvp5150_reg tvp5150_sharpness_m2[] = {
};

static const struct tvp5150_reg tvp5150_sharpness_m1[] = {
};

static const struct tvp5150_reg tvp5150_sharpness_default[] = {
};

static const struct tvp5150_reg tvp5150_sharpness_p1[] = {
};

static const struct tvp5150_reg tvp5150_sharpness_p2[] = {
};

static const unsigned char *tvp5150_regs_sharpness_bias[] = {
	(unsigned char *)tvp5150_sharpness_m2,
	(unsigned char *)tvp5150_sharpness_m1,
	(unsigned char *)tvp5150_sharpness_default,
	(unsigned char *)tvp5150_sharpness_p1,
	(unsigned char *)tvp5150_sharpness_p2,
};

#endif
