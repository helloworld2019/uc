#include "head.h"

int main(int argc , char** argv){
		int fd = 3;
		char buffer[MAXBUFFER]="Miss you my baby!";
		if(fd!=dup2(1,fd))printf("duplicate error\n");
		if(write(fd,buffer,strlen(buffer))<0)printf("write error!\n");
		exit(0);
}

/*

dup2 will create a new descripter which share same table entry with 1 (standard input);




 */
