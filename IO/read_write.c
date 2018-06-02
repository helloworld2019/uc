#include "head.h"

int main(){
	int fd = open("test",O_RDWR);
	char *a = "0123456789";
	char *b = "9876543210";
	char buffer[20]={0};
	char buffer1[20]={0};
	write(fd,b,10);
	read(fd, buffer , 10);
	printf("%s",buffer);
	lseek(fd,0,SEEK_SET);	
	read(fd, buffer1 , 10);
	printf("%s",buffer1);
}
