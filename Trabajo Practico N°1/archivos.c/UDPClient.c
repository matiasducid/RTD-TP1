#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define PORTNUMBER 8888
#define BUFLEN 256
int main()
{
int sock, bytes_recv, sin_size, bytes_send, cont = 0;
struct sockaddr_in server_addr;
struct hostent *host;
char send_data[BUFLEN],recv_data[BUFLEN];

host= (struct hostent *) gethostbyname((char *)"127.0.0.1");
if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
perror("socket");
exit(1);
}
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORTNUMBER);
server_addr.sin_addr = *((struct in_addr *)host->h_addr);
bzero(&(server_addr.sin_zero),8);
sin_size = sizeof(struct sockaddr);
   while (1)
   {
    memset(recv_data,0,BUFLEN);
    fflush(stdout);
    printf("Escriba su mensaje (q o Q para salir.):");
    //scanf("%s",send_data);//al usar scanf no se acepta que se envie un mensaje vacio.
    gets(send_data);
    if ((strcmp(send_data , "q") == 0) || strcmp(send_data , "Q") == 0)
       break;
    else{
        if ( bytes_send=sendto(sock, send_data, strlen(send_data), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
            printf("Error en el envio.\n");
    }
    if(bytes_recv = recvfrom(sock,recv_data,BUFLEN,0,(struct sockaddr *)&server_addr,&sin_size) == -1)  
    {   printf("Error en la Recepción\n");
        break;
    }
    printf("Respuesta del servidor: %s\n",recv_data);
   }
    return 0;
}

