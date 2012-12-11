/* linux/drivers/media/video/saa7113.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *	         http://www.samsung.com/
 *
 * Driver for saa7113 (UXGA camera) from Samsung Electronics
 * 1/4" 2.0Mp CMOS Image Sensor SoC with an Embedded Image Processor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SAA7113_H__
#define __SAA7113_H__

struct saa7113_reg {
	unsigned char addr;
	unsigned char val;
};

struct saa7113_regset_type {
	unsigned char *regset;
	int len;
};

/*
 * Macro
 */
#define REGSET_LENGTH(x)	(sizeof(x)/sizeof(saa7113_reg))

/*
 * User defined commands
 */
/* S/W defined features for tune */
#define REG_DELAY	0xFF00	/* in ms */
#define REG_CMD		0xFFFF	/* Followed by command */

/* Following order should not be changed */
enum image_size_saa7113 {
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
 * in user aspect and must be match with index of saa7113_regset[]
 * These values indicates each controls and should be used
 * to control each control
 */
enum saa7113_control {
	saa7113_INIT,
	saa7113_EV,
	saa7113_AWB,
	saa7113_MWB,
	saa7113_EFFECT,
	saa7113_CONTRAST,
	saa7113_SATURATION,
	saa7113_SHARPNESS,
};

#define saa7113_REGSET(x)	{	\
	.regset = x,			\
	.len = sizeof(x)/sizeof(saa7113_reg),}


/*
 * User tuned register setting values
 */
