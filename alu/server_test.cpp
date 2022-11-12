#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <vector>

using namespace std;

int fd,fd2,cell_len,numbytes,port;
vector<int> cells;
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

    printf("Mensaje de la celula: %s\n",buf);
}

void close_cell(int sock) {
    close(sock);
}

void accept_conn() {
    struct sockaddr_in cell;

    cell_len = sizeof(struct sockaddr_in);

    if((fd2 = accept(fd,(struct sockaddr *)&cell,&cell_len)) == -1) {
        printf("Error en accept() \n");
        exit(-1);
    }

    send_message(fd2, "Welcome\n");

    recv_message(fd2);
}

void connections_handler(vector<int> cells) {
    while(1) {
        thread fd2_thread(accept_conn);

        fd2_thread.join();

        close_cell(fd2);
    }
}

int main(int argc, char **argv) {
    if(argc > 1) {
        port = atoi(argv[1]);

        struct sockaddr_in server;

        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = INADDR_ANY;
        bzero(&(server.sin_zero),8);

        if((fd=socket(AF_INET,SOCK_STREAM,0)) < 0) {
            perror("Error de apertura");
            exit(-1);
        }

        if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr)) == -1) {
            printf("Error en bind() \n");
            exit(-1);
        }

        if(listen(fd,5) == -1) {
            printf("Error en listen() \n");
            exit(-1);
        }

        thread conn_handler(connections_handler,cells);

        conn_handler.join();
    }

    else {
        printf("ERROR\n");
    }

    return 0;
}