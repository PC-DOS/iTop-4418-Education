#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <poll.h>
#include <sys/prctl.h>
#include <signal.h>

//串口接收到字符z，则结束
#define EXIT_CHAR 'z'

//子进程运行的标志位，child_signal=0子进程循环通过串口发送，=1子进程结束
static int child_signal;
void handle_signal(int signo){
	if (signo == SIGHUP){                 
        printf("child recv SIGHUP..\n");
        child_signal = 1;
    }
}

//执行次数的计数器
int i;

//串口初始化函数
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

int main(int argc,char **argv)
{
	int fd,ret,nread,count=0;
	char *uart_innode;
	char *buffer = "hello world!\n";
	char buff[8];
	struct pollfd fds[1];
	child_signal = 0;
	i=0;
	
	printf("\r\n uart_write_read_test start\r\n");
	if(2 != argc){
		printf("Usage:	uart_write_read [uart port]\r\n");	
		return 1;
	}
	printf("TestDemon input char 'z',TestDemon exit!\n");
	
	uart_innode = argv[1];
	if((fd = open(uart_innode, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s is failed",uart_innode);
		return 1;
	}	
	else {
		printf("open %s is success, start sending 15 strings...\n",uart_innode);
		//串口参数配置
		set_opt(fd, 115200, 8, 'N', 1);
		fds[0].fd = fd;
		fds[0].events = POLLIN;
	}
	
	//串口发送函数，每隔1秒发送一次字符串
	write(fd,buffer, strlen(buffer));
	sleep(1);
	++i;
	if (i>=15){
		break;
	}
	
	close(fd);
	return 0;
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;
		newtio.c_cc[VTIME]  = 0;
		newtio.c_cc[VMIN] = 0;
		tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	
	//	printf("set done!\n\r");
	return 0;
}
