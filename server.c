#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>    
#include <sys/socket.h>
#include <arpa/inet.h>

//1 - fopen

void* connection_handler(void* socket_desc);

int main() 
{
    int socket_desc, client_sock, c, read_size, *new_sock;
    struct sockaddr_in server, client;
    char client_message[260];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
        return 1;
    }
    printf("Socket created\n");     

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed. Error");
        return 1;
    }
    printf("bind done\n");     

    listen(socket_desc, 5);
     
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
     
   
