#include "head.h"
#include "packet.h"
#include "database.h"
#include "io.h"
#include "mystring.h"
extern usr_DB* db;
extern pthread_mutex_t mutex;
void* transfer(void* );
bool testin(int connect);
void start(int listenfd){
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	while(1){
		int connect = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen);
		if(connect < 0 ){
			if(errno == EINTR){
				continue;
			}
			else{
				perror("connect");
			}
		}
		while(!testin(connect)){
			int count = writen(connect,"wrong user or password",22);
			if(count>0)break;
			if(count<0){
				if(errno==EINTR){
					continue;
				}
				perror("writen");
				exit(1);
			}
			if(count==0){
				printf("pid:%d offline",getpid());
				exit(0);
			}
	
		}
		printf("hello?\n");	
		writen(connect,"successful",10);
		printf("hi\n");
		pthread_t tid;
		int t = connect;
		pthread_create(&tid,NULL,transfer,(void*)&t);
	}
}

bool testin(int connect){
	char buffer[1024];
	while(1){
		bzero(buffer,1024);
		int count = readn(connect,buffer,4);
		if(count>0)break;
		if(count<0){
			if(errno==EINTR){
				continue;
			}
			else{
				perror("readn");
				exit(1);
			}
		}
		else{
			break;
		}
	}
	int number = getnumber(buffer);
	printf("the number is %d \n",number);
	char user[100];
	char password[100];
	bzero(user,100);
	bzero(password,100);

	readn(connect,buffer+4,number);

	getusername(buffer,user);
	getpassword(buffer,password);

	printf("username %s\n",user);
	printf("password %s\n",password);

	char fd[100];
	bzero(fd,100);
	itoc(connect,fd);
	pthread_mutex_lock(&mutex);	
	if(db->check(user,password)){
		printf("user and password are correct!\n");
		db->setfd(user,fd);
		pthread_mutex_unlock(&mutex);
		printf("finish the testin\n");
		return true;
	}
	pthread_mutex_unlock(&mutex);
	return false;
}

void* transfer(void* con){
	char buffer[1024];
	char to[100];
	printf("connect is %d",connect);
	int connect = *((int*)con);
	while(1){
			bzero(to,100);
			bzero(buffer,1024);

			while(1){		
					int count = readn(connect,buffer,4);
					if(count>0)break;
					if(count == 0 ){
						printf("%d offline",connect);
						exit(0);
					}
					if(count<0){
						if(errno==EINTR){
							continue;
						}
						else{
							perror("readn");
							exit(1);
						}
					}		
			}
			
			int number = getnumber(buffer);
			printf("in server recv number is %d\n",number);
			while(1){		
					int count = readn(connect,buffer+4,number);
					if(count>0)break;
					if(count == 0 ){
						printf("%d offline",connect);
						exit(0);
					}
					if(count<0){
						if(errno==EINTR){
							continue;
						}
						else{
							perror("readn");
							exit(1);
						}
					}
					
			}
			for(int k = 0 ; k < number+4 ;k++){
				printf("%c",buffer[k]);
			}
			getpeername(buffer,to);
			printf("peername is %s",to);
			
			printf("buffer is %s\n",buffer);		
			
			pthread_mutex_lock(&mutex);	
			int fd =  db->getfd(to);
			pthread_mutex_unlock(&mutex);	
			
			printf("get fd , and fd is %d\n",fd);
			int c = writen(fd,buffer,number+4);
			printf("in transfer , finish writen wrintein is %d\n",c);
	}		
}
