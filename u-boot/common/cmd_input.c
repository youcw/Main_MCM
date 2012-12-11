#include <common.h>
#include <command.h>

#if defined(CONFIG_CONCENWIT_INPUT)
#include <tq_input.h>
#include <lcd/s5pv210_fb.h>
#ifdef CONFIG_CONCENWIT_FAT 
#ifndef SD_DW_UBOOT
#define SD_DW_UBOOT     (1<<0)
#define SD_DW_LOGO      (1<<1)
#define SD_DW_KERNEL    (1<<2)
#define SD_DW_YAFFS	(1<<3)
#define SD_DW_UBIFS	(1<<4)
#define SD_DW_ALL	(0xff)
#endif
extern char UbootStructInit(void);
extern unsigned char FAT_Init(void);
extern char sd_downloader_linux(u8 d_flag);
#endif
#ifdef KEY_DEBUG
#define dbg(x...)       printf(x)
#else
#define dbg(x...)       do { } while (0)
#endif
static void lcd_choice_menu_usage(u8 page)
{
	printf("\r\n#####	 LCD select Menu	#####\r\n");
	if(page == 0)
	{
		printf("[K1:] T43\" screen.\r\n");
		printf("[K2:] A70\" screen.\r\n");
		printf("[K3:] A104\" screen.\r\n");
		printf("[K4:] VGA1024768\" screen.\r\n");
		printf("[K5:] Page Down.\r\n");
		Lcd_printf(0,17*4,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K1:] T43\" screen.               ");
		Lcd_printf(0,17*5,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K2:] A70\" screen.               ");
		Lcd_printf(0,17*6,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K3:] A104\" screen.              ");
		Lcd_printf(0,17*7,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K4:] VGA1024768\" screen.        ");
		Lcd_printf(0,17*8,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K5:] Page Down.                 ");

	}
	else
	{
		Lcd_printf(0,17*4,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K1:] W35\" screen.               ");
		Lcd_printf(0,17*5,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K2:] VGA640480\" screen.         ");
		Lcd_printf(0,17*6,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K3:] ..............             ");
		Lcd_printf(0,17*7,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K4:] ..............             ");
		Lcd_printf(0,17*8,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K5:] Page Up.                   ");

		printf("[K1:] W35\" screen.\r\n");
		printf("[K2:] VGA640480\" screen.\r\n");
		printf("[K3:] ...................\r\n");
		printf("[K4:] ...................\r\n");
		printf("[K5:] Page UP.\r\n");

	}
	printf("[K6:] Return Parameter Menu.\r\n");
	printf("Press a key on the CW210 Board.\r\n");

	Lcd_printf(0,16*3,RGB(0,0,0xff),0,0,"======   LCD select Menu    =====");
	Lcd_printf(0,17*9,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K6:] Return Parameter Menu.     ");

}


static void param_menu_usage(void)
{
	printf("\r\n#####	  Parameter Menu	#####\r\n");

	printf("[K1:] Set Yaffs boot parameter.\r\n");
	printf("[K2:] Set UBIfs boot parameter.\r\n");
	printf("[K3:] Set parameter for Android.\r\n");
	printf("[K4:] Choice lcd type. \r\n");
	printf("[K5:] Save the parameters to Nand\r\n");
	printf("[K6:] Return main Menu.\r\n");
	printf("Press a key on the CW210 Board.\r\n");

	Lcd_printf(0,16*3,RGB(0,0,0xff),0,0,"======    Parameter Menu    =====");

	Lcd_printf(0,17*4,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K1:] Set Yaffs boot parameter.  ");
	Lcd_printf(0,17*5,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K2:] Set UBIfs boot parameter.  ");
	Lcd_printf(0,17*6,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K3:] Set parameter for Android. ");
	Lcd_printf(0,17*7,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K4:] Choice lcd type.           ");
	Lcd_printf(0,17*8,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K5:] Save the parameters to Nand");
	Lcd_printf(0,17*9,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K6:] Return main Menu.          ");

}

