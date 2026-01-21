// mi si compila sul w7 con
// gcc UDP_server_minimo_crossplatf.c -lws2_32 -o UDP_server_minimo_crossplatf.exe
// su linux niente -lws2_32
// gcc UDP_server_minimo_crossplatf.c -o UDP_server_minimo_crossplatf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
#define MSG_CORRECTING_GREETING "Error: the first message to send to the server must be 'salute, o mio servo'"

typedef struct addrAndPortSimple
{
  char addr[INET_ADDRSTRLEN];
  unsigned short port;
} addrAndPortSimple;

typedef struct clientSimple
{
  addrAndPortSimple aAndP;
  int rnd;
  int birthTime;
} clientSimple;

int findInClientsList(clientSimple clientsList[], size_t len, int pendingClientsCount, char *clientAddress, int clientPort);
void removeClientFromList(clientSimple clientList[], size_t len, size_t idx);
void addClientToList(clientSimple clientList[], size_t len, clientSimple newClient);
int str_to_int(const char *str);

// MAIN FUNCTION
int main()
{
  int sockfd;                           // il file descriptor (da cui fd) del socket
  char buffer[BUFFER_SIZE];             // un array di caratteri dove i dati oggetto della comunicazione verranno memorizzati
  struct sockaddr_in servaddr, cliaddr; // bisogna anche riservare dentro al programma
  // - una struttura in memoria a cui bind-are, "legare" il socket, che ricordiamo è gestito dal "livello di trasporto", aka dal nostro punto di vista, dal SO, fuori dal nostro programma, ed è servaddr;
  // - e una per il client, dove verranno memorizzati l'indirizzo e la porta dell'entità che ha inviato il messaggio, che è cliaddr
  int addrLen = sizeof(cliaddr);

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
  clientSimple clientsList[MAX_PENDING_CLIENTS];
  // "cleaning the list"
  memset(clientsList, 0, sizeof(clientsList));
  int pendingClientsCount = 0;
  // The length of the clients list
  size_t len = 0;
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
        &addrLen); // dopo la chiamata, len sarà aggiornato con la dimensione effettiva dell'indirizzo del client dal quale è stato ricevuto il messaggio

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

    clientPosition = findInClientsList(clientsList, len, pendingClientsCount, clientAddress, clientPort);

    if (clientPosition >= 0) // If client is found in the clients list
    {
      // This client has already greeted this server - checking the message
      // the message should contain a number between 1 and 100 (both included)
      int clientGuess = str_to_int(buffer);
      if (clientGuess < 1 || clientGuess > 100)
      {
        sendto(sockfd, MSG_GUESS_TOO_BIG, strlen(MSG_GUESS_TOO_BIG), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
        continue;
      }
      else
      {
        if (clientsList[clientPosition].rnd == clientGuess)
        {
          // Send success and remove from list
        }
        else
        {
          // Send not success
        }
      }
    }
    else
    {
      // The client is new - saving its IPv4 address in the list and create and store its random number
      if (pendingClientsCount >= MAX_PENDING_CLIENTS)
      {
        // Too many pending clients - deleting the "oldest" client of the list
        int idxOldest;
        float oldestAge = 0;

        int tempAge;

        for (size_t i = 0; i < len; i++)
        {
          if (clientsList[i].aAndP.addr[0] == '\0') // Skips empty array cells
            continue;

          tempAge = difftime(time(NULL), clientsList[i].birthTime);
          if (tempAge > oldestAge)
          {
            oldestAge = tempAge;
            idxOldest = i;
          }
        }

        removeClientFromList(clientsList, len, idxOldest);
      }

      if (nBytesRecieved == sizeof(EXPECTED_GREETING)) // Length check to save computational time if false
      {
        // Checking for string equality
        // NOTE: strcmp runs through the string until \0 or a mismatch is found
        // this means that the buffer is safe to use since we've set the first character after the actual message to be '\0'
        if (strcmp(buffer, EXPECTED_GREETING) == 0)
        {
          // Copying the infos in a temporary struct
          clientSimple newCl;
          strcpy(newCl.aAndP.addr, clientAddress);
          newCl.aAndP.port = clientPort;
          newCl.birthTime = time(NULL);
          newCl.rnd = rand() % 100 + 1;
          addClientToList(clientsList, len, newCl);

          // Saying to the client the success of the "game registration"
          sendto(sockfd, MSG_CORRECTING_GREETING, strlen(MSG_CORRECTING_GREETING), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));

          continue;
        }
      }

      // Sending correction about first message
      sendto(sockfd, MSG_CORRECTING_GREETING, strlen(MSG_CORRECTING_GREETING), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }

    printf("Risposta al client: %s", buffer);
  }

  cleanup_socket(sockfd);
  return 0;
}

// If it finds the client returns its position in the list
// Otherwise returns -1 if the client couldn't be found, if the list is empty or if the clientAddress is not the length of INET_ADDRSTRLEN
int findInClientsList(clientSimple clientsList[], size_t len, int pendingClientsCount, char *clientAddress, int clientPort)
{
  // Checks for empty list
  if (pendingClientsCount == 0)
    return -1;

  // Checking for invalid client address
  if (sizeof(clientAddress) < INET_ADDRSTRLEN || sizeof(clientAddress) > INET_ADDRSTRLEN)
  {
    return -1;
  }

  // Checks for port
  for (size_t i = 0; i < len; i++)
  {
    if (clientsList[i].aAndP.port == clientPort)
      if (strcmp(clientsList[i].aAndP.addr, clientAddress) == 0)
        return i;
  }

  return -1;
}

void removeClientFromList(clientSimple clientList[], size_t len, size_t idx)
{
  memset(&clientList[idx], 0, sizeof(*clientList));
}

void addClientToList(clientSimple clientList[], size_t len, clientSimple newClient)
{
  // Looks for first empty space to save the new client data into
  for (size_t i = 0; i < len; i++)
  {
    if (clientList[i].aAndP.addr[0] == '\0')
    {
      // The address is set to null - this "cell" is empty - overwrite
      clientList[i] = newClient;
      return;
    }
  }
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