#if 0
unsigned char saa7113_init_reg[][2] = {
{0x01,  0x08},  
{0x02,  0xC0},  
{0x03,  0x33},  
{0x04,  0x00},  
{0x05,  0x00},  
//-------½âÂë²¿·Ö------  
{0x06,  0xEB},//default E9 ²ÉÓÃÈ±Ê¡µÄ»áµ¼ÖÂÍ¼ÐÎÍùÓÒÆ«ÒÆ  
{0x07,  0xE0},//default 0D  
{0x08,  0xB8},//9C  
{0x09,  0x01},//[PAL:01, NTSC:41]  
{0x0A,  0x80},//[PAL:80, NTSC:95]  
{0x0B,  0x47},//[PAL:47, NTSC:48]  
{0x0C,  0x42},//40/  
{0x0D,  0x01},//default 00  
{0x0E,  0x01},  
{0x0F,  0x0F},//24  
{0x10,  0x00},//00 VRLN=1  
{0x11,  0x0C},  
{0x12,  0x7B},//7B Õâ²¿·Ö¿ØÖÆRTS1-VREF(50Hz), RTS0-HREF(15.6kHz) Êä³ö  
{0x13,  0x00},//01  
{0x15,  0x00},  
{0x16,  0x00},  
{0x17,  0x00},  
//-------³£¹æ·ÖÀëÊý¾Ý²¿·Ö------  
{0x40,  0x02},  
{0x41,  0xFF},  
{0x42,  0xFF},  
{0x43,  0xFF},  
{0x44,  0xFF},  
{0x45,  0xFF},  
{0x46,  0xFF},  
{0x47,  0xFF},  
{0x48,  0xFF},  
{0x49,  0xFF},  
{0x4A,  0xFF},  
{0x4B,  0xFF},  
{0x4C,  0xFF},  
{0x4D,  0xFF},  
{0x4E,  0xFF},  
{0x4F,  0xFF},  
{0x50,  0xFF},  
{0x51,  0xFF},  
{0x52,  0xFF},  
{0x53,  0xFF},  
{0x54,  0xFF},  
{0x55,  0xFF},  
{0x56,  0xFF},  
{0x57,  0xFF},  
{0x58,  0x40},  
{0x59,  0x54},//horizontal offset for slicer   
{0x5A,  0x07},//vertical offset for slicer [PAL:07 NTSC:0A]  
{0x5B,  0x83},//83field offset and MSBs for horizontal and vertical offset  
{0x5C,  0x00},  
{0x5D,  0x00},  
{0x5E,  0x00},  
{0x00,  0x00}
}; 
#elif 1
unsigned char saa7113_init_reg[][2] = {
		{0x00, 0x00},		//ADR 0x00h		PH7113_CHIP_VERSION 00 - ID byte
		{0x01, 0x08},		//ADR 0x01h		PH7113_INCREMENT_DELAY - (1) (1) (1) (1) IDEL3 IDEL2 IDELL1 IDEL0
		{0x02, 0xc0},		//ADR 0x02h		PH7113_ANALOG_INPUT_CONTR_1 - FUSE1 FUSE0 GUDL1 GUDL0 MODE3 MODE2 MODE1 MODE0
		{0x03, 0x23},		//ADR 0x03h		PH7113_ANALOG_INPUT_CONTR_2 - (1) HLNRS VBSL WPOFF HOLDG GAFIX GAI28 GAI18
		{0x04, 0x00},		//ADR 0x04h		PH7113_ANALOG_INPUT_CONTR_3 - GAI17 GAI16 GAI15 GAI14 GAI13 GAI12 GAI11 GAI10
		{0x05, 0x00},		//ADR 0x05h		PH7113_ANALOG_INPUT_CONTR_4 - GAI27 GAI26 GAI25 GAI24 GAI23 GAI22 GAI21 GAI20
		{0x06, 0xe9},		//ADR 0x06h		PH7113_HORIZONTAL_SYNC_START - HSB7 HSB6 HSB5 HSB4 HSB3 HSB2 HSB1 HSB0
		{0x07, 0x0d},		//ADR 0x07h		PH7113_HORIZONTAL_SYNC_STOP - HSS7 HSS6 HSS5 HSS4 HSS3 HSS2 HSS1 HSS0
		{0x08, 0xB8},		//ADR 0x08h		PH7113_SYNC_CONTROL - AUFD FSEL FOET HTC1 HTC0 HPLL VNOI1 VNOI0
		{0x09, 0x01},		//ADR 0x09h		PH7113_LUMINANCE_CONTROL - BYPS PREF BPSS1 BPSS0 VBLB UPTCV APER1 APER0
		{0x0a, 0xA0},//0x80,		//ADR 0x0ah		PH7113_LUMINANCE_BRIGHTNESS - BRIG7 BRIG6 BRIG5 BRIG4 BRIG3 BRIG2 BRIG1 BRIG0
		{0x0b, 0x7f},//0x47,		//ADR 0x0bh		PH7113_LUMINANCE_CONTRAST - CONT7 CONT6 CONT5 CONT4 CONT3 CONT2 CONT1 CONT0
		{0x0c, 0x40},		//ADR 0x0ch		PH7113_CHROMA_SATURATION - SATN7 SATN6 SATN5 SATN4 SATN3 SATN2 SATN1 SATN0
		{0x0d, 0x00},		//ADR 0x0dh		PH7113_CHROMA_HUE_CONTROL - HUEC7 HUEC6 HUEC5 HUEC4 HUEC3 HUEC2 HUEC1 HUEC0
		{0x0e, 0x05},	 	//ADR 0x0eh		PH7113_CHROMA_CONTROL - CDTO CSTD2 CSTD1 CSTD0 DCCF FCTC CHBW1 CHBW0
		{0x0f, 0x24},		//ADR 0x0fh		PH7113_CHROMA_GAIN_CONTROL - ACGC CGAIN6 CGAIN5 CGAIN4 CGAIN3 CGAIN2 CGAIN1 CGAIN0
		{0x10, 0x30},		//ADR 0x10h		PH7113_FORMAT_DELAY_CONTROL - OFTS1 OFTS0 HDEL1 HDEL0 VRLN YDEL2 YDEL1 YDEL0
		{0x11, 0x1c},		//0x1c//ADR 0x11h 	PH7113_OUTPUT_CONTROL_1 - GPSW1 CM99 GPSW0 HLSEL OEYC OERT VIPB COLO
		{0x12, 0xA7},		//0xc7 ,		//ADR 0x12h		PH7113_OUTPUT_CONTROL_2 - RTSE13 RTSE12 RTSE11 RTSE10 RTSE03 RTSE02 RTSE01 RTSE00
								//RTS0 is VLINE,RTS1 is VFRAME
		{0x13, 0x81},		//0x01//ADR 0x13h		PH7113_OUTPUT_CONTROL_3 - ADLSB (1) (1) OLDSB FIDP (1) AOSL1 AOSL0
		{0x14, 0x00},		//ADR 0x14h		RESERVED 14 - (1) (1) (1) (1) (1) (1) (1) (1)
		{0x15, 0x38},		//ADR 0x15h		PH7113_V_GATE1_START - VSTA7 VSTA6 VSTA5 VSTA4 VSTA3 VSTA2 VSTA1 VSTA0
		{0x16, 0x38},		//ADR 0x16h		PH7113_V_GATE1_STOP - VSTO7 VSTO6 VSTO5 VSTO4 VSTO3 VSTO2 VSTO1 VSTO0
		{0x17, 0x03},		//ADR 0x17h		PH7113_V_GATE1_MSB - (1) (1) (1) (1) (1) (1) VSTO8 VSTA8
		{0x18, 0x00},		//ADR 0x18h
		{0x19, 0x00},		//ADR 0x19h
		{0x1a, 0x00},		//ADR 0x1ah
		{0x1b, 0x00},		//ADR 0x1bh
		{0x1c, 0x00},		//ADR 0x1ch
		{0x1d, 0x00},		//ADR 0x1dh
		{0x1e, 0x00},		//ADR 0x1eh
		{0x1f, 0x00},		//ADR 0x1fh
		{0x20, 0x00},		//ADR 0x20h
		{0x21, 0x00},		//ADR 0x21h
		{0x22, 0x00},		//ADR 0x22h
		{0x23, 0x00},		//ADR 0x23h
		{0x24, 0x00},		//ADR 0x24h
		{0x25, 0x00},		//ADR 0x25h
		{0x26, 0x00},		//ADR 0x26h
		{0x27, 0x00},		//ADR 0x27h
		{0x28, 0x00},		//ADR 0x28h
		{0x29, 0x00},		//ADR 0x29h
		{0x2a, 0x00},		//ADR 0x2ah
		{0x2b, 0x00},		//ADR 0x2bh
		{0x2c, 0x00},		//ADR 0x2ch
		{0x2d, 0x00},		//ADR 0x2dh
		{0x2e, 0x00},		//ADR 0x2eh
		{0x2f, 0x00},		//ADR 0x2fh
		{0x30, 0x00},		//ADR 0x30h
		{0x31, 0x00},		//ADR 0x31h
		{0x32, 0x00},		//ADR 0x32h
		{0x33, 0x00},		//ADR 0x33h
		{0x34, 0x00},		//ADR 0x34h
		{0x35, 0x00},		//ADR 0x35h
		{0x36, 0x00},		//ADR 0x36h
		{0x37, 0x00},		//ADR 0x37h
		{0x38, 0x00},		//ADR 0x38h
		{0x39, 0x00},		//ADR 0x39h
		{0x3a, 0x00},		//ADR 0x3ah
		{0x3b, 0x00},		//ADR 0x3bh
		{0x3c, 0x00},		//ADR 0x3ch
		{0x3d, 0x00},		//ADR 0x3dh
		{0x3e, 0x00},		//ADR 0x3eh
		{0x3f, 0x00},		//ADR 0x3fh
		{0x40, 0x02},		//ADR 0x40h
		{0x41, 0xff},		//ADR 0x41h
		{0x42, 0xff},		//ADR 0x42h
		{0x43, 0xff},		//ADR 0x43h
		{0x44, 0xff},		//ADR 0x44h
		{0x45, 0xff},		//ADR 0x45h
		{0x46, 0xff},		//ADR 0x46h
		{0x47, 0xff},		//ADR 0x47h
		{0x48, 0xff},		//ADR 0x48h
		{0x49, 0xff},		//ADR 0x49h
		{0x4a, 0xff},		//ADR 0x4ah
		{0x4b, 0xff},		//ADR 0x4bh
		{0x4c, 0xff},		//ADR 0x4ch
		{0x4d, 0xff},		//ADR 0x4dh
		{0x4e, 0xff},		//ADR 0x4eh
		{0x4f, 0xff},		//ADR 0x4fh
		{0x50, 0xff},		//ADR 0x50h
		{0x51, 0xff},		//ADR 0x51h
		{0x52, 0xff},		//ADR 0x52h
		{0x53, 0xff},		//ADR 0x53h
		{0x54, 0xff},		//ADR 0x54h
		{0x55, 0xff},		//ADR 0x55h
		{0x56, 0xff},		//ADR 0x56h
		{0x57, 0xff},		//ADR 0x57h
		{0x58, 0x00},		//ADR 0x58h
		{0x59, 0x54},		//ADR 0x59h
		{0x5a, 0x07},		//ADR 0x5ah
		{0x5b, 0x83},		//ADR 0x5bh
		{0x5c, 0x00},		//ADR 0x5ch
		{0x5d, 0x00},		//ADR 0x5dh
		{0x5e, 0x00},		//ADR 0x5eh
		{0x5f, 0x00},		//ADR 0x5fh
		{0x60, 0x00},		//ADR 0x60h
		{0x61, 0x00},		//ADR 0x61h
		{0x62, 0x00} 		//ADR 0x62h
};
#endif


