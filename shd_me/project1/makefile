
server1 : server.o init.o 
	gcc -o server1 server.o init.o 

server.o: server.c header.h decleration.h ds.h 
	gcc -c server.c
init.o: init.c header.h decleration.h ds.h
	gcc -c init.c
