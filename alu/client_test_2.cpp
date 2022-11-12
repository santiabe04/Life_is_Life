#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <unistd.h>

char *ip;
int fd,numbytes,port;
char buf[100];

void send_message(int sock,const char* message) {
    send(sock, message,26,0);
}

void recv_message(int sock) {
    if((numbytes = recv(sock,buf,100,0)) == -1) {
        printf("Error recv() \n");
        exit(-1);
    }

    buf[numbytes] = '\0';

    printf("Mensaje del server: %s\n",buf);
}

void close_conn(int sock) {
    close(sock);
}

int main(int argc, char *argv[]) {
    if(argc > 2) {
        port = atoi(argv[2]);
        ip = argv[1];

        struct hostent *he;
        struct sockaddr_in server;

        if((he = gethostbyname(ip)) == NULL) {
            printf("Error gethostbyname() \n");
            exit(-1);
        }

        if((fd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
            printf("Error socket() \n");
            exit(-1);
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr = *((struct in_addr *)he->h_addr);
        bzero(&(server.sin_zero),8);

        if(connect(fd,(struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
            printf("Error connect() \n");
            exit(-1);
        }

        recv_message(fd);

        send_message(fd, "Thanks\n");

        close_conn(fd);
    }
    else {
        printf("ERROR");
    }
}