#define saa7113_INIT_REGS	((sizeof(saa7113_init_reg)/sizeof(saa7113_init_reg[0])))

/*
 * EV bias
 */

static const struct saa7113_reg saa7113_ev_m6[] = {
};

static const struct saa7113_reg saa7113_ev_m5[] = {
};

static const struct saa7113_reg saa7113_ev_m4[] = {
};

static const struct saa7113_reg saa7113_ev_m3[] = {
};

static const struct saa7113_reg saa7113_ev_m2[] = {
};

static const struct saa7113_reg saa7113_ev_m1[] = {
};

static const struct saa7113_reg saa7113_ev_default[] = {
};

static const struct saa7113_reg saa7113_ev_p1[] = {
};

static const struct saa7113_reg saa7113_ev_p2[] = {
};

static const struct saa7113_reg saa7113_ev_p3[] = {
};

static const struct saa7113_reg saa7113_ev_p4[] = {
};

static const struct saa7113_reg saa7113_ev_p5[] = {
};

static const struct saa7113_reg saa7113_ev_p6[] = {
};

/* Order of this array should be following the querymenu data */
static const unsigned char *saa7113_regs_ev_bias[] = {
	(unsigned char *)saa7113_ev_m6, (unsigned char *)saa7113_ev_m5,
	(unsigned char *)saa7113_ev_m4, (unsigned char *)saa7113_ev_m3,
	(unsigned char *)saa7113_ev_m2, (unsigned char *)saa7113_ev_m1,
	(unsigned char *)saa7113_ev_default, (unsigned char *)saa7113_ev_p1,
	(unsigned char *)saa7113_ev_p2, (unsigned char *)saa7113_ev_p3,
	(unsigned char *)saa7113_ev_p4, (unsigned char *)saa7113_ev_p5,
	(unsigned char *)saa7113_ev_p6,
};

