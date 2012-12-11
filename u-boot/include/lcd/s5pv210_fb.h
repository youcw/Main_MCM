#ifndef __S5PC210FB_H__
#define __S5PC210FB_H__

#ifdef CONFIG_CONCENWIT_LCD

#define TFT240320				1
#define TFT320240				2
#define TFT480272				3//T43(天嵌4.3寸屏)
#define VGA640480				4
#define TFT800480				5//A70(群创7.0寸屏)
#define TFT800600				6//A104(友达10.4寸屏)
#define VGA1024768				7//VGA1024x768
#define DYNAMIC_CONFIG			8//动态配置LCD

#define LCD_TFT					DYNAMIC_CONFIG//TFT480272


#if(LCD_TFT == TFT240320)
#define	CONFIG_LCD_VBPD				1
#define	CONFIG_LCD_VFPD				2
#define	CONFIG_LCD_VSPW				1
#define	CONFIG_LCD_HBPD				6
#define	CONFIG_LCD_HFPD				3
#define	CONFIG_LCD_HSPW				1
#define	CONFIG_LCD_CLKVAL			2
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				240
#define LCD_YSIZE_TFT				320

#elif(LCD_TFT == TFT320240)
#define	CONFIG_LCD_VBPD				12
#define	CONFIG_LCD_VFPD				4
#define	CONFIG_LCD_VSPW				5
#define	CONFIG_LCD_HBPD				21
#define	CONFIG_LCD_HFPD				32
#define	CONFIG_LCD_HSPW				44
#define	CONFIG_LCD_CLKVAL			6
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				240
#define LCD_YSIZE_TFT				320

#elif(LCD_TFT == TFT480272)
#define	CONFIG_LCD_VBPD				2
#define	CONFIG_LCD_VFPD				2
#define	CONFIG_LCD_VSPW				10
#define	CONFIG_LCD_HBPD				2	
#define	CONFIG_LCD_HFPD				2	
#define	CONFIG_LCD_HSPW				40
#define	CONFIG_LCD_CLKVAL			7 
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				480
#define LCD_YSIZE_TFT				272

#elif(LCD_TFT == VGA640480)
#define	CONFIG_LCD_VBPD				29
#define	CONFIG_LCD_VFPD				5
#define	CONFIG_LCD_VSPW				4
#define	CONFIG_LCD_HBPD				71
#define	CONFIG_LCD_HFPD				40
#define	CONFIG_LCD_HSPW				31
#define	CONFIG_LCD_CLKVAL			1
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				640
#define LCD_YSIZE_TFT				480

#elif(LCD_TFT == TFT800480)
#define	CONFIG_LCD_VBPD				8
#define	CONFIG_LCD_VFPD				22
#define	CONFIG_LCD_VSPW				13
#define	CONFIG_LCD_HBPD				16
#define	CONFIG_LCD_HFPD				210
#define	CONFIG_LCD_HSPW				28
#define	CONFIG_LCD_CLKVAL			6
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				800
#define LCD_YSIZE_TFT				480

#elif(LCD_TFT == TFT800600)
#define	CONFIG_LCD_VBPD				4
#define	CONFIG_LCD_VFPD				2
#define	CONFIG_LCD_VSPW				2
#define	CONFIG_LCD_HBPD				27
#define	CONFIG_LCD_HFPD				14
#define	CONFIG_LCD_HSPW				8
#define	CONFIG_LCD_CLKVAL			4
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				800
#define LCD_YSIZE_TFT				600

#elif(LCD_TFT == VGA1024768)
#define	CONFIG_LCD_VBPD				5
#define	CONFIG_LCD_VFPD				3
#define	CONFIG_LCD_VSPW				3
#define	CONFIG_LCD_HBPD				27 
#define	CONFIG_LCD_HFPD				14 
#define	CONFIG_LCD_HSPW				10 
#define	CONFIG_LCD_CLKVAL			4
#define CONFIG_LCD_BPP				24//16
#define LCD_XSIZE_TFT				1024
#define LCD_YSIZE_TFT				768

