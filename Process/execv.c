#include"head.h"

int main(int argc , char** argv){
	char* env[]={"Love=care","Fridenship=understan",NULL};	
	execve("./showenv",argv,env);
	exit(0);	
}
