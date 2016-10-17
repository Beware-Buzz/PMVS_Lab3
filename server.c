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

 
    }
    printf("bind done\n");     

    listen(socket_desc, 5);
     
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
     
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        printf("Connection accepted\n");
                 
        new_sock = malloc(1);
        *new_sock = client_sock;

        #ifdef PROCESS
        pid_t childpid = 0;
        if ((childpid = fork())== -1) {
            perror("fork error");
            return 1;
        }
        if (childpid == 0) {
            connection_handler((void*) new_sock);
        }

        #else
        pthread_t th;
        if (pthread_create(&th, NULL,  connection_handler, (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        #endif

        printf("Handler assigned\n");
    }
     
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}

void* connection_handler(void* socket_desc)
{
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , filename[255];
    memset(filename, 0, 255);
    if ((read_size = recv(sock , filename, 255 , 0)) > 0) {
        printf("filename!!! %s\n", filename);
        FILE *file = fopen(filename, "rb");
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int file_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            write(sock, &file_size, 4);
            char buf[BUF_SIZE];
            int c = 0;
            memset(buf, 0, BUF_SIZE);
            while ((c = fread(buf, sizeof(char), BUF_SIZE, file)) > 0) {                
                write(sock , buf, c);
                memset(buf, 0, BUF_SIZE);
            }

            fclose(file);
        }
    	
    }
     
    if(read_size == 0) {
        printf("Client disconnected\n");
    }
    else if(read_size == -1) {
        perror("recv failed");
    }

    free(socket_desc);

    #ifdef PROCESS
    exit(0);
    #endif  
    return 0;
}
