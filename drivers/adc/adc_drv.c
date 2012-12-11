#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <mach/hardware.h>
#include <asm/uaccess.h>


#define ADC_REL	        (0x10012)
#define ADC_INPUT_PIN	(0x10013)

struct s5pv210_adc_regs {
	unsigned long tsadccon0;
	unsigned long tscon0;
	unsigned long tsdly0;
	unsigned long tsdatx0;
	unsigned long tstaty0;
	unsigned long tspenstat0;
	unsigned long clrintadc0;
	unsigned long adcmux;
	unsigned long clrintpen0;
        unsigned long tsadccon1;
        unsigned long tscon1;
        unsigned long tsdly1;
        unsigned long tsdatx1;
        unsigned long tsdaty1;
        unsigned long tspenstat1;
        unsigned long clrintadc1;
        unsigned long clrintpen1;
};

static struct s5pv210_adc_regs *adc_regs;
static int port;
static int nbit;
static int EndConvered;

static DECLARE_WAIT_QUEUE_HEAD(adc_waitq);

static int s5pv210_adc_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int s5pv210_adc_close(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t s5pv210_adc_read(struct file *file, char __user *buf, size_t count, loff_t *ffops)
{
	unsigned long data;

	adc_regs->tsadccon0 |= (1 << 0);

	udelay(500);

	wait_event_interruptible(adc_waitq, EndConvered);
	EndConvered = 0;
	
	if(nbit == 12)
		data = adc_regs->tsdatx0 & 0xfff;
	else
		data = adc_regs->tsdatx0 & 0x3ff;

	copy_to_user(buf, &data, sizeof(data));

	return count;
}

static int s5pv210_adc_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
        switch(cmd) {
                case ADC_INPUT_PIN:
                        copy_from_user(&port, (int *)arg, 4);
                        adc_regs->adcmux &= ~0xf;
                        adc_regs->adcmux |= port;
                        break;
                case ADC_REL:
                        copy_from_user(&nbit, (int *)arg, 4);
                        if(nbit == 12)
                                adc_regs->tsadccon0 |= (1 << 16);
                        else
                                adc_regs->tsadccon0 &= ~(1 << 16);
                        break;
        }
        return 0;
}

static struct file_operations s5pv210_adc_fops = {
	.open 				= s5pv210_adc_open,
	.release  			= s5pv210_adc_close,
	.read				= s5pv210_adc_read,
	.ioctl		= s5pv210_adc_ioctl,
};

static irqreturn_t adc_irq(int irq, void *dev_id)
{
	EndConvered = 1;
	wake_up_interruptible(&adc_waitq);
	
	adc_regs->clrintadc0 = 0;
	return IRQ_HANDLED;
}

static struct miscdevice s5pv210_adc_drv = {
	.minor 	= 132,
	.name	= "adc",
	.fops	= &s5pv210_adc_fops,
};
static int adc_drv_init(void)
{
	struct clk *clk;
	
   	misc_register(&s5pv210_adc_drv);

	clk = clk_get(NULL, "adc");
	clk_enable(clk);

	adc_regs = ioremap(0xe1700000, sizeof(struct s5pv210_adc_regs));

	/* ADCCON[16] = 1 (12bit)*/
	/* ADCCON[14] = 1 (enable prescaler)*/
	/* ADCCON[13:6] = 13 (prescaler value)*/
	adc_regs->tsadccon0 	= (1 << 16) | (1 << 14) | (13 << 6);
	adc_regs->tsdly0	= 10000;

	request_irq(IRQ_ADC, adc_irq, 0, "adc_irq", NULL);
	
	return 0;
}

static void adc_drv_exit(void)
{
        free_irq(IRQ_ADC, NULL);
	misc_deregister(&s5pv210_adc_drv);
}

module_init(adc_drv_init);
module_exit(adc_drv_exit);
MODULE_LICENSE("GPL");
