#include <iostream>
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
#include <semaphore.h>
#include <netdb.h>
#define MAX_MESSAGE  256

using namespace std;
struct request{
	char type[10];
	char msg[MAX_MESSAGE];
};
int numbytes;
char buf[100];
void send_message(int sock,const char* message);
void recv_message(int sock);
void close_conn(int sock);