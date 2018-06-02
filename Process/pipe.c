#include"head.h"

int main(){
	pid_t pid ;
	char buffer[MAXBUFFER]="I love you";
	int fd[2];

	if(pipe(fd)<0){
		perror("pipe error!");
		exit(2);
	}
	
	pid = fork();
	if(pid<0){
			perror("fork error!");
			exit(1);
	}

	if(pid==0){
	 	close(fd[1]);
		memset(buffer,'\0',strlen(buffer));
		int  n = read(fd[0],buffer,MAXBUFFER);
		printf("%d byte  %s\n",n , buffer);
		exit(0);
	}
	
	else if(pid>0){
		close(fd[0]);
		write(fd[1],buffer,strlen(buffer));
	
	}
	wait(NULL);
	exit(0);
}
