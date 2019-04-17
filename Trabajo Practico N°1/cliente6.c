#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define PORTNUMBER  12345

int main(int argc, char **argv){

    int sock,n;
    struct sockaddr_in server;
    char mensaje[150];

    

    sock = socket(AF_INET , SOCK_STREAM, 0);
    
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUMBER);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) <0)
    {
        perror("Error de conección. ERROR\n");
        return 1;
    }
    printf("Conectado al servidor.\n\n");
    sleep(1);
    printf("Ingrese el mensaje.\n");
    fgets(mensaje,150,stdin);
    send(sock,mensaje,strlen(mensaje),0);
    close(sock);
    return(0);
}