static void sd_download_usage(void)
{
	printf("\r\n#####     SD download mode Menu	#####\r\n");

	printf("[K1:] Download u-boot to Nand.\r\n");
	printf("[K2:] Download Kernel to Nand.\r\n");
	printf("[K3:] Download LOGO to Nand.\r\n");
	printf("[K4:] Download UBIFS to Nand.\r\n");
	printf("[K5:] Download YAFFS to Nand.\r\n");
	printf("[K6:] Return main Menu.\r\n");
	printf("Press a key on the CW210 Board.\r\n");

	Lcd_printf(0,16*3,RGB(0,0,0xff),0,0,"======SD  download mode Menu=====");

	Lcd_printf(0,17*4,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K1:] Download u-boot to Nand.   ");
	Lcd_printf(0,17*5,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K2:] Download Kernel to Nand.   ");
	Lcd_printf(0,17*6,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K3:] Download LOGO to Nand.     ");
	Lcd_printf(0,17*7,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K4:] Download UBIFS to Nand.    ");
	Lcd_printf(0,17*8,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K5:] Download YAFFS to Nand.    ");
	Lcd_printf(0,17*9,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K6:] Return main Menu.          ");
	
}
static void usb_download_usage(void)
{
	printf("\r\n#####	  USB download mode Menu	#####\r\n");

	printf("[K1:] Download u-boot to Nand.\r\n");
	printf("[K2:] Download Kernel to Nand.\r\n");
	printf("[K3:] Download LOGO to Nand.\r\n");
	printf("[K4:] Download UBIFS to Nand.\r\n");
	printf("[K5:] Download YAFFS to Nand.\r\n");
	printf("[K6:] Return main Menu.\r\n");
	printf("Press a key on the CW210 Board.\r\n");

	Lcd_printf(0,16*3,RGB(0,0,0xff),0,0,"======USB download mode Menu=====");

	Lcd_printf(0,17*4,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K1:] Download u-boot to Nand.   ");
	Lcd_printf(0,17*5,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K2:] Download Kernel to Nand.   ");
	Lcd_printf(0,17*6,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K3:] Download LOGO to Nand.     ");
	Lcd_printf(0,17*7,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K4:] Download UBIFS to Nand.    ");
	Lcd_printf(0,17*8,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K5:] Download YAFFS to Nand.    ");
	Lcd_printf(0,17*9,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K6:] Return main Menu.          ");
	
}
void main_dis_usage(char dis_type)
{
	printf("\r\n#####	 Boot for CW210 Input system Menu	#####\r\n");

	printf("[K1:] USB Downloader system.\r\n");
	printf("[K2:] SD Downloader system.\r\n");
	printf("[K3:] SD card auto update system.\r\n");
	printf("[K4:] Set the boot parameters.\r\n");
	printf("[K5:] Quit input mode! \r\n");
	printf("[K6:] Boot the system\r\n");
	printf("Press a key on the CW210 Board.\r\n");
	Lcd_printf(28*8,16*3,RGB(0,0,0),0,0,"     ");
//	concenwit_paint_table(LCD_XSIZE_TFT-26*8-4,4,26*8,16*6,0xff,NULL);

	Lcd_printf(0,16*3,RGB(0,0,0xff),0,0,"========test input========");

	Lcd_printf(0,17*4,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K1:] USB Downloader system.     ");
	Lcd_printf(0,17*5,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K2:] SD Downloader system.      ");
	Lcd_printf(0,17*6,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K3:] SD card auto update system.");
	Lcd_printf(0,17*7,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,	"[K4:] Set the boot parameters.   ");
	Lcd_printf(0,17*8,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K5:] Quit input mode!           ");
	Lcd_printf(0,17*9,RGB(0,0,0xff),RGB(0xc0,0xc0,0xc0),0,  "[K6:] Boot the system!           ");

}
static void lcd_choice_menu_shell(void)
{
	unsigned char input_exit=0;
	u8 flg=0;
	char cmd_buf[200];
	flg=0;
	lcd_choice_menu_usage(flg);
	while(!input_exit)
	{
		switch (get_button_value())
		{
			case (KEY0):
			{
				dbg("KEY1 up!\n");
				if(flg == 0){
					sprintf(cmd_buf, "setenv lcdtype X480Y272;");
				}else{
					sprintf(cmd_buf, "setenv lcdtype X320Y240;");
				}	
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);

				break;
			}
			case (KEY1):
			{
				dbg("KEY2 up!\n");
				if(flg == 0){
					sprintf(cmd_buf, "setenv lcdtype X800Y480;");
				}else{
					sprintf(cmd_buf, "setenv lcdtype X640Y480;");
				}	
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}
			case (KEY2):
			{
				dbg("KEY3 up!\n");
				sprintf(cmd_buf, "setenv lcdtype X800Y600;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}
			case (KEY3):
			{
				dbg("KEY4 up!\n");
				sprintf(cmd_buf, "setenv lcdtype X1024Y768;");
				run_command(cmd_buf, 0);
				run_command("saveenv;", 0);
				break;
			}
			case (KEY4):
			{
				dbg("KEY5 up!\n");
				flg = ++flg%2;
				lcd_choice_menu_usage(flg);
				break;
			}
			case (KEY5):
			{
				dbg("KEY6 up!\n");
				input_exit = 1;
				break;
			}
			default:break;
		}

	}
	param_menu_usage();
}
static void param_menu_shell(void)
{
	unsigned char input_exit=0;
	char ret=0;
	char cmd_buf[200];
	param_menu_usage();
	while(!input_exit)
	{
		switch (get_button_value())
		{
			case (KEY0):
			{
				dbg("KEY1 up!\n");
#ifdef CONFIG_NOT_SET_MEM
				sprintf(cmd_buf, "setenv bootargs noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/init console=ttySAC%d", SERIAL_PORT_NUM);
#else
#ifdef CONFIG_CW210_1G
				sprintf(cmd_buf, "setenv bootargs noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/init console=ttySAC0 mem=1G");
				printf("bootargs: noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/init console=ttySAC0 mem=1G\n");
#else
				sprintf(cmd_buf, "setenv bootargs noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/init console=ttySAC0 mem=512M");
				printf("bootargs: noinitrd root=/dev/mtdblock3 rootfstype=yaffs2 init=/init console=ttySAC0 mem=512M\n");
#endif /* CONFIG_CW210_1G */
#endif /* CONFIG_NOT_SET_MEM */

				run_command(cmd_buf, 0);

				break;
			}
			case (KEY1):
			{
				dbg("KEY2 up!\n");
#ifdef CONFIG_NOT_SET_MEM
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d", SERIAL_PORT_NUM);
#else
#ifdef CONFIG_CW210_1G
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=1G", SERIAL_PORT_NUM);
				printf("bootargs: noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=1G\n", SERIAL_PORT_NUM);
#else
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=512M", SERIAL_PORT_NUM);
				printf("bootargs: noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=512M\n", SERIAL_PORT_NUM);
#endif /* CONFIG_CW210_1G */
#endif /* CONFIG_NOT_SET_MEM */
				run_command(cmd_buf, 0);
				break;
			}
			case (KEY2):
			{
				dbg("KEY3 up!\n");
#ifdef CONFIG_NOT_SET_MEM
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d", SERIAL_PORT_NUM);
#else
#ifdef CONFIG_CW210_1G
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=1G", SERIAL_PORT_NUM);
				printf("bootargs: noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=1G\n", SERIAL_PORT_NUM);
#else
				sprintf(cmd_buf, "setenv bootargs noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=512M", SERIAL_PORT_NUM);
				printf("bootargs: noinitrd ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs init=/init console=ttySAC%d mem=512M\n", SERIAL_PORT_NUM);
#endif /* CONFIG_CW210_1G */
#endif /* CONFIG_NOT_SET_MEM */

				run_command(cmd_buf, 0);

				break;
			}
			case (KEY3):
			{
				dbg("KEY4 up!\n");
				lcd_choice_menu_shell();
				break;
			}
			case (KEY4):
			{
				dbg("KEY5 up!\n");
				sprintf(cmd_buf, "saveenv");
				run_command(cmd_buf, 0);
				break;
			}
			case (KEY5):
			{
				dbg("KEY6 up!\n");
				input_exit = 1;
				break;
			}
			default:break;
		}

	}
	main_dis_usage(1);

}
static void sd_download_shell(void)
{
	unsigned char input_exit=0;
	char ret=0;
	char cmd_buf[200];
	sd_download_usage();
	if (FAT_Init())
	{
		printf("Fat initialization failed!");
		concenwit_paint_table(LCD_XSIZE_TFT-26*8-4,4,0,16*6,0xff,"Fat init failed!");
		input_exit = 1;
	}

	while(!input_exit)
	{
		switch (get_button_value())
		{
			case (KEY0):
			{
				dbg("KEY1 up!\n");
				sd_downloader_linux(SD_DW_UBOOT);
				break;
			}
			case (KEY1):
			{
				dbg("KEY2 up!\n");
				sd_downloader_linux(SD_DW_KERNEL);
				break;
			}
			case (KEY2):
			{
				dbg("KEY3 up!\n");
				sd_downloader_linux(SD_DW_LOGO);
				break;
			}
			case (KEY3):
			{
				dbg("KEY4 up!\n");
				sd_downloader_linux(SD_DW_UBIFS);
				break;
			}
			case (KEY4):
			{
				dbg("KEY5 up!\n");
				sd_downloader_linux(SD_DW_YAFFS);
				break;
			}
			case (KEY5):
			{
				dbg("KEY6 up!\n");
				input_exit = 1;
				break;
			}
			default:break;
		}

	}
	main_dis_usage(1);
	
}

static void usb_download_shell(void)
{
	unsigned char input_exit=0;
	char ret=0;
	char cmd_buf[200];
	usb_download_usage();
	while(!input_exit)
	{
		switch (get_button_value())
		{
			case (KEY0):
			{
				dbg("KEY1 up!\n");
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase bios; nand write 0xc0008000 bios $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase 0x0 0x80000; nand write.jffs2 0xc0008000 0x0 $(filesize)");
#endif
				run_command(cmd_buf, 0);

				break;
			}
			case (KEY1):
			{
				dbg("KEY2 up!\n");

#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase kernel; nand write.jffs2 0xc0008000 kernel $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase 0x300000 0x400000; nand write.jffs2 0xc0008000 0x300000 $(filesize)");
#endif
				run_command(cmd_buf, 0);

				break;
			}
			case (KEY2):
			{
				dbg("KEY3 up!\n");
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase logo; nand write.jffs2 0xc0008000 logo $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0xc0008000; nand erase 0x100000 0x200000; nand write.jffs2 0xc0008000 0x100000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				break;
			}
			case (KEY3):
			{
				dbg("KEY4 up!\n");
				strcpy(cmd_buf, "dnw 0x40008000;nand erase root;ubi part root;ubi create rootfs;ubi write 0x40008000 rootfs $(filesize)");
				run_command(cmd_buf, 0);
				break;
			}
			case (KEY4):
			{
				dbg("KEY5 up!\n");
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "dnw 0x40008000; nand erase root; nand write.yaffs 0x40008000 root $(filesize)");
#else
				strcpy(cmd_buf, "dnw 0x40008000; nand erase 0x700000 0xF8D0000; nand write.yaffs 0x40008000 0x700000 $(filesize)");
#endif
				run_command(cmd_buf, 0);
				
				break;
			}
			case (KEY5):
			{
				dbg("KEY6 up!\n");
				input_exit = 1;
				break;
			}
			default:break;
		}

	}
	main_dis_usage(1);

	
}




