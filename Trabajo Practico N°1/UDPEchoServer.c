#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define BUFLEN 256
#define PORTNUMBER 8888
int main()
{
    int sock;
    int addr_len, bytes_read, bytes_write;
    char recv_data[BUFLEN];
    struct sockaddr_in server_addr , client_addr;
//Creamos el socket al que nos vamos a comunicar.
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNUMBER);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero),8);
    if (bind(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Bind");
        exit(1);
    }
    addr_len = sizeof(struct sockaddr);
    printf("UDPServer Waiting for client on port %d\n",PORTNUMBER);
    fflush(stdout);
    while (1)
    {
        printf("Esperando información...\n");
        fflush(stdout);
        if ((bytes_read = recvfrom(sock,recv_data, BUFLEN, 0, (struct sockaddr *) &client_addr, &addr_len)) == -1)
        {
            printf("ERROR RECIBIENDO MENSAJE\n");
            break;
        }
        recv_data[bytes_read] = '\0';
        //Devolvemos lo recibido (hacemos el ECHO)
        if (bytes_write = sendto(sock,recv_data,strlen(recv_data),0,(struct sockaddr *)&client_addr,sizeof(struct sockaddr)) == -1)
        {
            printf("ERROR ENVIANDO MENSAJE.\n");
            break;
        }
        printf("se recibió desde el servidor: %s\n",recv_data);
    }
    return 0;
}
