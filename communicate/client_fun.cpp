#include "head.h"
#include "mystring.h"
#include "packet.h"
#include "database.h"
#include "io.h"


void client_sendinformation(char* from , char* to , char* information,int fd){
	char message[1024];
	bzero(message,1024);
	
	int n = sendMessage(from,to,information,message);
	n = writen(fd,message,n);
	if(n==0)printf("server close\n");
}

void client_recvinformation(int fd){
		while(1){	
			char buffer[1024];
			char username[100];
			char peername[100];
			char message[1024];

			bzero(buffer,1024);
			bzero(username,100);
			bzero(peername,100);
			bzero(message,1024);
	
			int c = read(fd,buffer,4);
			if(c==-1){
				perror("readn");
				exit(1);
			}
			if(c==0){
				printf("server close\n");
				exit(0);
			}
			
			int number = getnumber(buffer);
			c = readn(fd,buffer+4,number);
			if(c==-1){
				perror("readn");
				exit(1);
			}
			else if(c==0){
				printf("server close\n");
				exit(0);
			}
			getusername(buffer,username);
			getpeername(buffer,peername);
	 		getinformation(buffer,message);
  			printf("user: %s\n",peername);
  			printf("%s\n",message);
		}
}
bool client_login(char* username , char* password ,int fd){
		char message[100];
		char rev;
		bzero(message,100);
		int n ;
		n = loginMessage(username,password,message);
		
		writen(fd,message,n);
		
		n = readn(fd,&rev,1);
		if(rev=='y'){
			printf("login status: %c\n",rev);
			return true;
		}
		else if(rev=='n'){
			printf("wrong\n");
			return false;
		}
		printf("server close\n");
		exit(0);
}

bool menu(char* username , int fd){
	char password[100];
	
	bzero(username,100);
	bzero(password,100);

	printf("welcome\n");
	
	printf("please input your user name: \n");
	scanf("%s",username);

	printf("please input your password: \n");
	scanf("%s",password);

	if(client_login(username,password,fd))return true;
	return false;
}

int client_send(char* from , int fd){
		char peername[100];
		char message[1024];
		bzero(peername,100);
		printf("please input the peername\n");
		scanf("%s",peername);
		printf("please input the message\n");
		getchar();
		while(1){	
			bzero(message,1024);
			gets(message);
			client_sendinformation(from,peername,message,fd);
		}
		return 0 ;
}

void client_start(int fd){
	char username[100];
	bzero(username,100);
	if(menu(username,fd)){
		int pid ;
		pid = fork();
		if(pid<0){
			perror("pid");
			exit(2);
		}

		if(pid==0){ 							//child
			client_recvinformation(fd);	
		}

		else{ 									//parent
			client_send(username , fd);	
			wait(NULL);
			exit(0);
		}
		
	}
	return; 
}
