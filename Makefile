all: echoclient echoserver

echoclient: echoclient.o
	gcc -g -o echoclient echoclient.o -lpthread

echoclient.o:
	gcc -g -c -o echoclient.o echoclient.c

echoserver: echoserver.o
	gcc -g -o echoserver echoserver.o -lpthread

echoserver.o:
	gcc -g -c -o echoserver.o echoserver.c

clean:
	rm -f echoclient echoserver
	rm -f *.o