/*
 * Auto White Balance configure
 */
static const struct saa7113_reg saa7113_awb_off[] = {
};

static const struct saa7113_reg saa7113_awb_on[] = {
};

static const unsigned char *saa7113_regs_awb_enable[] = {
	(unsigned char *)saa7113_awb_off,
	(unsigned char *)saa7113_awb_on,
};

/*
 * Manual White Balance (presets)
 */
static const struct saa7113_reg saa7113_wb_tungsten[] = {

};

static const struct saa7113_reg saa7113_wb_fluorescent[] = {

};

static const struct saa7113_reg saa7113_wb_sunny[] = {

};

static const struct saa7113_reg saa7113_wb_cloudy[] = {

};

/* Order of this array should be following the querymenu data */
static const unsigned char *saa7113_regs_wb_preset[] = {
	(unsigned char *)saa7113_wb_sunny,
	(unsigned char *)saa7113_wb_cloudy,
	(unsigned char *)saa7113_wb_tungsten,
	(unsigned char *)saa7113_wb_fluorescent,
};

/*
 * Color Effect (COLORFX)
 */
static const struct saa7113_reg saa7113_color_normal[] = {
};

static const struct saa7113_reg saa7113_color_monochrome[] = {
};

static const struct saa7113_reg saa7113_color_sepia[] = {
};

static const struct saa7113_reg saa7113_color_aqua[] = {
};

