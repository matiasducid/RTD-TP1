#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PORTNUMBER 12345

int main (int argc, char **argv){
    
    char buf[100];
    int s, n, ns, len;
    struct sockaddr_in direcc;

    s = socket(AF_INET,SOCK_STREAM, 0);
    
    bzero((char*)&direcc, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PORTNUMBER);
    direcc.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(struct sockaddr_in);
    bind(s, (struct sockaddr*)&direcc, len);
    listen(s, 5);
    ns = accept(s, (struct sockaddr*)&direcc, &len);
    
    while ((n = recv(ns, buf, sizeof(buf), 0)) > 0){
        int cantidadCaracteres = 0;
        char buffCaracter[4];
        write(1, buf, n);
        while(cantidadCaracteres < 10){
            sprintf(buffCaracter,"%d\n",cantidadCaracteres);
            sleep(1);
            send(ns, buffCaracter, sizeof(buffCaracter), 0);
            cantidadCaracteres +=1;
        }
    }
    close(ns);close(s);
    exit(0);  
   
}
