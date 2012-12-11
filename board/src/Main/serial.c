#include "common.h"

int speed_arr[] = {B115200,B38400,B19200,B9600,B4800,B2400,B1200,B300};
int bps_arr[]  = {115200,38400,19200,9600,4800,2400,1200,300};

void setBps(int fd,int bps)
{
    int i;
    int status;
    struct termios opt;
    tcgetattr(fd,&opt);
    for(i=0;i<sizeof(speed_arr)/sizeof(int);i++)
    {
        if(bps==bps_arr[i])
   	{
            tcflush(fd,TCIOFLUSH);
            cfsetispeed(&opt,speed_arr[i]);
            cfsetospeed(&opt,speed_arr[i]);
            status = tcsetattr(fd,TCSANOW,&opt);
            if(status != 0)
            {
                perror("Set Serial Bps Error");
            }
            return;
        }
        tcflush(fd,TCIOFLUSH);
    }
}

/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd     类型  int  打开的串口文件句柄*
*@param  databits 类型  int 数据位   取值 为 7 或者8*
*@param  stopbits 类型  int 停止位   取值为 1 或者2*
*@param  parity  类型  int  效验类型 取值为N,E,O,,S
*/
int setOption(int fd,int databits,int stopbits,int parity)
{
    struct termios opt;
    if(tcgetattr(fd,&opt) != 0)
    {
        perror("Get Serial Options Error");
        return(-1);
    }
    opt.c_cflag &= ~CSIZE;
    //set data bit length
    switch (databits) /*设置数据位数*/
    {
        case 7:
            opt.c_cflag |= CS7;
            break;
  	case 8:
            opt.c_cflag |= CS8;
            break;
	default:
            fprintf(stderr,"Unsupported data size!\n");
            return (-1);
    }
    //set parity bit mode
    switch (parity)
    {
        case 'n':
        case 'N':
            opt.c_cflag &= ~PARENB;		/* Clear parity enable */
            opt.c_iflag &= ~INPCK;			/* Disable parity checking */
            break;
        case 'o':
        case 'O':
            opt.c_cflag |= (PARODD|PARENB);	/* 设置为奇效验*/ 
            opt.c_iflag |= INPCK;			/* Enable parity checking */
            break;
        case 'e':
        case 'E':
            opt.c_cflag |= PARENB;     		/* Enable parity */
            opt.c_cflag &= ~PARODD;   		/* 转换为偶效验*/  
            opt.c_iflag |= INPCK;      		/* Enable parity checking */ break; case 's': case 'S':  				/*as no parity*/
            opt.c_cflag &= ~PARENB;
            opt.c_cflag &= ~CSTOPB;
            break;
	default:
            fprintf(stderr,"Unsupported parity\n");
            return (-1);
    }
    //set stop bit length
    switch (stopbits)
    {
        case 1:
            opt.c_cflag &= ~CSTOPB;
            break;
	case 2:
            opt.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr,"Unsupported stop bits\n");
        return (-1);
    }
    //set input parity option
    //if (parity != 'n')
    //{
        //opt.c_iflag |= INPCK;
    //}

    opt.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG);
    opt.c_oflag &= ~OPOST;

    //opt.c_cc[VTIME] = 150; // 15 seconds
    opt.c_cc[VMIN] = 0;

    tcflush(fd,TCIFLUSH);			//Update the options and do it NOW
    if (tcsetattr(fd,TCSANOW,&opt) != 0)
    {
        perror("Set Serial Options Error");
        return (-1);
    }
    return (0);
}
