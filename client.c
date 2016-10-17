#include <stdio.h> 
#include <string.h>  
#include <sys/socket.h>    
#include <arpa/inet.h> 
 
int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[255], server_reply[BUF_SIZE], savefile[255];
    memset(message, 0, 255);
    memset(savefile, 0, 255);
     
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
    }
    printf("Socket created\n");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
     
        }
        fwrite(server_reply, sizeof(char), read_size, file);
        already_read += read_size;
        memset(server_reply, 0, BUF_SIZE);
    }
    fclose(file);
    close(sock);
    return 0;
}