static const struct saa7113_reg saa7113_color_negative[] = {
};

static const struct saa7113_reg saa7113_color_sketch[] = {
};

/* Order of this array should be following the querymenu data */
static const unsigned char *saa7113_regs_color_effect[] = {
	(unsigned char *)saa7113_color_normal,
	(unsigned char *)saa7113_color_monochrome,
	(unsigned char *)saa7113_color_sepia,
	(unsigned char *)saa7113_color_aqua,
	(unsigned char *)saa7113_color_sketch,
	(unsigned char *)saa7113_color_negative,
};

/*
 * Contrast bias
 */
static const struct saa7113_reg saa7113_contrast_m2[] = {
};

static const struct saa7113_reg saa7113_contrast_m1[] = {
};

static const struct saa7113_reg saa7113_contrast_default[] = {
};

static const struct saa7113_reg saa7113_contrast_p1[] = {
};

static const struct saa7113_reg saa7113_contrast_p2[] = {
};

static const unsigned char *saa7113_regs_contrast_bias[] = {
	(unsigned char *)saa7113_contrast_m2,
	(unsigned char *)saa7113_contrast_m1,
	(unsigned char *)saa7113_contrast_default,
	(unsigned char *)saa7113_contrast_p1,
	(unsigned char *)saa7113_contrast_p2,
};

/*
 * Saturation bias
 */
static const struct saa7113_reg saa7113_saturation_m2[] = {
};

static const struct saa7113_reg saa7113_saturation_m1[] = {
};

static const struct saa7113_reg saa7113_saturation_default[] = {
};

static const struct saa7113_reg saa7113_saturation_p1[] = {
};

static const struct saa7113_reg saa7113_saturation_p2[] = {
};

static const unsigned char *saa7113_regs_saturation_bias[] = {
	(unsigned char *)saa7113_saturation_m2,
	(unsigned char *)saa7113_saturation_m1,
	(unsigned char *)saa7113_saturation_default,
	(unsigned char *)saa7113_saturation_p1,
	(unsigned char *)saa7113_saturation_p2,
};

/*
 * Sharpness bias
 */
static const struct saa7113_reg saa7113_sharpness_m2[] = {
};

static const struct saa7113_reg saa7113_sharpness_m1[] = {
};

static const struct saa7113_reg saa7113_sharpness_default[] = {
};

static const struct saa7113_reg saa7113_sharpness_p1[] = {
};

static const struct saa7113_reg saa7113_sharpness_p2[] = {
};

static const unsigned char *saa7113_regs_sharpness_bias[] = {
	(unsigned char *)saa7113_sharpness_m2,
	(unsigned char *)saa7113_sharpness_m1,
	(unsigned char *)saa7113_sharpness_default,
	(unsigned char *)saa7113_sharpness_p1,
	(unsigned char *)saa7113_sharpness_p2,
};


#define R_00_CHIP_VERSION                             0x00
/* Video Decoder */
	/* Video Decoder - Frontend part */
#define R_01_INC_DELAY                                0x01
#define R_02_INPUT_CNTL_1                             0x02
#define R_03_INPUT_CNTL_2                             0x03
#define R_04_INPUT_CNTL_3                             0x04
#define R_05_INPUT_CNTL_4                             0x05
	/* Video Decoder - Decoder part */
#define R_06_H_SYNC_START                             0x06
#define R_07_H_SYNC_STOP                              0x07
#define R_08_SYNC_CNTL                                0x08
#define R_09_LUMA_CNTL                                0x09
#define R_0A_LUMA_BRIGHT_CNTL                         0x0a
#define R_0B_LUMA_CONTRAST_CNTL                       0x0b
#define R_0C_CHROMA_SAT_CNTL                          0x0c
#define R_0D_CHROMA_HUE_CNTL                          0x0d
#define R_0E_CHROMA_CNTL_1                            0x0e
#define R_0F_CHROMA_GAIN_CNTL                         0x0f
#define R_10_CHROMA_CNTL_2                            0x10
#define R_11_MODE_DELAY_CNTL                          0x11
#define R_12_RT_SIGNAL_CNTL                           0x12
#define R_13_RT_X_PORT_OUT_CNTL                       0x13
#define R_14_ANAL_ADC_COMPAT_CNTL                     0x14
#define R_15_VGATE_START_FID_CHG                      0x15
#define R_16_VGATE_STOP                               0x16
#define R_17_MISC_VGATE_CONF_AND_MSB                  0x17
#define R_18_RAW_DATA_GAIN_CNTL                       0x18
#define R_19_RAW_DATA_OFF_CNTL                        0x19
#define R_1A_COLOR_KILL_LVL_CNTL                      0x1a
#define R_1B_MISC_TVVCRDET                            0x1b
#define R_1C_ENHAN_COMB_CTRL1                         0x1c
#define R_1D_ENHAN_COMB_CTRL2                         0x1d
#define R_1E_STATUS_BYTE_1_VD_DEC                     0x1e
#define R_1F_STATUS_BYTE_2_VD_DEC                     0x1f

