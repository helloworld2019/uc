#include <mysql/mysql.h>
#include "head.h"

int main(){
	MYSQL *conn ;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char server[] = "localhost"
	char user[] = "root"
	char password = "123"
	char database = "user_infor"

	conn  = mysql_init(NULL);

	if(!mysql_real_connect(conn,server,usr,password,database,0,NULL,0)){
		perror("database connect failed!");
		exit(1);
	}


	if(mysql_query(conn,"show tables")){
		perror("sql error");
		exit(2);
	}

	res = mysql_use_result(conn);

	print("MYSQL table is mysql databases:\n");
	
	while((row=mysql_fetch_row(res)!=NULL)){
		print("%s \n",row[0]);
	}

	mysql_free_result(res);

	mysql_close(conn);

	printf("finish! \n");
	return 0;
}
