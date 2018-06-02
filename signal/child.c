#include "head.h"

void child_handle(int a){
	pid_t pid ;
	while(	(pid = waitpid(-1,NULL,0) ) >0 ){
		printf("child %d is done, and reap\n",(int)pid);
	}
	sleep(1);
}


int main(){
	signal(SIGCHLD,child_handle);
	for(int i = 0 ; i < 3 ; i++){
		pid_t pid = fork();
		if(pid==0){
			printf("Hello I am %d\n",getpid());
			sleep(1);
			exit(0);
		}
	}

	while(1){
	}	
}

