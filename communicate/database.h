#include "head.h"

class usr_DB{
	private:
			MYSQL *conn;
			unsigned int online_client;
			const char* server ;
			const char* user ;
		    const char* password;
			const char* database ;
	public:
			usr_DB();
			~usr_DB();
			bool check(char* , char* pwd );
			void login(char* u);
			void offline(char* u);
			void getip(char* username,char* ip);
			void setip(char* username , char* ip);
			void getport(char* username , char* port);
			void setport(char* username, char* port);
			int getfd(char* username);
			void setfd(char* username, char* fd);
			unsigned int get_online_client();

};