void input_shell(void)
{	
	unsigned char input_exit=0;
	char ret=0;
	char cmd_buf[200];
	tq_button_init();
	main_dis_usage(1);
	while(!input_exit)
	{
		switch (get_button_value())
		{
			case (KEY0):
			{
				dbg("KEY1 up!\n");
				usb_download_shell();
				break;
			}
			case (KEY1):
			{
				dbg("KEY2 up!\n");
				sd_download_shell();
				break;
			}
			case (KEY2):
			{
				dbg("KEY3 up!\n");
#ifdef CONFIG_CONCENWIT_FAT 

				if (!FAT_Init())						//初始化SD卡和FAT成功
				{
					printf("SD and FAT initialize success!\n");
					ret = UbootStructInit();
					//printf("c=%d\n", c);
					switch(ret)
					{
						case 253://-3//if (c == 253)//-3				//操作系统类型为空
						{
							printf("OS Type is error,so u-boot run OS!\n");
							break;
						}
						case 254://-2//if (c == 254)//-2				//install或run的内容不对
						{
							printf("run/install info is error,so u-boot run OS!\n");
							break;
						}
						case 255://-1//if (c == 255)//-1				//缺少CONCENWIT.ini文件
						{
							printf("Without CONCENWIT.ini !\n");
							break;
						}
						case 0://0//else if (c == 0)					//配置文件内容不对,标题不对
						{
							printf("title is error, CONCENWIT.ini is bad file!\n");
							break;
						}
						case 1://1//else if (c == 1)					//获取配置文件成功
						{
							//printf("Get CONCENWIT.ini success!\n");
							break;
						}
						case 2://2//else if (c == 2)					//是run，直接运行
						{
							printf("u-boot will run OS!\n");
							break;
						}
						default:
							break;
					}
				}
#endif

				break;
			}
			case (KEY3):
			{
				dbg("KEY4 up!\n");
				param_menu_shell();
				break;
			}
			case (KEY4):
			{
				dbg("KEY5 up!\n");
				input_exit = 1;
//				run_command("menu", 0);
				break;
			}
			case (KEY5):
			{
				dbg("KEY6 up!\n");
				printf("Start Linux ...\n");
#ifdef CONFIG_MTD_DEVICE
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 kernel;bootm 0xc0008000");
#else
				strcpy(cmd_buf, "nand read.jffs2 0xc0008000 0x300000 0x400000;bootm 0xc0008000");
#endif
				run_command(cmd_buf, 0);

				break;
			}
			default:break;
		}

	}
	Lcd_printf(0,16*3,0,0,0,"                                 ");
	Lcd_printf(0,17*4,0,0,0,"                                 ");
	Lcd_printf(0,17*5,0,0,0,"                                 ");
	Lcd_printf(0,17*6,0,0,0,"                                 ");
	Lcd_printf(0,17*7,0,0,0,"                                 ");
	Lcd_printf(0,17*8,0,0,0,"                                 ");
	Lcd_printf(0,17*9,0,0,0,"                                 ");

}


int do_input(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	input_shell();
	return 0;
}

U_BOOT_CMD(
	input,	3,	0,	do_input,
	"input system, to select the items to do something",
	"\n"
	"\tinput system, to select the items to do something"
);
#endif /* CONFIG_CONCENWIT_INPUT */
