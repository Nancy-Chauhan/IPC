
server1 : server.o init.o 
	#thread1.o thread.o
	gcc -o server1 server.o init.o 
#thread1.o thread.o

server.o: server.c header.h decleration.h ds.h 
	gcc -c server.c
init.o: init.c header.h decleration.h ds.h
	gcc -c init.c
#thread1.o: thread1.c header.h decleration.h ds.h
#	gcc -c thread1.c -lpthread
#thread.o: init.c thread.c decleration.h ds.h
#	gcc -c thread.c -lpthread
