#include"head.h"

int main(){

	pid_t pid ;
	char buffer[MAXBUFFER];
	int fd[2];
	if(pipe(fd)<0){
		perror("pipe error!");
		exit(1);
	}
	pid = fork();

	if(pid<0){
		perror("fork error!");
		exit(2);
	}

	if(pid==0){
//		close(fd[1]);
		printf("%s \n",buffer);
		
		read(fd[0],buffer,MAXBUFFER);
		write(fd[1],"child\n",6);
		
		exit(0);
	}

	else{
//		close(fd[0]);
		write(fd[1],"parent\n",7);
		read(fd[0],buffer,MAXBUFFER);
		printf("%s\n",buffer);
	}

	wait(NULL);
	exit(0);
		
}



/*
	this programm will be block , that is , the programm will not run
   any more , why? read in child  block, read in parent block , so the
   the parent and child all block , so the process block.   
	so can't run 


*/
