#include "head.h"

void itoa(int , char*);

int main(int argc , char** argv){
	char no[10];
	char title[10]="pid\0";
	memset(no,sizeof(no),'\0');
	strcpy(no,title);
	int pid = getpid();	
	itoa(pid , no+3);
	printf("%s\n",no);	
	
	int fd = open(no,O_RDONLY|O_CREAT);
	if(fd<0){
		printf("creat error\n");
		exit(0);
	}
	close(fd);
	exit(0);
}



void itoa(int number , char* address){
		int n = 0;
		int tep = number ;
		int digit[10];
		while(tep!=0){
			digit[n] = tep % 10;
			tep /= 10;
			n++;	
		}

		int k = n-1 ;
		for(int i = 0 ; i < n ; i++){
			address[i] = digit[k] + '0';
			k--;
		}
}
