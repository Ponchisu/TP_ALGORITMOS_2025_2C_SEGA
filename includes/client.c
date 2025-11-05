#include "../headers/client.h"

int init_winsock() {
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET connect_to_server(const char *server_ip, int port) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        closesocket(sock);
        return INVALID_SOCKET;
    }

    return sock;
}

int send_request(SOCKET* sock, const char *request, char *response) {
    if (send(*sock, request, strlen(request), 0) < 0) {
        return -1;
    }

    int bytes_received = recv(*sock, response, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0) {
        return -1;
    }

    response[bytes_received] = '\0';
    return 0;
}

void close_connection(SOCKET* sock) {
    closesocket(*sock);
    WSACleanup();
}


void sendPlayer(SOCKET* pSocket, const char* name, char* response) {
    char buffer[BUFFER_SIZE];

    snprintf(buffer, BUFFER_SIZE, "%d %s", REQ_REGISTER_PLAYER, name);
    send_request(pSocket, buffer, response);
}

void sendRun(SOCKET* pSocket, const char* name, int points, int moves, char* response) {
    char buffer[BUFFER_SIZE];

    snprintf(buffer, BUFFER_SIZE, "%d %s|%d|%d", REQ_NEW_RUN, name, points, moves);
    send_request(pSocket, buffer, response);
}

void getRanking(SOCKET* pSocket, char* response) {
    char buffer[BUFFER_SIZE];

    snprintf(buffer, BUFFER_SIZE, "%d NULL", REQ_GET_RANKING);
    send_request(pSocket, buffer, response);
}
