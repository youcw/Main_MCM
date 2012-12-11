#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

#define DS18B20_RESET 0x10001
#define DS18B20_REL   0x10002

int main(int argc, char *argv[])
{
        int fd;
        int data;
        unsigned char relbit;

        fd = open("/dev/ds18b20", O_RDWR);
        if (fd < 0) {
                printf("open ds18b20 failed.\n");
                exit(-1);
        }

        if (argc < 2)  {
                printf("usage:\n %s <9|10|11|12>\n", argv[0]);
                exit(-1);
        }
       
        relbit = strtoul(argv[1], NULL, 10);
        while (1) {
                ioctl(fd, DS18B20_REL, &relbit);
                read(fd, &data, sizeof(data));
                usleep(200000);
                printf("%f\n", (float)data / 100);        
        }
        close(fd);
        return 0;
}
