#include "head.h"


int main(){
	pid_t pid ;
	char* message;
	int n ;
	pid=fork();

	if(pid<0){
		perror("fork failed");
		exit(1);
	}
	if(pid==0){
		message = "This is the child\n";
		n = 6 ;
	}
	else{
		message = "This is the parent\n";
		n = 3 ;
	}
	for(;n>0;n--){
		printf(message);
		sleep(1);
	}

	exit(0);
}



/*

	this is a  very interesting and signifianct example whil show the 
	detail of the relationship between the child and parent
	
	the result is follwing:

	hale@hale-virtual-machine:~/uc/Process$ ./a.out 
	This is the parent
	This is the child
	This is the child
	This is the parent
	This is the child
	This is the parent
	This is the child
	hale@hale-virtual-machine:~/uc/Process$ This is the child
	This is the child
	<<blanklie>>

	the parent may (much more posibity) rerturn earlier, however parent'
	parent is SHELL , so the flow get back to SHELL , so shell print the 
	prompt ,  however at moment the child is still runing , so it will 
	print the information follwing the prompt. But SHELL will not print
	the prompt again.Note: at this moment the flow have come back to the 
	shell , so we can normally use shell or type command in the shll.



*/
