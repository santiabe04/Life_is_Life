#include "utils.h"

void send_message(int sock,const char* message) {
    send(sock, message,26,0);
}

void recv_message(int sock) {
    if((numbytes = recv(sock,buf,100,0)) == -1) {
        printf("Error recv() \n");
        exit(-1);
    }

    buf[numbytes] = '\0';

    printf("Mensaje recibido: %s\n",buf);
}

void close_conn(int sock) {
    close(sock);
}