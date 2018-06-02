#include"head.h"

int main(){
	printf("in the father\n");
	int pid =  getpid();
	int gid =  getpgrp();
	printf("the pid is %d , the gid is %d\n",pid,gid);

	if(fork()==0){
		printf("in the child\n");
		int pid =  getpid();
		int gid =  getpgrp();
		printf("the pid is %d , the gid is %d\n",pid,gid);
		gid = setpgrp();
		printf("the pid is %d , the gid is %d\n",pid,gid);
		exit(0);
	}
	exit(0);
}
