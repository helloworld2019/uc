#include "head.h"


int readn(int fd , char* buf , int count ){
	int nleft = count ;
	char* bp = (char*)buf;
	while(nleft>0){
		int n = read(fd,bp,count);
		if(n<0){
			if(errno==EINTR){
				continue;
			}
			return -1 ;
		}
		else if(n==0){
			return count - nleft;
		}
		else{
			nleft -=  n ;
			bp += n ;
		}
	}	
	return count ;
}

int writen(int fd , char* buf , int count ){
	int nleft = count ;
	char* bp = (char*)buf;
	while(nleft>0){
		int n = write(fd,bp,count);
		if(n<0){
			if(errno==EINTR){
				continue;
			}
			return -1 ;
		}
		else if(n==0){
			return count - nleft;
		}
		else{
			nleft -=  n ;
			bp += n ;
		}
	}	
	return count ;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len){
	while(1){
		int n = recv(sockfd, buf, len , MSG_PEEK);
		if(n==-1&&errno==EINTR)continue;
		return n;
	}
}


ssize_t myreadline(int sockfd , void* buffer , ssize_t max){
	char* buff = (char *)buffer;
	int nread = recv_peek(sockfd,buff,max );
	if(nread<0){
		perror("recv_peek");
		exit(1);
	}
	else if(nread==0){
		return 0;
	}
	for(int i = 0; i < nread ; i++){
		if(buff[i]=='\n'){
			bzero(buff,nread);
			int n = readn(sockfd,buff,i+1);
			if(n!=i+1){
				perror("readn");
				exit(1);
			}
			return n ;
		}
	}
	
	nread = readn(sockfd,buff,max);
   	if(nread!=max)exit(1);
	return max;	
}

