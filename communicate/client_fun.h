void client_sendinformation(char* , char* to , char* info , int fd);
void client_recvinformation(int fd);
bool client_login(char* username , char* pas , int fd);
bool menu(char* username , int fd);
void client_send(char* from ,int fd);
void client_start(int fd);

