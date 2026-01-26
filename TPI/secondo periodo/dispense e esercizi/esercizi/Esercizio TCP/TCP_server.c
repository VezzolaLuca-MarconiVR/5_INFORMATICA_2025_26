// gcc TCP_server.c -lws2_32 -o TCP_server

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") // Collega la libreria WinSock

#define PORT 8888
#define MAX_CLIENTS 10

// Funzione gestore per ogni client (thread)
DWORD WINAPI ClientHandler(LPVOID lpParam)
{
    SOCKET clientSocket = *(SOCKET *)lpParam;
    char buffer[1024];
    int bytesRead;

    printf("Thread client creato.\n");

    // Ricevi dati dal client
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[bytesRead] = '\0';
        printf("Client dice: %s", buffer);
        send(clientSocket, buffer, bytesRead, 0); // Eco al client
    }

    printf("Client disconnesso.\n");
    closesocket(clientSocket);
    return 0;
}

int main()
{
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    // Inizializza WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Fallito. Codice errore: %d", WSAGetLastError());
        return 1;
    }

    // Crea socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Bind fallito.");
        return 1;
    }

    // Listen
    listen(serverSocket, MAX_CLIENTS);
    printf("Server in ascolto sulla porta %d...\n", PORT);

    while (1)
    {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        printf("Nuova connessione accettata.\n");

        // Crea un thread per gestire il client
        CreateThread(NULL, 0, ClientHandler, &clientSocket, 0, NULL);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
