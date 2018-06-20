#include "database.h"
#include "mystring.h"
#include "head.h"

usr_DB::usr_DB(){
	conn = new MYSQL;
	conn  = mysql_init(NULL);
	server = "localhost";
	user = "root";
	password = "123";
	database = "user_infor";

	online_client = 0 ;

	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		perror("database connect failed!");
		exit(1);
	}

}

usr_DB::~usr_DB(){
	mysql_close(conn) ;
	free(conn) ;
}


bool usr_DB::check(char* u , char* pwd){
	MYSQL_RES *res;
	MYSQL_ROW row;	
	if(mysql_query(conn,"select * from usr\0")){
		perror("quer error");
		exit(2);
	}

	res = mysql_use_result(conn);

	while((row=mysql_fetch_row(res))!=NULL){
		if(!strcmp(row[0],u)){
			if(!strcmp(row[1],pwd)){
				mysql_free_result(res);
				return true;
			}
		}
	}

	mysql_free_result(res);
	return false;
}

void usr_DB::login(char* u){
	char query[100] ="update usr set status = 1 where user=\0";
	
	join(query,"'");
	join(query,u);
	join(query,"'");	
	
	if(mysql_query(conn,query)){
		perror("query error");
		exit(2);
	}
}

void usr_DB::offline(char* u){
	char query[100] ="update usr set status = 0 where user= ";

	join(query,"'");
	join(query,u);
	join(query,"'");	

	if(mysql_query(conn,query)){
		perror("query error");
		exit(2);
	}
}

unsigned int usr_DB::get_online_client(){
	return online_client;
}


void usr_DB::getip(char* username , char* ip){
	char query[100];
	bzero(query,100);
	join(query,"select ip from usr where user= ");
	join(query,"'");
	join(query,username);
	join(query,"'");

	MYSQL_RES *res;
	MYSQL_ROW row;	
	
	if(mysql_query(conn,query)){
		perror("query error");
		exit(2);
	}

	res = mysql_use_result(conn);

	if((row=mysql_fetch_row(res))!=NULL){
		int k = 0 ;
		while(row[0][k]!='\0'){
			ip[k] = row[0][k];
			k++;		
		}
	}

	mysql_free_result(res);
}

void usr_DB::getport(char* username , char* port){
	char query[100];
	bzero(query,100);
	join(query,"select port from usr where user= ");
	join(query,"'");
	join(query,username);
	join(query,"'");
	MYSQL_RES *res;
	MYSQL_ROW row;	
	
	if(mysql_query(conn,query)){
		perror("query error");
		exit(2);
	}

	res = mysql_use_result(conn);

	if((row=mysql_fetch_row(res))!=NULL){
		int k = 0 ;
		while(row[0][k]!='\0'){
			port[k] = row[0][k];
			k++;		
		}
	}

	mysql_free_result(res);
}

void usr_DB::setip(char* username , char* ip){
	char query[100];
	bzero(query,100);

	join(query,"update usr set ip= ");
	join(query,"'");
	join(query,ip);
	join(query,"'");
	join(query," where user= ");
	join(query,"'");
	join(query,username);
	join(query,"'");
	if(mysql_query(conn,query)){
		perror("query error");
		exit(2);
	}

}


void usr_DB::setport(char* username , char* port){
	char query[100];
	bzero(query,100);

	join(query,"update usr set port= ");
	join(query,port);
	join(query," where user= ");
	join(query,username);

	if(mysql_query(conn,query)){
		perror("query error");
		exit(2);
	}

}

void usr_DB::setfd(char* username , char* fd){
	char query[100];
	bzero(query,100);

	join(query,"update usr set fd= ");
	join(query,fd);
	join(query," where user='");
	join(query,username);
	join(query,"'");
	printf("querry is %s\n",query);
	int s  ;
	if( (s=mysql_query(conn,query)) ){
		printf("s = %d\n",s);
		perror("dfsfd query error");
		exit(2);
	}

}

int usr_DB::getfd(char* username){
	char query[100];
	char fd[10];
	bzero(fd,10);
	bzero(query,100);
	join(query,"select fd from usr ");
	join(query," where user= '");
	join(query,username);
	join(query,"'");

	MYSQL_RES *res;
	MYSQL_ROW row;	
	
	if(mysql_query(conn,query)){
		perror("getfd query error");
		exit(2);
	}

	res = mysql_use_result(conn);
	
	if((row=mysql_fetch_row(res))!=NULL){
		int ki = 0;
		while(row[0][ki]!='\0'){
			fd[ki] = row[0][ki];
			ki++;
		}
		fd[ki]='\0';
	}

	int number = ctoi(fd);
	mysql_free_result(res);
	return number;
}

bool usr_DB::isonline(char* username){
	char query[100]="select status from usr where user = '";
	join(query,username);
	join(query,"'");


	MYSQL_RES *res;
	MYSQL_ROW row;	
	
	if(mysql_query(conn,query)){
		perror("getstatus query error");
		exit(2);
	}

	res = mysql_use_result(conn);
	char status[10];
	bzero(status,10);
	if((row=mysql_fetch_row(res))!=NULL){
		int ki = 0;
		while(row[0][ki]!='\0'){
			status[ki] = row[0][ki];
			ki++;
		}
		status[ki]='\0';
	}

	int number = ctoi(status);
	mysql_free_result(res);
	printf("status is %d",number);
	return number;
}
