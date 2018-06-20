#include "head.h"
#include "packet.h"
#include "database.h"
#include "io.h"
#include "mystring.h"
extern usr_DB* db;
extern pthread_mutex_t mutex;
void transfer(int,char* user);
void* deal(void*);
bool testin(int connect,char* user);
int conne_array[1024];
void start(int listenfd){
	int kk = 0 ;
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
	
		pthread_t tid;
		conne_array[kk] = connect;
		int err = pthread_create(&tid,NULL,deal,(void*)(&conne_array[kk]));
		printf("err is %d",err);
		kk++;
	}
}


void* deal(void* conn){
	int connect = *((int*)conn);
	char user[100];
	bzero(user,100);
	if(!testin(connect,user)){	
		int count = writen(connect,"n",1);
		if(count==0){
			printf("pid:%d offline",getpid());
			close(connect);
			pthread_exit(NULL);
		}
		else{
			printf("writen error!\n");
			close(connect);
			pthread_exit(NULL);			
		}
		close(connect);
		return NULL;	
	}
	writen(connect,"y",1);
	transfer(connect,user);
	return NULL;
}



bool testin(int connect, char* user){
	char buffer[1024];
	bzero(buffer,1024);
	int count = readn(connect,buffer,4);
	if(count==0)return false;
	
	int number = getnumber(buffer);
	char password[100];
	bzero(user,100);
	bzero(password,100);

	readn(connect,buffer+4,number);

	getusername(buffer,user);
	getpassword(buffer,password);


	char fd[100];
	bzero(fd,100);
	itoc(connect,fd);
	pthread_mutex_lock(&mutex);	
	if(db->check(user,password)){
		printf("user and password are correct!\n");
		db->setfd(user,fd);
		db->login(user);
		pthread_mutex_unlock(&mutex);
		printf("finish the testin\n");
		return true;
	}
	pthread_mutex_unlock(&mutex);
	return false;
}

void transfer(int connect,char* user){
	char buffer[1024];
	char to[100];
	char from[100];
	char message[100];
	
	printf("\n in transfer and , connect is %d",connect);
	while(1){
			bzero(to,100);
			bzero(from,100);
			bzero(buffer,1024);
			bzero(message,100);
			
			int count = readn(connect,buffer,4);
		
			if(count == 0 ){
				printf("%d offline",connect);
				pthread_mutex_lock(&mutex);	
				db->offline(user);
				pthread_mutex_unlock(&mutex);
				close(connect);	
				pthread_exit(NULL);
			}
			
			else if(count<0){
				perror("readn");
				close(connect);
				pthread_exit(NULL);				
			}
			
			int number = getnumber(buffer);
		
			count = readn(connect,buffer+4,number);
			
			if(count == 0 ){
				printf("%d offline",connect);
				pthread_mutex_lock(&mutex);	
				db->offline(user);
				pthread_mutex_unlock(&mutex);	
				close(connect);
				pthread_exit(NULL);
			}
			
			else if(count<0){
				perror("readn");
				pthread_exit(NULL);
			}
					
			
			getusername(buffer,from);
			getpeername(buffer,to);
			getinformation(buffer,message);
			printf("\nReaquest:\nfrom:%s\nto:%s\nmessage:%s\n",from,to,message);
			
			pthread_mutex_lock(&mutex);
			if(!db->isonline(to)){	
				printf("destination is offline\n");
				char message[5]="0000";
				int c = writen(connect,message,4);
				if(c==0){
					pthread_mutex_unlock(&mutex);
					close(connect);
					pthread_exit(NULL);
				}
				else if(c<0){
					perror("writen in 149 in server");
					exit(1);
				}
				continue;
			}	
			int fd =  db->getfd(to);
			pthread_mutex_unlock(&mutex);	
			
			int c = writen(fd,buffer,number+4);
			if(c==0){
				printf("offline\n");
				db->offline(user);
				pthread_exit(NULL);
			}
			if(c<0){
				printf("write error\n");
				pthread_exit(NULL);
			}
			printf("\n in transfer , finish writen wrintein is %d\n",c);

	}
}	
