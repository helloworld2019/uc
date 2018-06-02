
/**
* read timeout - detect the time out witout reading byte no I/O

* @fd file descripter
* @wiat_seconds: wait time if wait_seconds equal zero, the 
  function wound't operate and return zero

  if succesee return zero ,if timeout return -1 errno = timeout .
*/

/*
int read_timeout(int fd , unsigned int wait_seconds){
	int ret = 0 ;
	if(wait_seconds){
		FD_SET rset;
		FD_ZERO(&reset);
		FD_SET(fd,&reset);
		
		struct timeval timeou;
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;

		do{
			ret = select(fd+1,&rset,NULL,NULL,timeout);
		}while(ret<0&&errno = EINTR);
		
		if(ret==0){
			errno = ETIMEDOUT;
			return -1;
		}
		else if(ret==1){ 
			return 1;
		}
	}

	return 0;
}


/**
  * accept_timeout   will would operate the accept()
  * @fd: socket 
  * @addr: output argument, return the peer's address 
  * @wait_seconds: wait time if equal zero it will represent the 
  	the normal mode
  * succese return the connect socket , timeout return -1 and 
  	errno=ETIMEDOUT
*/

