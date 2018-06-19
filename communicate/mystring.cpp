#include <string.h>
void join(char* head , const char* tail){
	while(*head){
		head++;
	}
	
	int k = 0 ;
	while(tail[k]){
		head[k] = tail[k];
		k++;
	}

}

void getusername(char * buffer , char* username){
	int i = 0 ;
	buffer = buffer + 4;
	while(buffer[i]){
		username[i] = buffer[i];
		i++;
	}
	username[i]='\0';
}

void getpeername(char* buffer , char* peer ){
	int i = 0 ;
	buffer = buffer + 4;
	while(*buffer){
		buffer++;
	}
	buffer++;	
	while(buffer[i]){
		peer[i] = buffer[i];
		i++;
	}
	peer[i]='\0';
}

void getinformation(char* buffer, char* message){
	buffer = buffer + 4;
	while(*buffer){
		buffer++;
	}
	buffer++;
	while(buffer++){
		buffer++;
	}
	buffer++;
	int i = 0 ;
	while(buffer[i]){
		message[i]=buffer[i];
		i++;
	}
	message[i]='\0';
}

void getpassword(char* buffer , char* password ){
	int i = 0 ;
	buffer = buffer + 4;
	while(*buffer){
		buffer++;
	}
	buffer++;
	while(buffer[i]){
		password[i] = buffer[i];
		i++;
	}
	password[i]='\0';
}


int ctoi(char* a ){
	int n = 0 ;
	while(*a){
		n = n * 10 + (*a-'0');
		a++;
	}
	return n ;
}

void itoc(int n , char* a){
	char tep[10];
	int i = 0 ;
	while(n){
		tep[i++] = n % 10 + '0';
		n = n / 10;
	}
	i--;
	int k  = 0 ;
	while(i>=0){
		a[k] = tep[i];
		k++;
		i--;
	}
	a[k]='\0';
}

int getnumber(char* buffer){
	char number[5];
	bzero(number,5);
	for(int i = 0 ; i < 4 ; i++){
		number[i] = buffer[i];
	}
	return ctoi(number);
}
