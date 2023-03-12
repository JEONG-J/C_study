#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 1024

int main(){
	int fd;
	char *str_hello = "hello my name is jeong eui chan";
	char buff[BUFF_SIZE];

	printf("Device driver test");
	if((fd = open("/de/virtual_buffer", O_RDWR))>0){
		write(fd, str_hello, strlen(str_hello)+1);
		read(fd, buff, BUFF_SIZE);
		printf("read from device: %s\n", buff);
		close(fd);
	}
		return 0;
}