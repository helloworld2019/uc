#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(int argc , char **argv)
{
	
		int fd = 1 ;
		char buf[]="I love you Qiu\0";
		int fd1=dup(fd);
		if(write(fd1,buf,strlen(buf))<0)printf("write error");
		close(fd1);		
		exit(0);
}
