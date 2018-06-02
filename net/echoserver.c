#include "head.h"
#include "packet.h"
#include "fun.h"


int do_ser(int listenfd);


void handle_child(int a){
	int n ;
	while((n=waitpid(-1,NULL,0))>0){
		printf("reap child %d\n",n);
	}
}

	

int main(){
	char buff[1000];
	int listenfd ;
	struct sockaddr_in serveraddr;

	signal(SIGCHLD,handle_child);

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(13);

	if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
		perror("sockt:");
		exit(1);
	}

	listen(listenfd,100);

	do_ser(listenfd);
}

int do_ser(int listenfd){
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	
	for(;;){
		int connect;
		if ( (connect=accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0){
			perror("connect");
		}

		pid_t pid ;
		if((pid=fork())<0){
			perror("fork");
			exit(1);
		}
		
		if(pid==0){
			printf("ipv4:%s ,prot: %d has connected \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
			int n ;
			char buffer[MAXBUFFER]={0};
			while(1){
				printf("From ipv4:%s ,prot: %d \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
				int a = myreadline(connect,buffer,MAXBUFFER);
				if(a==0)exit(0);
				printf("%s",buffer);
				write(connect,buffer,strlen(buffer));
				bzero(buffer,MAXBUFFER);
			}
			close(connect);
			exit(0);
		}
		else{
			printf("%d has been creted\n",pid);
		}
	}	
}

