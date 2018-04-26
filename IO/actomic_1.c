#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argv , char** agrc){
	char buf[]="I miss you\0";
	char buf1[]="I still miss you\0";
	int fd = open ("test",O_RDWR|O_APPEND);
	int id;
	if((id=fork())==0){
		printf("I am in the child\n");
		if(write(fd,buf,strlen(buf))<0)printf("error write in child");		
		exit(0);
	}

	printf("I am in the parent\n");
	if(write(fd,buf1,strlen(buf1))<0)printf("error write in parent");	

	wait(NULL);
	exit(0);
}
/*
This is a test.
And I love you my little qiu.
I still miss youI miss you

Above is the result of the program
according to the recent result, it is correct. 

the option O_APPREND can make the operation become to atmatic.
*/
