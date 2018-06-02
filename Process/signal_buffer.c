#include"head.h"

void handle(int sig){
	printf("handle ing \n");
	sleep(3);
	printf("finish handle\n");
}


int main(){
	signal(SIGINT,handle);
	sleep(10);
	return 0;
}
