// mi si compila sul w7 con
// gcc UDP_server_minimo_crossplatf.c -lws2_32 -o UDP_server_minimo_crossplatf.exe
// su linux niente -lws2_32
// gcc UDP_server_minimo_crossplatf.c -o UDP_server_minimo_crossplatf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// questa sezione ifdef e la seguente sono necessarie per trattare diversamente, ove necessario, i socket tra windows e linux
#ifdef _WIN32 // qui perché windows usa nomi diversi per le biblioteche che implementano i socket
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

#define PORT 7890 // bada che porta TCP e UDP sono spazi separati, posso avere un server tcp e udp su stesso numero di porta
#define BUFFER_SIZE 1024

// e qui perché windows vuole una inizializzazione e una pulizia finale dei socket che linux non richiede (e alle chiamate faccio rispondere funzioni vuote)
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

// AGGIUNTE DA ME
// The expected greeting from a new client (or which already played and won)
#define EXPECTED_GREETING "salute, o mio servo"
#define MSG_GUESS_TOO_BIG "Error: Guessed number is too large!"
#define MAX_PENDING_CLIENTS 256
#define MSG_MAX_PENDING_CLIENTS_REACHED "Error: Too many pending 'sessions' for now - try again later"

typedef struct addrAndPortList
{
  char addr[INET_ADDRSTRLEN];
  unsigned short port;
} addrAndPortList;

int findInClientsList(addrAndPortList *clientsList, int pendingClientsCount, char *clientAddress, int clientPort);
int str_to_int(const char *str);

