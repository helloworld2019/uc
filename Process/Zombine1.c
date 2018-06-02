#include "head.h"

void handler1(int sig){
	pid_t pid;

	if((pid=waitpid(-1,NULL,0))<0)perror("waitpid error");
	printf("Handler reaped child %d\n",pid);
	return ;
}
int main(){
	int i , n ;
	if(signal(SIGCHLD,handler1)==SIG_ERR)perror("signal error");

	for(i = 0 ; i < 3 ; i++ ){
		if(fork()==0){
			printf("Hello from child\n");
			sleep(1);
			exit(0);
		}
	}
	int time = 10;
	while(time){
		time = sleep(time);
		printf("wake up and time rest is %d\n",time);
	}

	exit(0);
}
