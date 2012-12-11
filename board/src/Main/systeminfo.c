#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/vfs.h>
#include "msg.h"

/* 字符串解析*/
s8 *parse_string(char *file, char *string)
{
        char *pbuf;
        char *ptmp;
        char *ptmp1;
        int fd;
        int size;
        int nread;
        struct stat stat;

        if (!file || !string) return; 
        /* 打开文件*/
        fd = open(file, O_RDONLY);
        if (fd < 0) {
                printf("open %s file error!\n", file);
                return NULL;
        }
       
        /*将文件读入缓冲区中*/
        fstat(fd, &stat);
        size = stat.st_size; 
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
void get_cpu_freq(f32 *cpufreq)
{
        s8 *file = "/cpuinfo";
        s8 *pstr  = "BogoMIPS";
        s8 *ptmp;

        system("cp /proc/cpuinfo /");
        ptmp = parse_string(file, pstr);

        *cpufreq = strtod(ptmp, NULL);
}

/* 获取当前剩余内存*/
void get_freemem_space(u32 *freemem)
{
        char *file = "/meminfo";
        char *pstr = "MemFree:";
        char *ptmp;

        system("cp /proc/meminfo /");
        ptmp = parse_string(file, pstr);
        
        *freemem = strtol(ptmp, NULL, 10);;
}

/* 获取当前剩余磁盘空间*/
void get_freedisk_space(u32 *freedisk)
{
        long long free;
        long long blocks;
        struct statfs stat;
        char *dev = "/";

        statfs(dev, &stat);
        
        blocks    = stat.f_blocks;        
        free      = stat.f_bfree;
        *freedisk  = free * stat.f_bsize / (1024.00 * 1024.00);
}

