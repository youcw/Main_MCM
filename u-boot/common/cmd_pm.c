#include <common.h>
#include <command.h>
#include "../drivers/pm/tqpm.h"
#if defined(CONFIG_CW210_IIC_PM_CHIP)


int do_pm(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int val=0;  
//	chip_init();

	SDA_OUTP;
	SCL_OUTP;
#if 0
	
#else
	val = IIC_set_reg(0x30, 0x09); //设置VDIG1_REG	 输出1.8v
	if (val == FALSE)
	{
		printf("write tps901 register erro.\n");
		PWRHOLD_DOWN();
		goto FILED;
	}

	val = IIC_set_reg(0x33, 0x0d);	//设置VAUX2_REG	  输出3.3v
	if (val == FALSE)
	{
		printf("write tps901 register erro.\n");
		PWRHOLD_DOWN();
		goto FILED;
	}

	val = IIC_set_reg(0x3f, 0x50);	//设置DEVCTR_REG寄存器，置位SR_CTL_I2C_SEL（表明VDD1和VDD2由CRL-IIC控制）
	if (val == FALSE)
	{
		printf("write tps901 register erro.\n");
		PWRHOLD_DOWN();
		goto FILED;
	}

	val = IIC_set_reg(0x3e, 0);	//设置DCDCCTR_REG  禁止VDD2_PSKIP，VDD1_PSKIP，nosynchronizationofDCDCclocks
	if (val == FALSE)
	{
		printf("write tps901 register erro.\n");
		PWRHOLD_DOWN();
		goto FILED;
	}

	val = IIC_set_reg(0x22, 58);		 //设置VDD1_OP_REG 输出0.6v
	if (val == FALSE)
	{
		printf("write tps901 register erro.\n");
		PWRHOLD_DOWN();
		goto FILED;
	}

	val = IIC_set_reg(0x25, 54);	//设置VDD2_OP_REG  输出1.5v
	if (val == FALSE)
	{
		printf("write tps901 register erro.\n");
		PWRHOLD_DOWN();
		goto FILED;
	}
#endif
	return 0;
FILED:
	return -1;
}

U_BOOT_CMD(
	tqpm,	5,	1,	do_pm,
	"tqpm     - Embedsky board set power mangement chip test",
	"\n"
	"\tEmbedsky board set power mangement chip test"
);
#endif /* CONFIG_CONCENWIT_INPUT */
