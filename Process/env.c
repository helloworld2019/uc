#include"head.h"

extern char** environ;

int main(){
	char** env = environ;
	int i = 0;
	while(*env){
		printf("%s",*(env++));
		printf("\n");
	}

	return 0;
}
