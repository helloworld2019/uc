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


void show(char* targer){
	char **env = environ;
	
	while(*env){
		if(compare(targer,*env)){
			printf("%s\n",*env);
			break;
		}
		env++;
	}	
}

int main(){
	show("PWD");

	if(	chdir("/home/hale") < 0 )printf("change dir error\n");
	
	show("PWD");
	return 0 ;
}
