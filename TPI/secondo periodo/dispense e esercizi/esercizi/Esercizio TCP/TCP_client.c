// gcc TCP_client.c -lws2_32 -o TCP_client

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <sys/types.h>

#include "common_constants.h"

// Link con ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#ifndef ssize_t
#if defined(_WIN64)
typedef __int64 ssize_t;
#else
typedef long ssize_t;
#endif
#endif

int main()
{
  WSADATA wsaData;
  SOCKET ConnectSocket = INVALID_SOCKET;
  struct sockaddr_in clientService;
  ssize_t bytesRead = 0;
  boolean closeConnection = FALSE;
  char sendbuf[GERERAL_BUFF_SIZE];
  char recvbuf[GERERAL_BUFF_SIZE];
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
  clientService.sin_port = htons(SERVER_PORT);            // Porta Server

  // Connessione al server
  if (connect(ConnectSocket, (SOCKADDR *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
  {
    printf("Connessione fallita: %ld\n", WSAGetLastError());
    closesocket(ConnectSocket);
    WSACleanup();
    return 1;
  }

  printf("Connesso al server.\n");

  do
  {
    // Ask user to input string
    bytesRead = my_getline(&sendbuf, sizeof(sendbuf), stdin);
    if (bytesRead < 0)
    {
      // Getline error
      perror("Error: my_getline input invalid");
    }
    else
    {
      sendbuf[bytesRead - 1] = '\0';
      bytesRead = 0;
    }

    // Invio dati
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);

    printf("Waiting for server response...");

    bytesRead = (int)recv(ConnectSocket, recvbuf, (int)strlen(recvbuf), 0);

    recvbuf[bytesRead - 1] = '\0';

    // CHECK FOR SERVER RESPONSE (IN CODES)
  } while (closeConnection);

  // Chiusura connessione
  closesocket(ConnectSocket);
  WSACleanup();

  return 0;
}

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
  if (lineptr == NULL || n == NULL || stream == NULL)
  {
    errno = EINVAL;
    return -1;
  }
  size_t len = 0;
  char *buffer = *lineptr;
  size_t buffer_size = *n;
  if (buffer == NULL || buffer_size == 0)
  {
    buffer_size = 128;
    buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
      errno = ENOMEM;
      return -1;
    }
    *lineptr = buffer;
    *n = buffer_size;
  }
  int c;
  while ((c = fgetc(stream)) != EOF)
  { /* ensure room for char + terminating NUL */
    if (len + 1 >= buffer_size)
    { /* check for overflow */
      if (buffer_size > SIZE_MAX / 2)
      {
        errno = ENOMEM;
        return -1;
      }
      size_t new_size = buffer_size * 2;
      char *new_buffer = realloc(buffer, new_size);
      if (new_buffer == NULL)
      {
        errno = ENOMEM; /* keep original buffer intact; caller still owns it */
        return -1;
      }
      buffer = new_buffer;
      buffer_size = new_size;
      *lineptr = buffer;
      *n = buffer_size;
    }
    buffer[len++] = (char)c;
    if (c == '\n')
      break;
  }
  if (len == 0 && c == EOF)
  {
    return -1; /* no data read, EOF */
  }
  buffer[len] = '\0';
  return (ssize_t)len;
}