// MAIN FUNCTION
int main()
{
  int sockfd;                           // il file descriptor (da cui fd) del socket
  char buffer[BUFFER_SIZE];             // un array di caratteri dove i dati oggetto della comunicazione verranno memorizzati
  struct sockaddr_in servaddr, cliaddr; // bisogna anche riservare dentro al programma
  // - una struttura in memoria a cui bind-are, "legare" il socket, che ricordiamo è gestito dal "livello di trasporto", aka dal nostro punto di vista, dal SO, fuori dal nostro programma, ed è servaddr;
  // - e una per il client, dove verranno memorizzati l'indirizzo e la porta dell'entità che ha inviato il messaggio, che è cliaddr
  int len = sizeof(cliaddr);

  init_winsock(); // Initialize Winsock for Windows

  // Creo il socket con la sua "primitiva"
  sockfd = socket(AF_INET, SOCK_DGRAM, 0); // AF_INET indica che vogliamo usare IPv4, SOCK_DGRAM per il datagramma UDP e 0 che vogliamo il protocollo standard del datagram
  if (sockfd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr)); // pulizia preventiva della struttura
  servaddr.sin_family = AF_INET;          //  IPv4, repetita juvant
  servaddr.sin_addr.s_addr = INADDR_ANY;  // indica che il server accetta connessioni da qualsiasi interfaccia di rete disponibile
  servaddr.sin_port = htons(PORT);        // htons sta per "Host TO Network Short": il numero di porta è a 16 bit, e tra architetture di processori e di rete non v'è garantita la stessa end-ian-ness, con htons deleghiamo la garanzia

  // Bind - altra primitiva
  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("Bind failed");
    cleanup_socket(sockfd);
    exit(EXIT_FAILURE);
  }

  // Variables for "ease of use"
  char clientAddress[INET_ADDRSTRLEN];
  unsigned short clientPort;

  // List of UDP "pending" clients still not concluded with a right number guess
  addrAndPortList clientsList [MAX_PENDING_CLIENTS];
  int pendingClientsCount = 0;
  // List of the randomly generated numbers each corresponding to a client
  int *clientsRandomNumber;
  // Contains the position of the current client in the list of clients
  int clientPosition;

  // fine della preparazione
  // ora si comunica. riceviamo con la primitiva recvfrom
  while (1)
  {
    ssize_t nBytesRecieved = recvfrom( // la recvfrom ritorna il numero di byte effettivamente letti dal socket. ssize_t di fatto è un tipo intero, tanto che dopo lo casto a int per print-arlo
        sockfd,
        buffer,
        BUFFER_SIZE - 1, // il -1 è per lasciare agio per il terminatore nullo (\0), importante se stiamo trattando il contenuto del buffer come una stringa
        0,               // opzioni per la ricezione. 0 è nessuna opzione speciale
        (struct sockaddr *)&cliaddr,
        &len); // dopo la chiamata, len sarà aggiornato con la dimensione effettiva dell'indirizzo del client dal quale è stato ricevuto il messaggio

    if (nBytesRecieved < 0)
    {
      perror("Receive failed");
      break;
    }

    buffer[nBytesRecieved] = '\0'; // piazziamo il terminatore di stringa

    // Salviamo i dati identificativi del client in delle variabili per una maggiore accessibilità
    clientPort = ntohs(cliaddr.sin_port);

    memset(clientAddress, 0, sizeof(clientAddress)); // pulizia preventiva della stringa
    inet_ntop(AF_INET, &cliaddr.sin_addr, clientAddress, INET_ADDRSTRLEN);

    // Mostro all'utente il messaggio del client
    printf("[Client %s:%hu]: %s\n", clientAddress, clientPort, buffer);

    // Looking for the client address and port in the list and behaving accordingly

    clientPosition = findInClientsList(clientsList, pendingClientsCount, clientAddress, clientPort);

    if (clientPosition >= 0) // If client is found in the clients list
    {
      // This client has already greeted this server - checking the message
      // the message should contain a number between 1 and 100 (both included)
      int clientGuess = str_to_int(buffer);
      if(clientGuess<1 || clientGuess>100){
        sendto(sockfd, MSG_GUESS_TOO_BIG, strlen(MSG_GUESS_TOO_BIG), 0, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
        continue;
      } else {
        if(clientGuess == )
      }
    } else if(pendingClientsCount >= MAX_PENDING_CLIENTS){
      // Too many pending clients - denying any new client
      sendto(sockfd, MSG_MAX_PENDING_CLIENTS_REACHED, strlen(MSG_MAX_PENDING_CLIENTS_REACHED), 0, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
    } else {
      if(clientsRandomNumber[clientPosition] == clientGuess){
        // Send success and remove from list
      } else {
        // Send not success
      }
    }

    if (nBytesRecieved == sizeof(EXPECTED_GREETING)) // Length check to save computational time if false
    {
      // Checking for string equality
      strcmp(buffer, EXPECTED_GREETING);
      // NOTE: strcmp runs through the string until \0 or a mismatch is found
      // this means that the buffer is safe to use since we've set the first character after the actual message to be '\0'
    }

    printf("Risposta al client: ");
  }

  cleanup_socket(sockfd);
  return 0;
}

// If it finds the client returns its position in the list
// Otherwise returns 0 if the client couldn't be found, if the list is empty or if the clientAddress is not the length of INET_ADDRSTRLEN
int findInClientsList(addrAndPortList *clientsList, int pendingClientsCount, char *clientAddress, int clientPort)
{
  // Checks for empty list
  if (pendingClientsCount == 0)
    return 0;

  // Checking for invalid client address
  if (sizeof(clientAddress) < INET_ADDRSTRLEN || sizeof(clientAddress) > INET_ADDRSTRLEN)
  {
    return 0;
  }

  // Checks for port
  for (int i = 0; i < pendingClientsCount; i++)
  {
    if (clientsList[i].port == clientPort)
    {
      if (strcmp(clientsList[i].addr, clientAddress) == 0)
        return i;
    }
  }

  return 0;
}

int str_to_int(const char *str)
{
  errno = 0;
  long result = strtol(str, NULL, 10);

  // Check for conversion errors
  if (errno == ERANGE)
  {
    perror("Errore: errore di conversione con strtol)");
    return 0; // Overflow or underflow
  }
  if (result > INT_MAX || result < INT_MIN)
  {
    perror("Errore: errore di conversione con strtol (out of int range)");
    return 0; // Out of int range
  }
  return (int)result;
}