/* Component processing and interrupt masking part */
#define R_23_INPUT_CNTL_5                             0x23
#define R_24_INPUT_CNTL_6                             0x24
#define R_25_INPUT_CNTL_7                             0x25
#define R_29_COMP_DELAY                               0x29
#define R_2A_COMP_BRIGHT_CNTL                         0x2a
#define R_2B_COMP_CONTRAST_CNTL                       0x2b
#define R_2C_COMP_SAT_CNTL                            0x2c
#define R_2D_INTERRUPT_MASK_1                         0x2d
#define R_2E_INTERRUPT_MASK_2                         0x2e
#define R_2F_INTERRUPT_MASK_3                         0x2f

/* Audio clock generator part */
#define R_30_AUD_MAST_CLK_CYCLES_PER_FIELD            0x30
#define R_34_AUD_MAST_CLK_NOMINAL_INC                 0x34
#define R_38_CLK_RATIO_AMXCLK_TO_ASCLK                0x38
#define R_39_CLK_RATIO_ASCLK_TO_ALRCLK                0x39
#define R_3A_AUD_CLK_GEN_BASIC_SETUP                  0x3a

/* General purpose VBI data slicer part */
#define R_40_SLICER_CNTL_1                            0x40
#define R_41_LCR_BASE                                 0x41
#define R_58_PROGRAM_FRAMING_CODE                     0x58
#define R_59_H_OFF_FOR_SLICER                         0x59
#define R_5A_V_OFF_FOR_SLICER                         0x5a
#define R_5B_FLD_OFF_AND_MSB_FOR_H_AND_V_OFF          0x5b
#define R_5D_DID                                      0x5d
#define R_5E_SDID                                     0x5e
#define R_60_SLICER_STATUS_BYTE_0                     0x60
#define R_61_SLICER_STATUS_BYTE_1                     0x61
#define R_62_SLICER_STATUS_BYTE_2                     0x62

/* X port, I port and the scaler part */
	/* Task independent global settings */
#define R_80_GLOBAL_CNTL_1                            0x80
#define R_81_V_SYNC_FLD_ID_SRC_SEL_AND_RETIMED_V_F    0x81
#define R_83_X_PORT_I_O_ENA_AND_OUT_CLK               0x83
#define R_84_I_PORT_SIGNAL_DEF                        0x84
#define R_85_I_PORT_SIGNAL_POLAR                      0x85
#define R_86_I_PORT_FIFO_FLAG_CNTL_AND_ARBIT          0x86
#define R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED         0x87
#define R_88_POWER_SAVE_ADC_PORT_CNTL                 0x88
#define R_8F_STATUS_INFO_SCALER                       0x8f
	/* Task A definition */
		/* Basic settings and acquisition window definition */
