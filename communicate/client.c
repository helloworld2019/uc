#include "head.h"
#include "packet.h"
#include "fun.h"

void sendinformation(int connect){
	struct packet sendbuffer;
			for(;;){
				bzero(&sendbuffer,sizeof(sendbuffer));
				read(0,sendbuffer.buffer,sizeof(sendbuffer.buffer));
				int n = strlen(sendbuffer.buffer);
				for(int i = 0 ; i < n ; i++){
					printf("%c",sendbuffer.buffer[i]);
				}
				printf("%d\n",n);
				sendbuffer.len = htonl(n);
				n = write(connect,&sendbuffer,4+n);
				printf("write number:%d",n);
				bzero(&sendbuffer,sizeof(sendbuffer));
			}
	
}

void recvinformation(int connect){
	struct packet recvbuffer;
	for(;;){
		bzero(&recvbuffer,sizeof(recvbuffer));	
		read(connect,&recvbuffer.len,4);
	    int n = ntohl(recvbuffer.len);
		read(connect,recvbuffer.buffer,n);
		printf("%s",recvbuffer.buffer);
		bzero(&recvbuffer,sizeof(recvbuffer));
	}
}


int main(int argc , char** argv){
	int sockfd , n ;
	struct sockaddr_in servaddr;

	if(argc!=2){
		printf("please use a.out <IPaddress>\n");
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


	pid_t pid = fork();


	if(pid==0){
		sendinformation(sockfd);
	}

	recvinformation(sockfd);
	wait(NULL);

	exit(0);
}
