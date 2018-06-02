#include "head.h"

int timer=0;

void handle(int a){
	printf("Bi! %d\n",timer);
	timer++;
	alarm(1);
}


int main(){
	signal(SIGALRM,handle);
	alarm(1);
	while(1){
	}
}


/*
   the SIGALRM   default deal is to terminalte the progress
*/
