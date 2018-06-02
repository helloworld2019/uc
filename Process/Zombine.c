#include "head.h"


int main(){
	pid_t pid = fork();
	if(pid<0){
		perror("fork ,error");
		exit(1);
	}
	if(pid>0){
		while(1);
	}
	return 0;
}
