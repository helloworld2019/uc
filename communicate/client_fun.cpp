#include "head.h"
#include "mystring.h"
#include "packet.h"
#include "database.h"
#include "io.h"
void client_sendinformation(char* from , char* to , char* information,int fd){
	char message[1024];
	bzero(message,1024);
	
	int n = sendMessage(from,to,information,message);
	for(int i = 0 ; i < n ; i++){
		printf("%c",message[i]);
	}
	printf("\n");
	writen(fd,message,n);
}

void client_recvinformation(int fd){
	printf("in client_recvinformation()\n");
	char buffer[1024];
	char username[100];
	char peername[100];
	char message[1024];

	bzero(buffer,1024);
	bzero(username,100);
	bzero(peername,100);
	bzero(message,1024);
	
	int c = readn(fd,buffer,4);
	if(c==-1){
		perror("readn");
		exit(1);
	}
	
	int number = getnumber(buffer);
	
	c = readn(fd,buffer+4,number);
	if(c==-1){
		perror("readn");
		exit(1);
	}

	getusername(buffer,username);
	getpeername(buffer,peername);
	getinformation(buffer,message);
	
	printf("from:%s\n",username);
	printf("to:%s \n",peername);
	printf("%s\n",message);

}
bool client_login(char* username , char* password ,int fd){
		char message[100];
		char rev[100];
		bzero(message,100);
		bzero(rev,100);
		printf("in the client_login\n");
		int n ;
		n = loginMessage(username,password,message);
		printf("the length is %d",getnumber(message));	
		for(int j = 0 ; j < n ; j++){
			printf("%c",message[j]);
		}
		
		writen(fd,message,n);
		
		while(1){
			int n = readn(fd,rev,10);
			printf("have readn\n");
			printf("%s\n",rev);
			if(n==10){
				printf("true\n");
				return true;
			}
			if(n==0){
				printf("unknow error");
				exit(0);
			}
			if(n<0){
				if(errno==EINTR){
					continue;
				}
				break;
			}
		}		
		return false;
}

bool menu(int fd){
	for(int i = 0 ; i < 20 ; i++){
		printf("\n");
	}
	char username[100];
	char password[100];
	
	bzero(username,100);
	bzero(password,100);

	printf("welcom\n");
	
	printf("please input your user name: \n");
	scanf("%s",username);

	printf("please input your password: \n");
	scanf("%s",password);

	if(client_login(username,password,fd))return true;
	return false;
}

int client_send(int fd){
	char username[100];
	char peername[100];
	char message[1024];
	bzero(message,1024);
	bzero(username,100);
	bzero(peername,100);
	fflush(stdin);
	printf("please input the username\n");
	scanf("%s",username);
	printf("please input the peername\n");
	scanf("%s",peername);
	printf("please input the message\n");
	gets(message);
	gets(message);
	printf("message is :%s\n",message);
	client_sendinformation(username,peername,message,fd);
	char a;
	scanf("%c",&a);
	if(a=='q')return 0;
	return 1;
}

void client_start(int fd){
	if(menu(fd)){
		int pid ;
		pid = fork();
		if(pid<0){
			perror("pid");
			exit(2);
		}
		if(pid>0){
			while(1){
				client_recvinformation(fd);	
			}
		}
		else{
			while(1){
				int opt = client_send(fd);	
				if(opt==1){
					kill(pid,SIGKILL);
					break;
				}
			}
			wait(NULL);
		}
	}
	return; 
}
