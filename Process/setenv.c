#include"head.h"

extern char** environ ;






int main(){
	printf("PWD=%s\n",getenv("PWD"));
	setenv("PWD","/tmp",0); // zero will rewite the value
//	setenv("PWD","/tmp",1); non-zero will rewite the value
	printf("PWD=%s\n",getenv("PWD"));
	exit(0);
}
