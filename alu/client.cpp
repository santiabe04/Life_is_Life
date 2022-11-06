#include <string>
#include <iostream>
#include <thread>
#include "header.h"

using namespace std;


// Asumiendo servidor en ip local, y dado un puerto, establece una conexion
// con el destino retornando un socket en estado conectado en caso de exito
int connect_socket(int port)
{
   if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) { // Le ponemos un nombre a la conexion o al socket que vamos a usar posteriormente
        perror("creando socket");
        exit(1);
    }

    /* Establecer la dirección a la cual conectarse. */
    remote.sin_family = AF_INET; // Asignacion del protocolo
    remote.sin_port = htons(port); // Asignacion del puerto
    inet_pton(AF_INET, "127.0.0.1", &(remote.sin_addr));

    /* Conectarse. */
    int s = connect(socket_fd, (struct sockaddr *)&remote, sizeof(remote)); // Nos conectamos al host, teniendo socket_fd que viene de cuando lo creamos
    if ( s == -1) {
        perror("conectandose");
        exit(1);
    }
}


// Dada una lista de puertos de vecinos, conecta el cliente con cada vecino
// agregando cada socket al vector de sockets
void con2neigh(string list, vector<int>& sockets)
{
    int posInit = 0;
    int posFound = 0;
    string splitted;
    string pattern = ',';
    int objectInt;

    while(posFound >= 0){
         posFound = list.find(pattern, posInit);
         splitted = str.substr(posInit, posFound - posInit);
         posInit = posFound + 1;
         int objectInt = stoi(splitted);
         socket = connect_socket(objectInt);
         sockets.push_back(socket);
    }
 }

// Dado el estado actual de la celula y el estado de los vecinos en una ronda
// computa el nuevo estado de la celula segun las reglas del juego
bool set_state(bool alive, const vector<request>& cl)
{
    int count;
	for (int iterator = 0; iterator <= cl.size(); iterator++)
    {
        bool state = cl[iterator.msg[0]];
        
        if(state == 1){
            count += 1;
        }
        
        if(count < 2 || count > 3)
        {
            alive = false;
        }
        if(count == 2 || count == 3)
        {
            alive = true;
        }
        return alive;        
    }
}

int run_cell(int port)
{   
    char                buf[MENSAJE_MAXIMO+1];
    struct request      srv_req;
    int                 srv_socket, accepting_socket;
    // Definir estructuras para manejar los sockets
    // Sugerancia: Diferenciar los canales donde la celula publica su estado
    //             de los que usa para recibir estado de sus vecinos
  
    /* Conectarse al server */
    srv_socket = connect_socket(htons(port));

    /* Crear socket de escucha y permitir aceptar conexiones concurrentemente */
    int lsn_port = port/* TO DO*/ ;
    acc_sock_fd = srv_socket /* TO DO*/
    set_acc_socket(lsn_port,acc_sock_fd)
    accept_conns(srv_socket) //falta el vector con vecinos que completa la funcion con2neigh
    
    /* TO DO*/
  
    /* Enviar msg al srv con el puerto de escucha */
    /* TO DO*/
    /* hacer un send */
    
    /* Obtener lista de vecinos inicial */
    /* hay una funcion sobre eso */
    /* TO DO*/

    /* Conectarse a los vecinos */
    /* con2neight */
    /* TO DO*/ 

    /* Enviar msg ready para el server */
    /* otro send */
    /* TO DO*/

    /* Comenzar juego */
    srand(getpid());
    char alive = random() % 2;
    while(1)
    {
        // Esperar request del srv
        get_request(&srv_req, srv_socket);
        if (strncmp(srv_req.type,"TICK",4) == 0)
        {
            /* Publicar estado*/
            /* hacer un send */
            /* TO DO*/

            /* Obtener estado de los vecinos*/
            /* TO DO*/

            /* Computar nuevo estado*/
            /* usar el set_state */
            /* TO DO*/

            /* Informar al srv nuevo estado*/
            /* hacer un send */
            /* TO DO*/
        }
        else if (strncmp(srv_req.type,"NEW",3) == 0)
        {
            /* Conectarse a los nuevos vecinos*/
            /* hacer eñ con2neigh*/
            /* TO DO*/

            /* Avisar con CLIENT_READY al srv*/
            /* server */
            /* TO DO*/

        } 

    }
    
    return;
}


int main(int argc, char* argv[]){
    int pid;
   /* Lanzar tantos procesos celulas como los indicados por argv[1]*/
    /* TO DO*/
    int socket_fd;
    int len;
    struct sockaddr_in  remote;
    struct hostent *hp;
    struct in_addr addr;
    // char buf[MENSAJE_MAXIMO];
    
    
}
