#include "../headersDB/server.h"


// Implementación de funciones públicas
int init_winsock() {
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET create_server_socket() {
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        closesocket(s);
        return INVALID_SOCKET;
    }

    if (listen(s, 1) == SOCKET_ERROR)
    {
        closesocket(s);
        return INVALID_SOCKET;
    }

    return s;
}

void process_request(tDbManager* pDb, const char *request, char *response) {
    int operation;
    char info[BUFFER_SIZE];
    sscanf(request, "%d %[^\n]", &operation, info);
    printf("%d\n", operation);
    switch (operation) {
        case REQ_GET_RANKING:
            Database_getRanking(pDb, response);
            break;
        case REQ_REGISTER_PLAYER:
            DataBase_registerPlayer(pDb, info, response);
            break;
        case REQ_NEW_RUN:
            Database_registerNewRun(pDb, info, response);
            break;
        default:
            puts("Codigo desconocido");
            break;
    }
}

void run_server() {
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    int bytes_received;

    struct sockaddr_in client_addr;
    int client_addr_size;
    int err;
    char peticion[BUFFER_SIZE];

    tDbManager dataBase;
    if(!DataBase_init(&dataBase)) {
        fprintf(stderr, "Error al inicializar base de datos\n");
        return;
    }

    tCola cola;

    if (init_winsock() != 0) {
        printf("Error al inicializar Winsock\n");
        return;
    }

    SOCKET server_socket = create_server_socket();
    if (server_socket == INVALID_SOCKET) {
        printf("Error al crear socket del servidor\n");
        WSACleanup();
        return;
    }

    printf("Servidor escuchando en puerto %d...\n", PORT);
    client_addr_size = sizeof(client_addr);

    SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_socket == INVALID_SOCKET) {
        printf("Error en accept()\n");
        closesocket(server_socket);
        WSACleanup();
        return;
    }

    printf("Cliente conectado.\n");
    Cola_create(&cola);

    while (1) {
        // Intentar recibir un mensaje
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("[RX] Recibido: %s\n", buffer);

            // Encolamos el mensaje recibido
            Cola_put(&cola, buffer, BUFFER_SIZE);
        }
        else if (bytes_received == 0) {
            // El cliente ha cerrado la conexión de forma ordenada
            printf("Cliente desconectado (recv == 0). Saliendo del bucle.\n");
            break;
        }
        else { /* bytes_received == SOCKET_ERROR */
            err = WSAGetLastError();        // Ver que es esto
            if (err == WSAEWOULDBLOCK)
            {
                // No hay datos en modo no-bloqueante.
                // Simplemente seguimos el bucle y procesamos la cola.
            }
            else
            {
                // Error serio, salimos
                printf("Error en recv(): %d. Saliendo.\n", err);
                break;
            }
        }

        // Procesar mensajes pendientes en la cola
        while (!Cola_isEmpty(&cola)) {
            // Desencolar la peticion
            Cola_takeOut(&cola, peticion, BUFFER_SIZE);

            // Procesar la peticion
            printf("[PROC] Procesando: %s\n", peticion);
            process_request(&dataBase, peticion, response);

            // Enviar la respuesta al cliente (si es necesario)
            send(client_socket, response, strlen(response), 0);

            printf("[TX] Enviado: %s\n", response);
        }

        Sleep(100);
    }

    DataBase_updateIndx(&dataBase);

    Cola_clean(&cola);
    printf("Conexion cerrada.\n");
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
}