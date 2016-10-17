
all: client server

.PHONY: server
server: serverproc serverth

client: client.c
	gcc -D BUF_SIZE=100 client.c -o client

serverproc: server.c
	gcc -D PROCESS -D BUF_SIZE=100 -pthread server.c -o serverproc

serverth: server.c
	gcc -D BUF_SIZE=100 -pthread server.c -o serverth

clean:
	rm client serverth serverproc
