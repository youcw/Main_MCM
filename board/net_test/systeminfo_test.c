#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/vfs.h>
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

float get_cpu_freq(void)
{
        char *file = "cpuinfo";
        char *pstr  = "cpu MHz";
        float cpufreq;
        char *ptmp;

        ptmp = parse_string(file, pstr);

        cpufreq = strtod(ptmp, NULL);
        printf("cpufreq = %f\n", cpufreq);
        
        return cpufreq;
}

unsigned long get_freemem_space(void)
{
        char *file = "meminfo";
        char *pstr = "MemFree:";
        unsigned long freemem;
        char *ptmp;

        ptmp = parse_string(file, pstr);
        
        freemem = strtol(ptmp, NULL, 10);;
        printf("freemem = %ld\n", freemem);
        return freemem;
}

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

int main(int argc, char *argv[])
{
        get_cpu_freq();
        get_freemem_space();
        get_freedisk_space();
        return 0;
}

