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
#include <linux/miscdevice.h>

#define DS18B20_RESET   (0x10009)
#define DS18B20_REL     (0x10011)

#define SKIP_ROM        0xcc
#define COVERTT         0x44
#define READ_MEM        0xbe
#define WRITE_MEM       0x4e

#define NINE_BIT           0x1f
#define TEN_BIT          0x3f
#define ELE_BIT          0x5f
#define TWL_BIT          0x7f

#define TH              100
#define TL              0

static unsigned long *gpio_con;
static unsigned long *gpio_dat;

static void gpio_cfg_out(unsigned char val)
{
        *gpio_con &= ~0xf;
        *gpio_con |= 0x1;
        if (val == 0)
                *gpio_dat &= ~0x1;
        else
                *gpio_dat |= 0x1;
}

static unsigned char gpio_cfg_in(void)
{
        *gpio_con &= ~0xf;
        return *gpio_dat&0x1;
}

/* 参看文档P16,注意写1和0的时隙要求*/
static void ds18b20_write8(unsigned char data)
{
        int i;

       for (i = 0; i < 8; i++) {
                if ((data & 0x1) == 1) {
                        gpio_cfg_out(0);
                        udelay(3);
                        gpio_cfg_out(1);
                        udelay(80);
                } else {
                        gpio_cfg_out(0);
                        udelay(80);
                        gpio_cfg_out(1);
                        udelay(3);
                }
                data >>= 1;
       }
}

/* 参看文档P16,注意读1和0的时隙要求*/
static unsigned char ds18b20_read8(void)
{
        int i;
        unsigned char bit;
        unsigned char data = 0;

        for (i = 0; i < 8; i++) {
                gpio_cfg_out(0);
                udelay(2);
                bit = gpio_cfg_in();
                data |= (bit << i);
                udelay(60);
        }
        return data;
}

/* 参看文档P15*/
static void ds18b20_reset(void)
{
        unsigned char ret;

        gpio_cfg_out(0);
        udelay(500);
        gpio_cfg_out(1);
        udelay(30);
        ret = gpio_cfg_in();
        udelay(500);
#if 0
        if (ret == 0) {
                printk("reset ok.\n");
        } else {
                printk("reset failed.\n");
        }
#endif
}

static void ds18b20_config_rel(unsigned char rel)
{
        ds18b20_reset();
        ds18b20_write8(SKIP_ROM);
        ds18b20_write8(WRITE_MEM);
        ds18b20_write8(TH);
        ds18b20_write8(TL);
        switch(rel) {
                case 9: 
                        ds18b20_write8(NINE_BIT);
                        break;
                case 10:
                        ds18b20_write8(TEN_BIT);
                        break;
                case 11:
                        ds18b20_write8(ELE_BIT);
                        break;
                case 12:
                        ds18b20_write8(TWL_BIT);
                        break;
        }
}

static int ds18b20_open(struct inode *inode, struct file *file)
{
        return 0;
}

static int ds18b20_close(struct inode *inode, struct file *file)
{
        return 0;
}

static ssize_t ds18b20_read(struct file *file, char *buf, size_t count, loff_t *pos)
{
        unsigned char h8, l8;
        int temp;

        ds18b20_reset();
        ds18b20_write8(SKIP_ROM);
        ds18b20_write8(COVERTT);

        ds18b20_reset();
        ds18b20_write8(SKIP_ROM);
        ds18b20_write8(READ_MEM);

        l8 = ds18b20_read8();
        h8 = ds18b20_read8();

        temp = (h8 << 8) | l8;
        if (temp & 0x8000) {
                temp = ~temp + 1;
        }
        temp *= 50;
        temp >>= 3;
        copy_to_user(buf, &temp, 4);
        return count;
}

static int ds18b20_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
        unsigned char rel;

        copy_from_user(&rel, (unsigned char *)arg, 1);

        switch(cmd) {
                case DS18B20_RESET:
                        ds18b20_reset();
                        break;
                case DS18B20_REL:
                        ds18b20_config_rel(rel);
                        break;
                default:
                        return -1;
        }
        return 0;
}

static struct file_operations ds18b20_fops = {
        .owner  = THIS_MODULE,
        .open   = ds18b20_open,
        .release  = ds18b20_close,
        .read    = ds18b20_read,
        .ioctl  = ds18b20_ioctl,
};

static struct miscdevice ds18b20_miscdev = {
        .minor  = MISC_DYNAMIC_MINOR,       
        .name   = "ds18b20",
        .fops   = &ds18b20_fops,
};

static int ds18b20_init(void)
{
        misc_register(&ds18b20_miscdev);

        gpio_con = ioremap(0xe0200c20, 8);
        gpio_dat = gpio_con + 1;

        return 0;
}

static void ds18b20_exit(void)
{
        iounmap(gpio_con);
        misc_deregister(&ds18b20_miscdev);
}

module_init(ds18b20_init);
module_exit(ds18b20_exit);
MODULE_LICENSE("GPL");
