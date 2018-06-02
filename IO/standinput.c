#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MAXBUFFER 100000

int main(int argc, char** argv){	
		char buffer[MAXBUFFER];
		memset(buffer,sizeof(buffer),'\0');
		if(read(0,buffer,MAXBUFFER)<0)printf("error read");
		printf("read ok\n");
		printf("%s",buffer);
		
		exit(0);
}


/*	
	open() could specif the option which determine whether read blok
	Likely, read(device) would block
