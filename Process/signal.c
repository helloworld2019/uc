#include"head.h"


void print(int sig){
	printf("wake up \n");
}

int main(){
	signal(SIGINT,print);
	int time ;
	time=sleep(10);
	printf("the rest time is %d",time);
	return 0 ;
}



/*
   Above code has tell us ,  sleep will no cotinue accomplish the rest work
  when it is intefferd by a singal and thr control transfer to operate the 
  handler
 */
