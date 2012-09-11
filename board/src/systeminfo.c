#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/vfs.h>

/* 字符串解析*/
char *parse_string(char *file, char *string)
{
        char *pbuf;
        char *ptmp;
        char *ptmp1;
        int fd;
        int size;
        int nread;
        struct stat stat;

        if (!file || !string)
                return;

        /* 打开文件*/
        fd = open(file, O_RDONLY);
        if (fd < 0) {
                printf("open %s file error!\n", file);
                return NULL;
        }
        
        /*将文件读入缓冲区中*/
        fstat(fd, &stat);
        size = stat.st_size; 
        printf("size = %d\n", size);
        pbuf = malloc(size);
        if (pbuf < 0) {
                printf("malloc error!\n");
                return NULL;
        } memset(pbuf, 0, size); 

        nread = read(fd, pbuf, size);
        if (nread < 0) {
                printf("read %s file error!", file);
                return NULL;
        }

        /* 解析字符串*/
        ptmp = strstr(pbuf, string);
        ptmp += strlen(string);

        while (1) {
                if ((*ptmp == ' ') || (*ptmp == ':') || (*ptmp == '\t')) { 
                        /* nothing */
                } else {
                        ptmp1 = strchr(ptmp, '\n');
                        *ptmp1 = '\0';
                        break;
                }
                ptmp++;
        }
       
        return ptmp;
}

/* 获取cpu频率*/
float get_cpu_freq(void)
{
        char *file = "/proc/cpuinfo";
        char *pstr  = "cpu MHz";
        float cpufreq;
        char *ptmp;

        ptmp = parse_string(file, pstr);

        cpufreq = strtod(ptmp, NULL);
        printf("cpufreq = %f\n", cpufreq);
        
        return cpufreq;
}

/* 获取当前剩余内存*/
unsigned long get_freemem_space(void)
{
        char *file = "/proc/meminfo";
        char *pstr = "MemFree:";
        unsigned long freemem;
        char *ptmp;

        ptmp = parse_string(file, pstr);
        
        freemem = strtol(ptmp, NULL, 10);;
        printf("freemem = %ld\n", freemem);
        return freemem;
}

/* 获取当前剩余磁盘空间*/
unsigned long get_freedisk_space(void)
{
        long long free;
        long long blocks;
        unsigned long freedisk;
        struct statfs stat;
        char *dev = "/";

        statfs(dev, &stat);
        
        blocks    = stat.f_blocks;        
        free      = stat.f_bfree;
        freedisk  = free * stat.f_bsize / (1024.00 * 1024.00);
        printf("freedisk = %ld M\n", freedisk);
        return freedisk;
}

