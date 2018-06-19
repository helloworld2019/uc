#include "head.h"
#include "mystring.h"
int loginMessage(char* username , char* password , char* message){
	int k = 0 ;
	int i = 4;
	
	while(username[k]!='\0'&&username[k]!='\n'){
		message[i] = username[k];
		i++;
		k++;
	}
	
	message[i++]='\0';
	
	k = 0 ;
	
	while(password[k]!='\0'&&password[k]!='\n'){
		message[i] = password[k];
		i++;
		k++;
	}
	
	message[i++]='\0';

	char number[4];
	bzero(number,4);
	int count = i - 4 ;
	itoc(count,number);
	for(int j = 0 ; j < 4 ; j++){
		message[j] = number[j];
	}

	return i ;
}

int sendMessage(char* from , char* to , char* information , char* message ){
	
	int i = 4 ;
	int k = 0 ;
	while(from[k]!='\0'&&from[k]!='\n'){
		message[i] = from[k];
		i++;
		k++;
	}
	message[i++]='\0';

	k = 0 ;
	while(to[k]!='\0'&&to[k]!='\n'){
		message[i] = to[k];
		i++;
		k++;
	}
	message[i++]='\0';

	k = 0 ;
	while(information[k]!='\0'&&information[k]!='\n'){
		message[i] = information[k];
		i++;
		k++;
	}
	message[i++]='\0';
	
	char number[5];
	bzero(number,5);
	int count = i - 4 ;
	itoc(count,number);
	for(int j = 0 ; j < 4 ; j++){
		message[j] = number[j];
	}

	return i ;
}

