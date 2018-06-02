#include "head.h"


void handler(int a ){
}

int mysleep(int time){
	struct sigaction action , oldaction;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags=0;

	sigaction(SIGALRM,&action,&oldaction);
	alarm(time);
	pause();
	int rest = alarm(0);
	sigaction(SIGALRM,&oldaction,NULL);
	return rest;	
}

int main(){
	int rest = -1 ;
	printf("I am about to sleep!\n");
	int resst = mysleep(5);
	if(rest!=-1){
		printf("wake up and rest time is %d",rest);
		return 0 ;
	}

	printf("wake!\n");
}
