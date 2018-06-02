#include "head.h"
#include "packet.h"


ssize_t readn(int fd , void* buf , size_t count ){
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

ssize_t writen(int fd , void* buf , size_t count ){
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
	char* buff = buffer;
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

/**
* read timeout - detect the time out witout reading byte no I/O

* @fd file descripter
* @wiat_seconds: wait time if wait_seconds equal zero, the 
  function wound't operate and return zero

  if succesee return zero ,if timeout return -1 errno = timeout .
*/


int read_timeout(int fd , unsigned int wait_seconds){
	int ret = 0 ;
	if(wait_seconds){
		FD_SET rset;
		FD_ZERO(&reset);
		FD_SET(fd,&reset);
		
		struct timeval timeou;
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;

		do{
			ret = select(fd+1,&rset,NULL,NULL,timeout);
		}while(ret<0&&errno = EINTR);
		
		if(ret==0){
			errno = ETIMEDOUT;
			return -1;
		}
		else if(ret==1){ 
			return 1;
		}
	}

	return 0;
}


/**
  * accept_timeout   will would operate the accept()
  * @fd: socket 
  * @addr: output argument, return the peer's address 
  * @wait_seconds: wait time if equal zero it will represent the 
  	the normal mode
  * succese return the connect socket , timeout return -1 and 
  	errno=ETIMEDOUT
*/

int accept_timeout(int fd, struct sockaddr_in *addr , unsigned int wait_seconds){
	int ret ;
	if(wait_seconds>0){
		FD_SET fdaccept ;
			struct timeval timeout ;

			FD_ZERO(&fdaccept);
			FD_SET(fd,&fdaccept);

			timeout.tv_sec = wait_seconds;
			timeout.tv_usec = 0 ;

			struct socklen_t arrlen = sizeof(struct sockaddr_in);
			
			do{
				ret = select(fd+1,&fdaccept,NULL,NULL,timeout);
			}while(ret<0&&errno==EINTR)
			
			if(ret==-1){
				return -1;
			}
			else if(ret == 0){
				errno = ETIMEDOUT;
				return -1;
			}
	}

	if(addr!=NULL){
		ret = accept(fd,(struct sockaddr*)addr,&addrlen);
	}
	else{
		ret = accept(fd,NULL,NULL);
	}
	if(ret == -1 ){
		perror("accept");
		exit(1);
	}

	return ret;

}

/*
   *connect_timeout - connect
   *@fd : socket
   *@addr: peer address 
   *@wait_timeout : wait time
   *@success return 0 if fail return -1 , if timeout return -1 and set errno
    ETIMEDOUT
*/

/*
	set nonblock mode
	* @ fd file descripter
*/
void active_nonblock(int fd){
	int ret;
	int flags = fentl(fd,F_GETFL); // get the flags of the file descripter
	if(flags==-1){
		perror("fcntl");
		exit(1);
	}
	flags |= O_NONBLOCK;
	ret = fcntl(fd,F_SETFL,flags);
	if(ret==-1){
		perror("fcntl");
		exit(1);
	}
}

void deactive_nonblock(int fd){
	int ret ;
	int flags = fcntl(fd,F_GETFL);
	if(flags==-1){
		perror("fcntl");
		exit(0);
	}
	flags &= ~O_NONBLOCK;
	ret = fcntl(fd,F_SETFL,flags);
	if(ret==-1){
		perror("fcntl");
		exit(1);
	}
}


/*

	wait_timeout if equal zero , operate normal mode
*/
//11
int connect_timeout(int fd , struct sockaddr_in* addr , unsigned int wait_seconds){
	int ret ;
	sockelen_t addrlen = sizeof(struct sockaddr_in);	
	ret = connect(fd,(struct sockaddr*)addr , addrlen);
	
	if(ret<0&&errno == EINPROGRESS){              //  connect will return EINTPROGRESS if connect fails in nonblock mode 
		fd_set con_fdset;
		struct timeval timeout;
		FD_ZERO(&con_fdset);
		FD_SET(fd,&con_fdset);
		timeout.tv_sec = wait_seconds;
		timeout.tv_uset = 0;
		
		do{
				ret = select(fd+1,NULL,&con_fdset,NULL,&timeout); // once the socket is connectd , the socket can be writtem , so in writeset
		}while(ret<0&&errno == EINTR)
		
		if(ret == 0 ){
			errno = ETIMEDOUT;
			return -1;
		}

		else if(ret < 0){
			return -1;	
		}
		
		else if(ret == 1){
			// ret equals zero , there may be two posibilities 
			// one is socker have error in wrtie set 
			// socket is connected
			int err ;
			socklen_t socklen = sizeof(err);
			int sockopret = getsockopt(fd,SOL_SOCKET,SO_ERROR,&err,&socklen);
			if(sockoptret == -1){
				return -1;
			}
			if(err == 0){
				ret = 0 ;
			}
			else{
				errno = err;
				ret = -1;
			}
		}
	}


	}
}
