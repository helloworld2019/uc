all: client.o server.o io.o database.o mystring.o client_fun.o server_fun.o packet.o  
	 g++ io.o server.o mystring.o packet.o server_fun.o database.o -lmysqlclient -lpthread -o server -g
	 g++ client.o io.o mystring.o packet.o client_fun.o database.o  -lmysqlclient  -o client -g
	 rm *.o
server.o: server.cpp head.h packet.h
				g++ -c server.cpp -g 

client.o: client.cpp head.h packet.h
				g++ -c client.cpp -g 

io.o: io.cpp head.h io.h
	  g++ -c io.cpp -g

mystring.o: mystring.cpp mystring.h
			g++ -c mystring.cpp -g

packet.o: packet.cpp packet.h
			g++ -c packet.cpp -g

server_fun.o: server_fun.cpp  server_fun.h mystring.cpp packet.cpp io.cpp database.cpp
				g++ -c server_fun.cpp -g

client_fun.o: client_fun.cpp client_fun.h mystring.cpp packet.cpp io.cpp database.cpp
				g++ -c client_fun.cpp -g

database.o: database.cpp database.h
	g++ database.cpp -c -g
clean: 
		rm server client
