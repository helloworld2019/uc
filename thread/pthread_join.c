#include "head.h"


void* thr_fn(void* arg){
	printf("In the thr_fn\n");
	while(1){
		printf("I am in the loop\n");
		sleep(1);
	}
	pthread_exit((void*)2);
}

int main(){
	
	void* tret;
		
	pthread_t tid1;
	
	pthread_create(&tid1,NULL,thr_fn,NULL);

	pthread_join(tid1,&tret);

	printf("the thread have return\n");

	
}



/*
	this is code have tell us that pthread_join have wait function , 
	the pthread_join() will wait the specified thread to return;


*/
