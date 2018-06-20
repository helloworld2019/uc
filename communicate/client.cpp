#include "head.h"
#include "packet.h"
#include "io.h"
#include "client_fun.h"
void handle_child(int a){
	int n ; 
	while((n=waitpid(-1,NULL,0))>0){
		printf("reap child %d\n",n);
	}
	printf("parent and the child close\n");
	exit(0);
}

int main(int argc , char** argv){
	int sockfd , n ;
	struct sockaddr_in servaddr;
	signal(SIGCHLD,handle_child);
	if(argc!=2){
		printf("please use client <IPaddress>\n");
		exit(1);
	}

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("soket error\n");
		exit(1);
	}

	bzero(&servaddr,sizeof(servaddr))	;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0){
		printf("error ip\n");
		exit(1);
	}
	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("connet error \n");
		exit(1);
	}
	printf("connet succese\n");

	client_start(sockfd);
		
	exit(0);
}