#elif(LCD_TFT == DYNAMIC_CONFIG)
typedef struct __LCD_CONFIG{
	u8 lcd_vbpd;
	u8 lcd_vfpd;
	u8 lcd_vspw;
	u8 lcd_hbpd;
	u8 lcd_hfpd;
	u8 lcd_hspw;
	u8 lcd_clkval;
	u8 lcd_bpp;
	u16 lcd_xsize;
	u16 lcd_ysize;
}lcd_config_info;
typedef enum _LCD_TYPE{
	X240Y320=0,
	X320Y240,
	X480Y272,
	X640Y480,
	X800Y480,
	X800Y600,
	X1024Y768,
	VGA7213,
	VGA1280X800,
	LCD_TYPE_MAX,
}LCD_TYPE;
//#define LCD_TYPE_MAX 				8
extern lcd_config_info *curren_info;
extern const lcd_config_info tq_lcd_config_info[LCD_TYPE_MAX];
#define	CONFIG_LCD_VBPD				(curren_info->lcd_vbpd)
#define	CONFIG_LCD_VFPD				(curren_info->lcd_vfpd)
#define	CONFIG_LCD_VSPW				(curren_info->lcd_vspw)
#define	CONFIG_LCD_HBPD				(curren_info->lcd_hbpd) 
#define	CONFIG_LCD_HFPD				(curren_info->lcd_hfpd)
#define	CONFIG_LCD_HSPW				(curren_info->lcd_hspw)
#define	CONFIG_LCD_CLKVAL			(curren_info->lcd_clkval)
#define CONFIG_LCD_BPP				(24)//(curren_info->lcd_bpp)
#define LCD_XSIZE_TFT				(curren_info->lcd_xsize)
#define LCD_YSIZE_TFT				(curren_info->lcd_ysize)
#endif

#define NAND_CONTROL_ENABLE()		(NFCONT_REG |= (1 << 0))
#define NAND_DISABLE_CE()			(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()			(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()				do { while(!(NFSTAT_REG & (1 << 0))); } while(0)

#define SCR_XSIZE_TFT	 			(LCD_XSIZE_TFT)
#define SCR_YSIZE_TFT	 			(LCD_YSIZE_TFT)

#define HOZVAL_TFT				(LCD_XSIZE_TFT - 1 )
#define LINEVAL_TFT				(LCD_YSIZE_TFT - 1 )

#define LOGO_ZONE_OFFSET			0x100000
#define VIDEO_MEM_SIZE				0x300000					/*1024*768*4 = 0x180000Byte */

#define LCD_VIDEO_ADDR				0x28000000   //0x28000000

#if(CONFIG_LCD_BPP == 16)
#define RGB(r,g,b)  				(u16)(((r)&0x1f)<<11 | ((g)&0x3f)<<5 | ((b)&0x1f)<<0)
#elif(CONFIG_LCD_BPP == 24)
#define RGB(r,g,b)				(u32)((r)<<16 | (g)<<8 | (b)<<0)
#endif

#define LCD_VIDEO_BACKGROUND_ALPHA         	(0xa)

void cw210_lcd_init(void);
void concenwit_user_logo(void);
void concenwit_tq_logo(void);
void Lcd_printf(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned int st,char *fmt,...);
void concenwit_paint_Dot(int x,int y,u32 bmp);
void concenwit_paint_Progress_bar(u32 x,u32 y,u32 width,u32 length,u32 current,u32 colour);
void concenwit_Write_Progress_note(u32 x,u32 y,u32 length,u8 left, u32 colour,char *str);
void concenwit_paint_table(u32 x,u32 y,u32 width,u32 hight,u32 colour,char *info);



#endif /* CONFIG_CONCENWIT_LCD */
#endif

