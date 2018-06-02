#include "head.h"
#include "packet.h"
#include "fun.h"


int do_ser(int listenfd);

struct user{
	int fd ;
	int user;
};


struct user client[100];


void init(){
	for(int i = 0 ; i < 100 ; i++){
		client[i].fd = -1;
		client[i].user = -1;
	}
	
}


int insert(int con){
	printf("insert start\n");
	for(int i = 0; i< 100 ;i++){
		printf("loop\n");
		if(client[i].fd==-1){
			client[i].fd=con;
			client[i].user= con;
			printf("user %d is in client[%d]\n",con,i);
			return i ;
		}
	}
	return -1 ;
}

void removeuser(int fd ){
	for(int i = 0 ; i < 100 ; i++){
		if(client[i].fd==fd){
			client[i].fd=-1;
			client[i].user=-1;
			return ;
		}
	}
}


int find(int name){
	for(int i = 0 ; i < 100 ; i++){
		if(client[i].fd==-1)continue;
		if(name==client[i].user){
			return client[i].fd;
		}
	}
	return -1;
}

int findMax(){
	int max = 0;
	for(int i = 0 ; i < 100 ;i++){
		if(client[i].fd>max){
			max = client[i].fd;
		}
	}
	return max ;
}

int ctou(char* n){
	int i = 0 ;
	while(n[i]!=0){
		i++;
	}
	i--;
	int sum = 0 ;
	for(;i>=0;i--){
		sum += (n[i]-'0');
		sum = sum*10;
	}
	sum /= 10;
	return sum;
}


int main(){
	char buff[1000];
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

	init();


	do_ser(listenfd);
}

int do_ser(int listenfd){
	printf("start\n");
	int conn ;
	int nready;
	int maxfd = listenfd;
	fd_set rset ;
	fd_set allset;
	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

	for(;;){
		rset = allset;
		nready = select(maxfd+1,&rset,NULL,NULL,NULL);
		printf("in\n");
		printf("nready=%d\n",nready);
		if(nready==-1){
			if(errno == EINTR){
				continue;
			}
			perror("select");
			exit(1);
		}
		if(nready==0){
			continue ;// timeout
		}

		if(FD_ISSET(listenfd,&rset)){
			struct sockaddr_in peeraddr;
			socklen_t peerlen = sizeof(peeraddr);
	
			conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen);
			printf("ipv4:%s ,prot: %d has connected \n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));

			if(conn==-1){
				perror("accept");
				exit(1);
			}
			printf("user:%d login\n",conn);
			
			int f = insert(conn);			
			printf("finish insert\n");
			if(f==-1){
				printf("client has full\n");
				close(conn);
			}
			if(f!=-1){
				FD_SET(conn,&allset);
				maxfd = findMax();
			}
			if(--nready==0)continue;
		}
		
		for(int k = 0 ; k < 100 ; k++){
			if(client[k].fd==-1)continue;
			if(FD_ISSET(client[k].fd,&rset)){
				printf("maxfd is %d\n",maxfd);
				printf("event in k : %d\n",k);
				struct packet recvbuffer;
				int length;
				int n ;
				bzero(&recvbuffer,sizeof(recvbuffer));
				printf("start to read the length\n");	
				readn(client[k].fd,&n,4);
				printf("mid in length\n");
				length = ntohl(n);
				printf("the length is %d",length);
				recvbuffer.len = n ;
				readn(client[k].fd,recvbuffer.buffer,length);
				char username[10];
				bzero(username,10);
				int i = 0 ;
				while(1){
					if(recvbuffer.buffer[i]==' ')break;
					username[i]=recvbuffer.buffer[i];
					i++;
				}

				int t = ctou(username);
				printf("user name %d\n",t);
				int target = find(t);
				if(target==-1)continue;
				printf("start send\n");
				writen(target,&recvbuffer,4+length);
				printf("finish the send\n");
			}
			
		}
		
		printf("finish all event\n");
		
	}

}

