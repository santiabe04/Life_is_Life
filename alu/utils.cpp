#include "header.h"

using namespace std;

int s, s1;
struct sockaddr_in local;
struct sockaddr_in remote;
char buf[MENSAJE_MAXIMO];
struct hostent *hp;
struct in_addr addr;

// Un regalito, puede que quieran modificarla
// Dado un arreglo de char str y un socket descriptor s, hace una lectura
// bloqueante sobre s y llena el buffer str con los bytes leídos.
int read_sock(char str[], int s) 
{
    int n;
    n = recv(s, str, 2*MENSAJE_MAXIMO, 0);

    if (n == 0) 
        return -1;
    if (n < 0) { 
        perror("recibiendo");
        exit(1);
    }
    str[n] = '\0';
    printf("%d\n",n);
    printf("recibi: %s\n",str);
    return 0;
}


// Dado un puntero a un request req y un socket s, recibe una request en s y la 
// almacena en req. La funcion es bloqueante
void get_request(struct request* req, int s)
{
    int r;
    r = recv(s, req, sizeof(req), 0);  
}

// Dado un vector de enteros que representan socket descriptors y un request,
// envía a traves de todos los sockets la request.
void broadcast(vector<int>& sockets, struct request* req)
{ 
    for (int i = 0; i <= sockets.size(); i++)
    {
        int s = send(sockets[i], req, sizeof(struct request* req), 0); 
    }
}

// Por siempre, acepta conexiones sobre un socket s en estado listen y 
// agrega los sockets asociados al vector v.
void accept_conns(int s, vector<int>& v)
{
    int t = sizeof(remote);
    for (int i = 0; i <= v.size(); i++)
    {
        s1 = accept(s, (struct sockaddr*) &remote, (socklen_t*) &t);
    }
}
// Dado un puerto lsn_port devuelve un socket en estado listen asociado
// a todas las interfaces de red local y a ese puerto (ej 127.0.0.1:lsn_port)
int set_acc_socket(int lsn_port)
{
    local.sin_family = AF_INET;
    local.sin_port = htons(lsn_port);
    inet_pton(AF_INET, "127.0.0.1", &(local.sin_addr));

    bind(s, (struct sockaddr *)&local, sizeof(local));

    return s;
}

// Setea un socket al modo nobloqueante
static int nonblockingsocket(int s)
{
    int flags;

    if ((flags = fcntl(s, F_GETFL)) == -1)
        return -1;

    return fcntl(s, F_SETFL, flags | O_NONBLOCK);
}
