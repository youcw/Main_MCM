#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>

#define BEEP_ON		(0x10007)
#define BEEP_OFF	(0x10008)

static int major;
static struct class *beep_class;
static unsigned long *gpio_con;
static unsigned long *gpio_data;
static int pin;

static struct resource beep_resources[] = {
		[0] = {
			.start	=	0xE02000A0,
			.end	=	0xE02000A8 - 1,
			.flags	=	IORESOURCE_MEM,
		},
		[1] = {
			.start	=	1,
			.end	=	1,
			.flags	=	IORESOURCE_IRQ,
		},
};

static void beep_release(struct device *dev)
{
    printk("%s\n", __func__);
}

static struct platform_device beep_device = {
	.name			=	"tpad_beep",
	.num_resources	=	ARRAY_SIZE(beep_resources),
	.resource		=	beep_resources,

        .dev        = {
            .release = beep_release,
        }
};

static int beep_open(struct inode *inode, struct file *file)
{
	*gpio_con	&= ~(0xf << (pin * 4));
	*gpio_con	|= (1 << (pin * 4));
	return 0;
}

static int beep_close(struct inode *inode, struct file *file)
{
	return 0;
}

static int beep_ioctl(struct inode *inode, struct file *file, 
						unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
		case BEEP_ON:
                                *gpio_data	|= (1 << pin);
			break;
		case BEEP_OFF:
				*gpio_data	&= ~(1 << pin);
			break;
		default:
			return -1;
	};
	return 0;
}

static struct file_operations beep_fops = {
	.open		=	beep_open,
	.release	=	beep_close,
	.ioctl		=	beep_ioctl,
};

static int beep_probe(struct platform_device *dev)
{
	struct resource *res;
	
	major		=	register_chrdev(0, "beeps", &beep_fops);
	beep_class 	= 	class_create(THIS_MODULE, "beeps");
	device_create(beep_class, NULL, MKDEV(major, 0), NULL, "beeps");

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);

	gpio_con = ioremap(res->start, res->end - res->start + 1);
	gpio_data = gpio_con + 1;

	res = platform_get_resource(dev, IORESOURCE_IRQ, 0);
	pin = res->start;

        return 0;
}

static int beep_remove(struct platform_device *dev)
{
	iounmap(gpio_con);
	device_destroy(beep_class, MKDEV(major, 0));
	class_destroy(beep_class);
	unregister_chrdev(major, "beeps");
    
        return 0;
}

static struct platform_driver   beep_driver	= {
	.probe	=	beep_probe,
	.remove	=	beep_remove,
	.driver	=	{
			.name	=	"tpad_beep",
	},
};

static int beep_init(void)
{
	platform_device_register(&beep_device);
	platform_driver_register(&beep_driver);
	return 0;
}

static void beep_exit(void)
{
	platform_driver_unregister(&beep_driver);
	platform_device_unregister(&beep_device);
}

module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL");

