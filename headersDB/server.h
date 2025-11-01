#ifndef SERVIDOR_LIB_H_INCLUDED
#define SERVIDOR_LIB_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <winsock2.h>
#include "../headersDB/dbManager.h"
#include "../headersDB/cola.h"

#define PORT 12345

#define REQ_GET_RANKING 0
#define REQ_REGISTER_PLAYER 1
#define REQ_NEW_RUN 2

int init_winsock();
SOCKET create_server_socket();
void process_request(tDbManager* pDb, const char *request, char *response);
void run_server();

#endif // SERVIDOR_LIB_H_INCLUDED
