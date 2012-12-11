#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LED1_ON		(0x10001)
#define LED1_OFF	(0x10002)
#define LED2_ON		(0x10003)
#define LED2_OFF	(0X10004)

int main(int argc, char *argv[])
{
    int fd;

    fd = open("/dev/leds", O_RDWR);
    if (fd < 0) {
        printf("open leds error\n");
        return -1;
    }


    while (1) {
        ioctl(fd, LED1_ON);
        sleep(1);
        ioctl(fd, LED1_OFF);
        sleep(1);
        ioctl(fd, LED2_ON);
        sleep(1);
        ioctl(fd, LED2_OFF);
        sleep(1);
    }
    close(fd);
    return 0;
}
