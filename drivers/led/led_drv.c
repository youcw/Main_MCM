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

#define LED1_ON		(0x10001)
#define LED1_OFF	(0x10002)
#define LED2_ON		(0x10003)
#define LED2_OFF	(0X10004)

static int major;
static struct class *led_class;
static unsigned long *gpio_con;
static unsigned long *gpio_data;
static int pin1, pin2;

static struct resource led_resources[] = {
		[0] = {
			.start	=	0xE0200080,
			.end	=	0xE0200094 - 1,
			.flags	=	IORESOURCE_MEM,
		},
		[1] = {
			.start	=	3,
			.end	=	3,
			.flags	=	IORESOURCE_IRQ,
		},
		[2] = {
			.start	=	4,
			.end	=	4,
			.flags	=	IORESOURCE_IRQ,
		}
};

static void led_release(struct device *dev)
{
    printk("%s\n", __func__);
}

static struct platform_device led_device = {
	.name			=	"tpad_leds",
	.num_resources	=	ARRAY_SIZE(led_resources),
	.resource		=	led_resources,
        .dev                    = {
            .release    = led_release,
        }
};

static int led_open(struct inode *inode, struct file *file)
{
	*gpio_con	&= ~((0xf << (pin1 * 4)) | (0xf << (pin2 * 4)));
	*gpio_con	|= (1 << (pin1 * 4)) | (1 << (pin2 * 4));
	return 0;
}

static int led_close(struct inode *inode, struct file *file)
{
	return 0;
}

static int led_ioctl(struct inode *inode, struct file *file, 
						unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
		case LED1_ON:
				*gpio_data	|= (1 << pin1);
			break;
		case LED1_OFF:
				*gpio_data	&= ~(1 << pin1);
			break;
		case LED2_ON:
				*gpio_data	|= (1 << pin2);
			break;
		case LED2_OFF:
				*gpio_data	&= ~(1 << pin2);
			break;
		default:
			return -1;
	};
	return 0;
}

static struct file_operations led_fops = {
	.open		=	led_open,
	.release	=	led_close,
	.ioctl		=	led_ioctl,
};
static int led_probe(struct platform_device *dev)
{
	struct resource *res;
	
	major		=	register_chrdev(0, "leds", &led_fops);
	led_class 	= 	class_create(THIS_MODULE, "leds");
	device_create(led_class, NULL, MKDEV(major, 0), NULL, "leds");

	res	= platform_get_resource(dev, IORESOURCE_MEM, 0);

	gpio_con = ioremap(res->start, res->end - res->start + 1);
	gpio_data = gpio_con + 1;

	res = platform_get_resource(dev, IORESOURCE_IRQ, 0);
	pin1 = res->start;

	res	= platform_get_resource(dev, IORESOURCE_IRQ, 1);
	pin2 = res->start;

        return 0;
}

static int led_remove(struct platform_device *dev)
{
	iounmap(gpio_con);
	device_destroy(led_class, MKDEV(major, 0));
	class_destroy(led_class);
	unregister_chrdev(major, "leds");
    
        return 0;
}

static struct platform_driver	led_driver	= {
	.probe	=	led_probe,
	.remove	=	led_remove,
	.driver	=	{
			.name	=	"tpad_leds",
	},
};

static int led_init(void)
{
	platform_device_register(&led_device);
	platform_driver_register(&led_driver);
	return 0;
}

static void led_exit(void)
{
	platform_driver_unregister(&led_driver);
	platform_device_unregister(&led_device);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");

