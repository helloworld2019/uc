#include"head.h"

int main(){
	printf("fd :0 %s \n",ttyname(0));
	printf("fd :1 %s \n",ttyname(1));
	printf("fd :2 %s \n",ttyname(2));
	return 0;
}


/*
	In fact , I don't know the exactly meanings of the terminal.
	I will focus on this part .
*/
