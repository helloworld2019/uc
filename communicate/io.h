int readn(int fd , char* buf , int count);
int writen(int fd, char* buf , int count);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
ssize_t myreadline(int sockdf ,void* buffer, size_t max);