#define R_90_A_TASK_HANDLING_CNTL                     0x90
#define R_91_A_X_PORT_FORMATS_AND_CONF                0x91
#define R_92_A_X_PORT_INPUT_REFERENCE_SIGNAL          0x92
#define R_93_A_I_PORT_OUTPUT_FORMATS_AND_CONF         0x93
#define R_94_A_HORIZ_INPUT_WINDOW_START               0x94
#define R_95_A_HORIZ_INPUT_WINDOW_START_MSB           0x95
#define R_96_A_HORIZ_INPUT_WINDOW_LENGTH              0x96
#define R_97_A_HORIZ_INPUT_WINDOW_LENGTH_MSB          0x97
#define R_98_A_VERT_INPUT_WINDOW_START                0x98
#define R_99_A_VERT_INPUT_WINDOW_START_MSB            0x99
#define R_9A_A_VERT_INPUT_WINDOW_LENGTH               0x9a
#define R_9B_A_VERT_INPUT_WINDOW_LENGTH_MSB           0x9b
#define R_9C_A_HORIZ_OUTPUT_WINDOW_LENGTH             0x9c
#define R_9D_A_HORIZ_OUTPUT_WINDOW_LENGTH_MSB         0x9d
#define R_9E_A_VERT_OUTPUT_WINDOW_LENGTH              0x9e
#define R_9F_A_VERT_OUTPUT_WINDOW_LENGTH_MSB          0x9f
		/* FIR filtering and prescaling */
#define R_A0_A_HORIZ_PRESCALING                       0xa0
#define R_A1_A_ACCUMULATION_LENGTH                    0xa1
#define R_A2_A_PRESCALER_DC_GAIN_AND_FIR_PREFILTER    0xa2
#define R_A4_A_LUMA_BRIGHTNESS_CNTL                   0xa4
#define R_A5_A_LUMA_CONTRAST_CNTL                     0xa5
#define R_A6_A_CHROMA_SATURATION_CNTL                 0xa6
		/* Horizontal phase scaling */
#define R_A8_A_HORIZ_LUMA_SCALING_INC                 0xa8
#define R_A9_A_HORIZ_LUMA_SCALING_INC_MSB             0xa9
#define R_AA_A_HORIZ_LUMA_PHASE_OFF                   0xaa
#define R_AC_A_HORIZ_CHROMA_SCALING_INC               0xac
#define R_AD_A_HORIZ_CHROMA_SCALING_INC_MSB           0xad
#define R_AE_A_HORIZ_CHROMA_PHASE_OFF                 0xae
#define R_AF_A_HORIZ_CHROMA_PHASE_OFF_MSB             0xaf
		/* Vertical scaling */
#define R_B0_A_VERT_LUMA_SCALING_INC                  0xb0
#define R_B1_A_VERT_LUMA_SCALING_INC_MSB              0xb1
#define R_B2_A_VERT_CHROMA_SCALING_INC                0xb2
#define R_B3_A_VERT_CHROMA_SCALING_INC_MSB            0xb3
#define R_B4_A_VERT_SCALING_MODE_CNTL                 0xb4
#define R_B8_A_VERT_CHROMA_PHASE_OFF_00               0xb8
#define R_B9_A_VERT_CHROMA_PHASE_OFF_01               0xb9
#define R_BA_A_VERT_CHROMA_PHASE_OFF_10               0xba
#define R_BB_A_VERT_CHROMA_PHASE_OFF_11               0xbb
#define R_BC_A_VERT_LUMA_PHASE_OFF_00                 0xbc
#define R_BD_A_VERT_LUMA_PHASE_OFF_01                 0xbd
#define R_BE_A_VERT_LUMA_PHASE_OFF_10                 0xbe
#define R_BF_A_VERT_LUMA_PHASE_OFF_11                 0xbf
	/* Task B definition */
		/* Basic settings and acquisition window definition */
#define R_C0_B_TASK_HANDLING_CNTL                     0xc0
#define R_C1_B_X_PORT_FORMATS_AND_CONF                0xc1
#define R_C2_B_INPUT_REFERENCE_SIGNAL_DEFINITION      0xc2
#define R_C3_B_I_PORT_FORMATS_AND_CONF                0xc3
#define R_C4_B_HORIZ_INPUT_WINDOW_START               0xc4
#define R_C5_B_HORIZ_INPUT_WINDOW_START_MSB           0xc5
#define R_C6_B_HORIZ_INPUT_WINDOW_LENGTH              0xc6
#define R_C7_B_HORIZ_INPUT_WINDOW_LENGTH_MSB          0xc7
#define R_C8_B_VERT_INPUT_WINDOW_START                0xc8
#define R_C9_B_VERT_INPUT_WINDOW_START_MSB            0xc9


#endif
