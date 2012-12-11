#include <common.h>
#include <command.h>

#ifdef CONFIG_CMD_MEMTEST
#define MEMSTART 0x20000000
#define MEMSEND  0x23e00000

#define MEMSTART1 0x24100000
#define MEMSEND1  0x30000000

//#define MEMSTART2 0x30000000
//#define MEMSEND2  0x40000000

#define MEMSTART2 0x40000000
#define MEMSEND2  0x50000000
//0x23e00000  uboot base
//0x24100000  uboot end
// uboot size (3*1024*1024)
#ifdef MEMTEST_DEBUG
#define dbg(x...)       printf(x)
#else
#define dbg(x...)       do { } while (0)
#endif

void memtest_shell()
{
	int i;
	int memErro=0;
	u32 data;
	u32 *Pmem;
	printf("Memory test(%xH~%xH)\"WR\",(%xH~%xH)\"WR\",(%xH~%xH)\"WR\",\n",MEMSTART,MEMSEND,MEMSTART1,MEMSEND1,MEMSTART2,MEMSEND2);
	Pmem = (u32 *) (MEMSTART);
	while((u32)Pmem<(MEMSEND))
	{
#ifdef	MEMTEST_DEBUG
		if(((u32)Pmem%0x200000) == 0)
		dbg("%xH\n",Pmem);
#endif
		*Pmem = (u32)Pmem;
		Pmem++;
	}
	printf("(%xH~%xH)write ok!\n",MEMSTART,MEMSEND);
	Pmem = (u32 *) (MEMSTART1);
	while((u32)Pmem<(MEMSEND1))
	{
#ifdef	MEMTEST_DEBUG
		if(((u32)Pmem%0x10000000) == 0)
		dbg("%xH\n",Pmem);
#endif
		*Pmem = (u32)Pmem;
		Pmem++;

	}
	printf("(%xH~%xH)write ok!\n",MEMSTART1,MEMSEND1);
	Pmem = (u32 *) (MEMSTART2);
	while((u32)Pmem<(MEMSEND2))
	{
#ifdef	MEMTEST_DEBUG
		if(((u32)Pmem%0x10000000) == 0)
		dbg("%xH\n",Pmem);
#endif
		*Pmem = (u32)Pmem;
		Pmem++;

	}
	printf("(%xH~%xH)write ok!\n",MEMSTART2,MEMSEND2);

	printf("Memory test(%xH~%xH)\"RD\",(%xH~%xH)\"RD\",(%xH~%xH)\"RD\",\n",MEMSTART,MEMSEND,MEMSTART1,MEMSEND1,MEMSTART2,MEMSEND2);
	Pmem = (u32 *) (MEMSTART);
	while((u32)Pmem<(MEMSEND))
	{
		data = *Pmem;
		if(data != (u32)Pmem)
		{
			memErro=1;
			printf("Failed memory addr :%xH,date:%xH\n",Pmem,data);		
		}
		Pmem++;
	}
	if(memErro == 0)
	{
		printf("Memory test(%xH~%xH)\"RD\"OK!\n",MEMSTART,MEMSEND);		
	}

	Pmem = (u32 *) (MEMSTART1);
	while((u32)Pmem<(MEMSEND1))
	{
		data = *Pmem;
		if(data != (u32)Pmem)
		{
			memErro=1;
			printf("Failed memory addr :%xH,date:%xH\n",Pmem,data);		
		}
		Pmem++;
	}
	if(memErro == 0)
	{
		printf("Memory test(%xH~%xH)\"RD\"OK!\n",MEMSTART1,MEMSEND1);		
	}
	Pmem = (u32 *) (MEMSTART2);
	while((u32)Pmem<(MEMSEND2))
	{
		data = *Pmem;
		if(data != (u32)Pmem)
		{
			memErro=1;
			printf("Failed memory addr :%xH,date:%xH\n",Pmem,data);		
		}
		Pmem++;
	}
	if(memErro == 0)
	{
		printf("Memory test(%xH~%xH)\"RD\"OK!\n",MEMSTART2,MEMSEND2);		
	}
	
}

int do_memtest(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char *cmd;
	u32 addr=0;
	u32 data=0;
	u32 i=0;
	dbg("argc:%d\n",argc);
	dbg("%s,%s,%s,%s\n",argv[1],argv[2],argv[3],arg[4]);
	if(argc == 1)
	{
		memtest_shell();
	}
	else
	{
		cmd = argv[1];
		if(strcmp(cmd, "read") == 0)
		{
			if(argc != 3)
			{
				printf("memtest read addr.\n");
				return 1;
			}
			addr = (u32)simple_strtoul(argv[2], NULL, 16);
			if(((addr >= MEMSTART) && (addr <= MEMSEND)) || ((addr >= MEMSTART1) && (addr <= MEMSEND1)))
			{
				printf("addr:%xH,data:%xH\n",addr,*((u32*)(addr)));
			}
		}
		else
		if(strcmp(cmd, "write") == 0)
		{
			if(argc != 4)
			{
				printf("memtest write addr data.\n");
				return 1;
			}
			addr = (u32)simple_strtoul(argv[2], NULL, 16);
			data = (u32)simple_strtoul(argv[3], NULL, 16);
			printf("writeing %xH  to %xH \n",data,addr);
			if(((addr >= MEMSTART) && (addr <= MEMSEND)) || ((addr >= MEMSTART1) && (addr <= MEMSEND1)))
			{
				*((u32*)(addr)) = data;
				printf("write %xH  to %xH succeed!\n",data,addr);
			}	
			else
			{
				printf("err:memory write\n");

			}		
		}
		else if(strcmp(cmd, "memreginfo") == 0)
		{
			*((u32 *)(0xF1400018))=*((u32 *)(0xF0000018));
			for(i = 0 ; i< 60 ; i++)
			{
				printf("DCM0:%xH--%xH\n",0xF0000000+i*4,*((u32 *)(0xF0000000+i*4)));
				printf("DCM1:%xH--%xH\n\n",0xF1400000+i*4,*((u32 *)(0xF1400000+i*4)));

			}


		}
		else{
			memtest_shell();	
		}
		
	}
	return 0;
}

U_BOOT_CMD(
	memtest,	5,	1,	do_memtest,
	"memtest tools, memory test!",
	"\n"
	"\tmemtest tools"
	"memtest read    addr.\n"
	"memtest write   addr data.\n"

);
#endif
