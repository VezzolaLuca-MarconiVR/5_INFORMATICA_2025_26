// gcc TCP_client.c -lws2_32 -o TCP_client

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// Link con ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;
    char *sendbuf = "Hello from Winsock Client";
    char recvbuf[512];
    int iResult;

    // Inizializzazione Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup fallito\n");
        return 1;
    }

    // Creazione socket
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Errore socket: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configurazione server (IP e Porta)
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP Server
    clientService.sin_port = htons(8888);                   // Porta Server

    // Connessione al server
    if (connect(ConnectSocket, (SOCKADDR *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        printf("Connessione fallita: %ld\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Connesso al server.\n");

    // Invio dati
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    printf("Bytes inviati: %ld\n", iResult);

    // Chiusura connessione
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
