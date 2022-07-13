#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "ioctl_test.h"

#define DEVICE_FILENAME  "/dev/jiffies_int"

int main() {
	ioctl_test_info info = {0, 0, {0}};
    int dev;
    char buff = 15;
    int ret;
    int key_old = 0;
	int cnt = 0;
	float INTVAL = 0;

//	dev = open(DEVICE_FILENAME, O_RDWR | O_NDELAY);
//	dev = open(DEVICE_FILENAME, O_RDWR | O_NONBLOCK);
	dev = open(DEVICE_FILENAME, O_RDWR); //block mode
	if(dev < 0)	{
		perror("open()");
		return 1;
	}
    ret = write(dev, &buff, sizeof(buff));
	if(ret < 0)
		perror("write()");
	buff = 0;
	do {
		ret = read(dev, &buff, sizeof(buff));
		printf("ret : %d, cnt : %d\n", ret, cnt++);
		ioctl(dev, IOCTLTEST_READ, &info );
		INTVAL = ((float)info.time)/100;
  		if(ret < 0) {
  			perror("read()");
			return 1;
		}
		if(buff == 0) //sw_no : 0
			continue;
		if(buff != key_old)	{
			printf("key_no : %d, INTVAL : %.2lfsec\n", buff, INTVAL);
			write(dev, &buff, sizeof(buff));
			if(buff == 8)
				break;
			key_old = buff;
		}
	} while(1);
    close(dev);
    return 0;
}
