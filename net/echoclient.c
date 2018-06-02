#include "head.h"
#include "packet.h"
#include "fun.h"

int do_ser(int connect){
	char sendbuffer[MAXBUFFER]={0};
	char recvbuffer[MAXBUFFER]={0};
	
	fd_set rset;
	while(1){
		int std = fileno(stdin);

		FD_ZERO(&rset);
		
		FD_SET(fileno(stdin),&rset);
		FD_SET(connect,&rset);
		
		int max ;

		if(connect>std){
		 	max = connect ;
		}
		else {
			max = std;	
		}
		int number = select(max+1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(std,&rset)){
			read(std,sendbuffer,sizeof(sendbuffer));
			write(connect,sendbuffer,strlen(sendbuffer));
			bzero(sendbuffer,sizeof(sendbuffer));
		}
		
		if(FD_ISSET(connect,&rset)){
			myreadline(connect,recvbuffer,MAXBUFFER);
			printf("%s",recvbuffer);
			bzero(recvbuffer,sizeof(recvbuffer));	
		}
	}
	
	return 0 ;
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


	do_ser(sockfd);

	exit(0);
}
