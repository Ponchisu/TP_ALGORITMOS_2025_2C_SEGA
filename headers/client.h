#ifndef CLIENTE_LIB_H_INCLUDED
#define CLIENTE_LIB_H_INCLUDED

#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

#define REQ_GET_RANKING 0
#define REQ_REGISTER_PLAYER 1
#define REQ_NEW_RUN 2

int init_winsock();
SOCKET connect_to_server(const char *server_ip, int port);
int send_request(SOCKET* sock, const char *request, char *response);
void close_connection(SOCKET* sock);

void sendPlayer(SOCKET* pSocket, const char* name, char* response);
void sendRun(SOCKET* pSocket, const char* name, int points, int moves, char* response);
void getRanking(SOCKET* pSocket, char* response);

#endif // CLIENTE_LIB_H_INCLUDED
