#include"sccb.h"
#include <mach/gpio.h>
#include <mach/gpio-smdkc110.h>
#include <mach/regs-gpio.h>
#include <linux/gpio.h>
#include <linux/gpio_event.h>
#include <linux/delay.h>
#include <asm/io.h>

//#define SIO_C				S5PV210_GPG2(5)
//#define SIO_D				S5PV210_GPG2(6)
#define SIO_C		S5PV210_GPD1(3)
#define SIO_D		S5PV210_GPD1(2)

#define GPG2DAT 		0xe02001e4
#if 1
#define State(x)		gpio_get_value(x)
#define High(x)		    do{gpio_direction_output(x,1); smp_mb();}while(0)
#define Low(x)		    do{gpio_direction_output(x,0); smp_mb();}while(0)
#elif 1
#define State(x)		pin_in(x)
#define High(x)		    pin_out(x,1)
#define Low(x)		    pin_out(x,0)
#endif

#define WAIT_STABLE()	do{udelay(5);}while(0)		//
#define WAIT_CYCLE()	do{udelay(100);}while(0)		//
//#define WAIT_STABLE()	do{udelay(3);}while(0)		//
//#define WAIT_CYCLE()	do{udelay(3);}while(0)		//

#define CFG_READ(x)		do{s3c_gpio_cfgpin(x,S3C_GPIO_SFN(0));smp_mb();}while(0)
#define CFG_WRITE(x)	do{s3c_gpio_cfgpin(x,S3C_GPIO_SFN(1));smp_mb();}while(0)

int* pdat; 
inline void pin_out(unsigned int pin,int level)
{
	if(pin == SIO_D)
	{	
		if(level == 0)
			*pdat|=(1<<6);
		else
			*pdat&=~(1<<6);
	}	
	else 
	{
		if(level == 0)
			*pdat|=(1<<5);
		else
			*pdat&=~(1<<5);
	}  
}

inline int pin_in(unsigned int pin)
{
	return ((*pdat&(1<<6))==0)?0:1;
}

static void __inline__ sccb_start(void)
{
	CFG_WRITE(SIO_D);

	Low(SIO_D);
	WAIT_STABLE();
}

static void __inline__ sccb_write_byte(u8 data)
{
	int i;

	CFG_WRITE(SIO_D);
	WAIT_STABLE();

	/* write 8-bits octet. */
	for (i=0;i<8;i++)
	{
		Low(SIO_C);
		WAIT_STABLE();

		if (data & 0x80)
		{
			High(SIO_D);
		}
		else
		{
			Low(SIO_D);
		}
		data = data<<1;
		WAIT_CYCLE();
		
		High(SIO_C);
		WAIT_CYCLE();
	}
	
	/* write byte done, wait the Don't care bit now. */
	{
		Low(SIO_C);
		High(SIO_D);
		CFG_READ(SIO_D);
		WAIT_CYCLE();
		
		High(SIO_C);
		WAIT_CYCLE();
	}
}

static u8 __inline__ sccb_read_byte(void)
{
	int i;
	u8 data;

	CFG_READ(SIO_D);
	WAIT_STABLE();
	
	Low(SIO_C);
	WAIT_CYCLE();

	data = 0;
	for (i=0;i<8;i++)
	{
		High(SIO_C);
		WAIT_STABLE();
		
		data = data<<1;
		data |= State(SIO_D)?1:0;
		WAIT_CYCLE();
		
		Low(SIO_C);
		WAIT_CYCLE();
	}
	
	/* read byte down, write the NA bit now.*/
	{
		CFG_WRITE(SIO_D);
		High(SIO_D);
		WAIT_CYCLE();
		
		High(SIO_C);
		WAIT_CYCLE();
	}
	
	return data;
}

static void __inline__ sccb_stop(void)
{
	Low(SIO_C);
	WAIT_STABLE();
	
	CFG_WRITE(SIO_D);
	Low(SIO_D);
	WAIT_CYCLE();
	
	High(SIO_C);
	WAIT_STABLE();
	
	High(SIO_D);
	WAIT_CYCLE();
	
	CFG_READ(SIO_D);
}

void sccb_write(u8 IdAddr, u8 SubAddr, u8 data)
{
//	down(&bus_lock);
	sccb_start();
	sccb_write_byte(IdAddr);
	sccb_write_byte(SubAddr);
	sccb_write_byte(data);
	sccb_stop();
//	up (&bus_lock);
}

void sccb_write16(u8 IdAddr, u16 SubAddr, u8 data)
{
//	down(&bus_lock);
	sccb_start();
	sccb_write_byte(IdAddr);
	sccb_write_byte(SubAddr>>8);
	sccb_write_byte(SubAddr&0xff);	
	sccb_write_byte(data);
	sccb_stop();
//	up (&bus_lock);
}

u8 sccb_read(u8 IdAddr, u8 SubAddr)
{
	u8 data;

	CFG_WRITE(SIO_C);
	WAIT_STABLE();	
//	down(&bus_lock);
	sccb_start();
	sccb_write_byte(IdAddr);
	sccb_write_byte(SubAddr);                
	sccb_stop();

	sccb_start();
	sccb_write_byte(IdAddr|0x01);
	data = sccb_read_byte();
	sccb_stop();
//	up(&bus_lock);
	
	return data;
}
u8 sccb_read16(u8 IdAddr, u16 SubAddr)
{
	u8 data;

//	down(&bus_lock);
	sccb_start();
	sccb_write_byte(IdAddr);
	sccb_write_byte(SubAddr>>8);
	sccb_write_byte(SubAddr&0xff);	
	sccb_stop();

	sccb_start();
	sccb_write_byte(IdAddr|0x01);
	data = sccb_read_byte();
	sccb_stop();
//	up(&bus_lock);
	
	return data;
}

#if 0
int sccb_init(void)
{
	int err;

	gpio_free(SIO_C);
	gpio_free(SIO_D);

	err = gpio_request(SIO_C, "SIO_C");
	if (err) {
		printk(KERN_ERR "failed to request SIO_C \n");
		return err;
	}
	err = gpio_request(SIO_D, "SIO_D");
	if (err) {
		printk(KERN_ERR "failed to request SIC_C \n");
		goto err_d;
	}
	pdat = ioremap(GPG2DAT,4);
	CFG_WRITE(SIO_D);
	CFG_WRITE(SIO_C);
	s3c_gpio_setpull(SIO_D, S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(SIO_C, S3C_GPIO_PULL_NONE);
	High(SIO_D);
	High(SIO_C);


    return 0;
err_d:
    gpio_free(SIO_C);
    return err;
}
#elif 1
#define LEVEL5	1
#define LEVEL6	1

int sccb_init(void)
{
	int *pdri,i;
/*
	pdri = ioremap(0xE02001EC,4);
	printk("before set %08x\n",*pdri);
	*pdri &= ~((3<<(6*2))|(3<<(5*2)));
	printk("after mask %08x\n",*pdri);
	*pdri |= ((LEVEL6<<(6*2))|(LEVEL5<<(5*2)));
	printk("after set %08x\n",*pdri);

	pdri = ioremap(0xE02000C0,0xd4-0xc0+4);
	for(i=0;i<6;++i)
		printk("0x%08x--%08x\n",0xE02000C0+4*i,pdri[i]);
printk("---------------\n",*pdri);
	pdri = ioremap(0xE02001E0,0xd4-0xc0+4); 
	for(i=0;i<6;++i)
		printk("0x%08x--%08x\n", 0xE02001E0+4*i,pdri[i]);
*/	return 0;
}

#endif

