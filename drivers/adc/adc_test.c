#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

#define ADC_RESOL       0x10012
#define ADC_INPUT_PIN   0x10013

int main(int argc, char *argv[])
{
    int fd;
    unsigned int voltage;
    double AdcInfo;
    char  tmp[10];
    int nbit;
    int port;

    memset(tmp, 0, sizeof(tmp));
    
    if (argc != 3) {
        printf("usage:\n%s <nbit | port>\n", argv[0]);
        return -1;
    }
    
    nbit = strtoul(argv[1], NULL, 10);
    port = strtoul(argv[2], NULL, 10);

    fd = open("/dev/s5pv210_adc", O_RDWR);

    ioctl(fd, ADC_RESOL, &nbit);
    ioctl(fd, ADC_INPUT_PIN, &port);

    while (1) {
        read(fd, &voltage, sizeof(voltage));
        AdcInfo =  (float)voltage / (1 << nbit) * 3.3;
        sprintf(tmp, "%.1f", AdcInfo);
        AdcInfo = atof(tmp);
        printf("vol = %f\n", AdcInfo);
        usleep(300000);
    }

    close(fd);
    return 0;
}
