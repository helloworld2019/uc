
all: client.o server.o  io.o head.h packet.h
	 gcc client.o io.o -o client -g
	 gcc server.o io.o -o server -g
	 rm *.o
echoserver.o: server.c head.h packet.h
				gcc -c server.c -g 

echoclient.o: client.c head.h packet.h
				gcc -c client.c -g 

io.o: io.c head.h packet.h
	  gcc -c io.c -g 

clean: 
		rm server client
