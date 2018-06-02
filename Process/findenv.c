#include"head.h"

extern char** environ;

int compare(char* find, char* target){
	int len = strlen(find);
	for(int i = 0 ; i < len ; i++){
		if(target[i]=='\0')return 0;
		if(find[i]!=target[i])return 0;
	}
	return 1;
}


int main(int argc , char** argv){
	char **env = environ;
	
	while(*env){
		if(compare(argv[1],*env)){
			printf("%s\n",*env);
			break;
		}
		env++;
	}	
	exit(0);
}
