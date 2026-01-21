// mi si compila sul w7 con
// gcc UDP_client_minimo_crossplatf.c -lws2_32 -o UDP_client_minimo_crossplatf.exe
// su linux niente -lws2_32
// gcc UDP_client_minimo_crossplatf.c -o UDP_client_minimo_crossplatf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Link with Ws2_32.lib
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

#ifndef ssize_t
#if defined(_WIN64)
typedef __int64 ssize_t;
#else
typedef long ssize_t;
#endif
#endif

#define PORT 7890
#define SERVER_IP "127.0.0.1"
#define GREETING_MESSAGE "salute, o mio servo"

#define BUFFER_SIZE 1024

#ifdef _WIN32
void init_winsock()
{
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void cleanup_socket(int sockfd)
{
  closesocket(sockfd);
  WSACleanup();
}
#else
#define init_winsock()                       // No-op for Unix
#define cleanup_socket(sockfd) close(sockfd) // Cleanup for Unix
#endif

// per i commenti, vedi il server, qua c'è poco d'altro e si può intuire
int main()
{
  int sockfd;
  struct sockaddr_in servaddr;

  int addrLen = sizeof(servaddr);

  char buffer[BUFFER_SIZE];

  init_winsock(); // solo per win

  // Create socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Server address
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

  // Send message
  sendto(sockfd, (const char *)GREETING_MESSAGE, strlen(GREETING_MESSAGE),
         0, (const struct sockaddr *)&servaddr,
         sizeof(servaddr));
  printf("Message sent to the server.\n");

  while (1)
  {
    ssize_t nBytesRecieved = recvfrom( // la recvfrom ritorna il numero di byte effettivamente letti dal socket. ssize_t di fatto è un tipo intero, tanto che dopo lo casto a int per print-arlo
        sockfd,
        buffer,
        BUFFER_SIZE - 1, // il -1 è per lasciare agio per il terminatore nullo (\0), importante se stiamo trattando il contenuto del buffer come una stringa
        0,               // opzioni per la ricezione. 0 è nessuna opzione speciale
        (struct sockaddr *)&servaddr,
        &addrLen); // dopo la chiamata, len sarà aggiornato con la dimensione effettiva dell'indirizzo del client dal quale è stato ricevuto il messaggio

    printf("[Server]: %s", buffer);
  }

  cleanup_socket(sockfd); // win only
  return 0;
}