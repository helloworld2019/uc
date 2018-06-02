#include "head.h"

int main(void){
	pid_t pid ;
	pid = fork();
	if(pid<0){
		perror("fork error!");
		exit(1);
	}
	if(pid==0){
		int i ;
		for(i = 3 ; i >= 0 ; i--){
			printf("This is the child!\n");
			sleep(1);
		}
		abort();
	}

	else {
		int stat_val;
		waitpid(pid,&stat_val,0);
		if(WIFEXITED(stat_val))printf("child exited with code %d \n",WEXITSTATUS(stat_val));
		else if(WIFSIGNALED(stat_val))printf("child terminated abnormally, signal %d\n",WTERMSIG(stat_val));
		return 0;
	}
}
