#include "head.h"

pthread_t ntid;

void* test(void* t){
	exit(0);
}

int main(){
	pthread_create(&ntid,NULL,test,NULL);
	while(1);
}


/*

   no matter exit() from main thread or other thread whenever , it will terminate the process.

*/
