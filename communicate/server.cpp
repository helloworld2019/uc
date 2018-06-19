#include "head.h"
#include "packet.h"
#include "io.h"
#include "server_fun.h"
void handle_child(int a){
	int n ; 
	while((n=waitpid(-1,NULL,0))>0){
		printf("reap child %d\n",n);
	}
}

int main(){
	signal(SIGCHLD,handle_child);
	int listenfd ;
	struct sockaddr_in serveraddr;
	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(13);
	
	int on = 1 ;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){
		perror("setsockopt");
		exit(1);
	}

	if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
		perror("sockt:");
		exit(1);
	}

	listen(listenfd,100);
	
	for(;;){
		start(listenfd);
	}
	
}

