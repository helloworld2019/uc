#include"head.h"

int main(int argc , char** argv){
	if(argc==1)exit(0);
	char* name=NULL;
	name=getenv(argv[1]);
	if(name==NULL)exit(0);
	printf("%s=%s\n",argv[1],name);
	exit(0);
}
