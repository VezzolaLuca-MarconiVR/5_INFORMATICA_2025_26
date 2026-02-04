// gcc TCP_server.c -lws2_32 -o TCP_server

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#include <time.h>

#include "common_constants.h"

#pragma comment(lib, "ws2_32.lib") // Collega la libreria WinSock

#define MAX_CLIENTS 10

// Checks if a string contains "bad" characters (not just standard ASCII letters)
boolean isBadString(char str[], size_t len);

// Funzione gestore per ogni client (thread)
DWORD WINAPI ClientHandler(LPVOID lpParam)
{
  SOCKET clientSocket = *(SOCKET *)lpParam;
  char buffer[GENERAL_BUFF_SIZE];
  int bytesReadFromBuffer;

  boolean closeConnection = FALSE;

  char partialString[MAX_FINAL_STRING_LENGTH];
  size_t partialStringLength = 0;
  size_t finalStringLength = 0;

  srand(time(NULL));
  finalStringLength = rand() % MAX_FINAL_STRING_LENGTH + 1;

  printf("Thread client creato.\n");

  // Main cicle for constructing user string
  do
  {
    // Ricevi dati dal client
    bytesReadFromBuffer = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReadFromBuffer > 0)
    {
      buffer[bytesReadFromBuffer] = '\0';
      printf("Client dice: %s", buffer);
      strncpy(partialString, buffer, bytesReadFromBuffer);
      partialStringLength = bytesReadFromBuffer;
    }

    if (bytesReadFromBuffer <= 0)
    {
      // "recv" function mulfunction
      perror("Errore: nessun byte ricevuto dal client. Messaggio ignorato.");
      continue;
    }

    if (isBadString(buffer, bytesReadFromBuffer))
    {
      // String is not valid - communicating to client
      send(clientSocket, MSG_ERROR_BAD_STRING, sizeof(MSG_ERROR_BAD_STRING), 0);
      // Eliminating any progress
      memset(partialString, 0, partialStringLength);
      continue;
    }

    // Check on the length of the partial string

    if (partialStringLength > finalStringLength)
    {
      // Il messaggio è troppo lungo per essere accettato
      send(clientSocket, MSG_ERROR_STRING_TOO_LONG, sizeof(MSG_ERROR_STRING_TOO_LONG), 0);
      // Comunica la lunghezza massima per la stringa
      char str[32];                                    // Stringa temporanea per il parsing
      int len = sprintf(str, "%d", finalStringLength); // Parsing - returns num of chars written
      send(clientSocket, str, len, 0);                 // Invio
      // Elimina i progressi raggiunti fino ad ora
      memset(partialString, 0, partialStringLength);
    }
    else if (partialStringLength < finalStringLength)
    {
      // Il messaggio è troppo corto
      send(clientSocket, MSG_ERROR_STRING_TOO_SHORT, sizeof(MSG_ERROR_STRING_TOO_SHORT), 0);
      // Comunica il numero di lettere mancanti e la stringa parziale
      char *str = malloc(32);
      int len = sprintf(str, "%d", finalStringLength - partialStringLength);

      // Inserting the delimiter
      str[len++] = ';';

      // Appending the partial string to the message
      for (size_t i = 0; i < sizeof(partialString); i++)
      {
        str[len + i] = partialString[i];
      }

      len += partialStringLength; // Updating the number of written characters

      send(clientSocket, str, len, 0);
    }
    else if (partialStringLength == finalStringLength)
    {
      // Il messaggio è della lunghezza giusta
      send(clientSocket, MSG_ERROR_STRING_TOO_SHORT, sizeof(MSG_ERROR_STRING_TOO_SHORT), 0);
    }

  } while (!closeConnection);

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
  serverAddr.sin_port = htons(SERVER_PORT);

  // Bind
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
  {
    printf("Bind fallito.");
    return 1;
  }

  // Listen
  listen(serverSocket, MAX_CLIENTS);
  printf("Server in ascolto sulla porta %d...\n", SERVER_PORT);

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

boolean isBadString(char str[], size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
      return TRUE;
  }
  return FALSE;
}