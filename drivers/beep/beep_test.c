#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BEEP_ON		(0x10007)
#define BEEP_OFF	(0x10008)

int main(int argc, char *argv[])
{
    int fd;

    fd = open("/dev/beeps", O_RDWR);
    if (fd < 0) {
        printf("open beep error\n");
        return -1;
    }


    while (1) {
        ioctl(fd, BEEP_ON);
        sleep(1);
        ioctl(fd, BEEP_OFF);
        sleep(1);
    }
    close(fd);
    return 0;
}
