#include "utils.h"

int fd,fd2,cell_len,numbytes,port,cell_port;
string list;
vector<int> cells_connd;
vector<int> cells_qeue;
vector<thread> cells_thread;
int cells_matrix[3][3];
// vector<vector<int>> grid = {{0,0,0},{0,0,0},{0,0,0}};
int available_cells = 0;
int grid_side_size = 3;
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

// void available_cells_grid() {
//     for(int i = 0;i < grid.size();i++) {
//         for(int j = 0;j < grid[i].size();j++) {
//             if(grid[i][j] == 0) {
//                 available_cells ++;
//             }
//         }
//     }
// }

int read_sock(char str[], int sockect) {
    int status;
    status = recv(sockect, str, 2*100, 0);

    if (status == 0) {
        return -1;
    }
    if (status < 0) { 
        perror("ERROR WHILE RECEIVING");
        exit(1);
    }

    str[status] = '\0';
    printf("Recibido: %s\n",str);
    return 0;
}

void connd_cell_flow(int sock) {
    send_message(sock, "Bienvenido\n");

    recv_message(sock);

    int status;

    while(1) {
        status = read_sock(buf,sock);

        if(status != 0) {
            break;
        }
    }
}

void connections_handler() {
    while(1) {
        cout << "Connecting" << endl;

        struct sockaddr_in cell;

        cell_len = sizeof(struct sockaddr_in);

        if((fd2 = accept(fd,(struct sockaddr *)&cell,&cell_len)) == -1) {
            printf("ERROR WHILE ACCEPTING CONNECTION \n");
            exit(-1);
        }
        else {
            if (getsockname(fd, (struct sockaddr *)&cell, &cell_len) == -1)
                perror("ERROR WHILE GETHOSTBYNAME");
            else
                cell_port = ntohs(sin.sin_port);
                list = cell_port + ",";
                count<<list<< endl;
            
            cout << "ACCEPTED" << endl;
            cells_thread.push_back(thread(connd_cell_flow,fd2));
            
            // for(int i = 0; i < cells_thread.size(); i++) {
            //     cells_thread[i].join();
            // }
        }
    }

    // while(1) {
    //     if(cells_qeue.size() < grid_side_size) {
    //         cout << "Here" << endl;
    //         cells_qeue.push_back(1);
    //     }
    //     else {
    //         for(int i = 0;i < cells_qeue.size();i++) {
    //             cout << "Threading" << endl;
    //             cells_connd.push_back(1);
    //             cells_thread.push_back(thread(accept_conn));
    //         }
    //         cells_qeue.clear();
    //         for(int i = 0;i < cells_qeue.size();i++) {
    //             cout << "Threading Out" << endl;
    //             cells_thread[i].join();
    //             cells_thread.erase(cells_thread.begin());
    //         }
    //     }
    //     brake;
    // }
}

void add_conecciones(string list, int cells_matrix){
    

    int filas = 3;
    int columnas = 3;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            string delimitador = ",";
            size_t pos = 0;
            string objeto;
            while((pos = list.find(delimitador)) != 9)
            {
                objeto = list.substr(0, pos);
                cells_matrix[i][j] = objeto;
                
                list.erase(0, pos + delimitador.length());
            }
        }
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

        connections_handler();
    }

    else {
        printf("ERROR\n");
    }

    return 0;
}