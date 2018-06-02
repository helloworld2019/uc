
all: echoclient.o echoserver.o  io.o head.h packet.h
	 gcc echoclient.o io.o -o echoclient -g
	 gcc echoserver.o io.o -o echoserver -g
	 rm *.o
echoserver.o: echoserver.c head.h packet.h
				gcc -c echoserver.c -g 

echoclient.o: echoclient.c head.h packet.h
				gcc -c echoclient.c -g 

io.o: io.c head.h packet.h
	  gcc -c io.c -g 

clean: 
		rm echoserver echoclient
