#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/poll.h>
#include <linux/device.h>

#define	REGEDITOR_WRITE	(0x10005)
#define REGEDITOR_READ	(0x10006)

static int major;
static struct class *regeditor_class;

static int regeditor_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int regeditor_close(struct inode *inode, struct file *file)
{
	return 0;
}

static int regeditor_ioctl(struct inode *inode, struct file *file, 
							unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	volatile unsigned long *p32;
	unsigned int addr;
	unsigned int data;
	unsigned int buf[2];
	
	copy_from_user(buf, (const void __user *)arg, 8);
	addr = buf[0];
	data = buf[1];
        
	p32	= (volatile unsigned long *)ioremap(addr, 4);
	
	switch(cmd) {
		case REGEDITOR_WRITE:
			{
                                writel(data, p32);
                                break;
			}
		case REGEDITOR_READ:
			{
				buf[1] = readl(p32);
				copy_to_user((void __user *)(arg + 4), &buf[1], 4);
				break;
			}
		default:
			ret = -1;
	};
	iounmap(p32);
	return ret;
}

static struct file_operations regeditor_fops = {
	.owner  	= 	THIS_MODULE,
	.open		= 	regeditor_open,
	.release 	= 	regeditor_close,
	.ioctl		=	regeditor_ioctl,	
};
static int regeditor_init(void)
{
	major	=	register_chrdev(0, "regeditor", &regeditor_fops);
	regeditor_class	= class_create(THIS_MODULE, "regeditor");
	device_create(regeditor_class, NULL, MKDEV(major, 0), NULL, "regeditor");
	
	return 0;
}

static void regeditor_exit(void)
{
	device_destroy(regeditor_class, MKDEV(major, 0));
	class_destroy(regeditor_class);
	unregister_chrdev(major, "regeditor");
}

module_init(regeditor_init);
module_exit(regeditor_exit);
MODULE_LICENSE("GPL");
































































































































