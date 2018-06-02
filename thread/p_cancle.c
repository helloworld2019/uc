#include "head.h"

void* test(void* t){
	while(1);
	pthread_exit((void*)666);
}





pthread_t ntid;

int main(){
	int* t;
	pthread_create(&ntid,NULL,test,NULL);
	pthread_cancel(ntid);
	pthread_join(ntid,(void*)&t);
	printf("%d",*t);
	

	exit(0);
}
