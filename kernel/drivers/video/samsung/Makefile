#
# Makefile for the s3c framebuffer driver
#

ifeq ($(CONFIG_FB_S3C),y)
obj-y							+= s3cfb.o
obj-$(CONFIG_ARCH_S5PV210)		+= s3cfb_fimd6x.o

obj-$(CONFIG_FB_S3C_LTE480WV)	+= s3cfb_lte480wv.o
obj-$(CONFIG_FB_S3C_LCD800480)	+= cw210_800*480.o
obj-$(CONFIG_FB_S3C_LCD480272)	+= cw210_480*272.o
obj-$(CONFIG_FB_S3C_LCD800600)	+= cw210_800*600.o
obj-$(CONFIG_FB_S3C_LCD640480)	+= cw210_640*480.o
obj-$(CONFIG_FB_S3C_LCD320240)	+= cw210_320*240.o
obj-$(CONFIG_FB_S3C_VGA1024768)	+= cw210_vga1024*768.o
obj-$(CONFIG_FB_S3C_LVDS)       += s3cfb_lvds.o
obj-$(CONFIG_FB_S3C_HT101HD1)   += s3cfb_ht101hd1.o
obj-$(CONFIG_FB_S3C_TL2796)     += s3cfb_tl2796.o
obj-$(CONFIG_FB_S3C_AMS701KA)	+= s3cfb_ams701ka.o
obj-$(CONFIG_FB_S3C_MDNIE)      += s3cfb_mdnie.o s3cfb_ielcd.o
obj-$(CONFIG_FB_S3C_CMC623)     += tune_cmc623.o
obj-$(CONFIG_CW210_VGA)			+= ch7026.o
endif

ifeq ($(CONFIG_FB_S3C_DEBUG),y)
EXTRA_CFLAGS					+= -DDEBUG
endif

