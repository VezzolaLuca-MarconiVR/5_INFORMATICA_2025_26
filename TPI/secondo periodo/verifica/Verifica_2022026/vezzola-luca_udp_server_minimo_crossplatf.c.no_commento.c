#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Include specifici per Windows e Linux
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

// Definizione di ssize_t per Windows o per un altro sistema che non ne dispone
#ifndef ssize_t
#if defined(_WIN64)
typedef __int64 ssize_t;
#else
typedef long ssize_t;
#endif
#endif

// La porta di questo server
#define PORT 7890
// Le dimensioni del buffer di ricezione
#define BUFFER_SIZE 1024

// Definisce le funzioni di inizializzazione e di eliminazione del socket per Windows (per Linux non serve la init, infatti è vuota)
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
#define init_winsock()
#define cleanup_socket(sockfd) close(sockfd)
#endif

// Includendo il file con i messaggi
#include "constants.h"

// Il numero massimo di client di cui possono essere mantenuti i dati relativi in memoria
#define MAX_PENDING_CLIENTS 256
// Una semplice struttura contenente solo indirizzo (di qualsiasi lunghezza standard) e la porta
typedef struct addrAndPortSimple
{
  char addr[INET_ADDRSTRLEN];
  unsigned short port;
} addrAndPortSimple;
// Una semplice struttura contenente i dati relativi al client
typedef struct clientSimple
{
  addrAndPortSimple aAndP;
  int rnd;     // Il numero che il client deve indovinare
  int subTime; // L'istante in cui il client è stato registrato nel sistema
} clientSimple;

// Funzione che trova la posizione di un client in una lista
int findInClientsList(clientSimple clientsList[], size_t len, int pendingClientsCount, char clientAddress[], int clientPort);
// Funzione che rimuove un client da una lista
void removeClientFromList(clientSimple clientList[], size_t *len, size_t idx);
// Funzione che aggiunge un client in una lista nel primo spazio libero
void addClientToList(clientSimple clientList[], size_t *len, clientSimple newClient);
// Funzione che fa il parsing di una stringa in intero
int str_to_int(const char *str);

// Funzione principale
int main()
{
  // Il File Descriptor del socket
  int sockfd;
  // Il buffer di ricezione
  char buffer[BUFFER_SIZE];
  // Le strutture contenenti i dati dei socket del server e del client per poterne fare le connessioni
  struct sockaddr_in servaddr, cliaddr;
  int addrLen = sizeof(cliaddr);
  // Inizializzazione di winsock (per Windows)
  init_winsock();
  // La creazione del socket (AF_INET => indirizzo IPv4, SOCK_DGRAM => utilizzo di datagrammi UDP)
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    // Errore nella creazione del socket
    perror("Socket creation failed");
    // Chiude il programma con un errore
    exit(EXIT_FAILURE);
  }
  // "Pulisce" la memoria che contiene l'indirizzo del server
  memset(&servaddr, 0, sizeof(servaddr));
  // "Setup" dei dati del server
  servaddr.sin_family = AF_INET; // Famiglia indirizzo: IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT); // Converte in formato adeguato per la struct la porta del server e la assegna

  // Effettua l'operazione di bind del socket in preparazione per l'ascolto
  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("Bind failed");
    cleanup_socket(sockfd);
    exit(EXIT_FAILURE);
  }

  // L'indirizzo del client corrente in stringa (INET_ADDRSTRLEN => lunghezza massima per l'IP in tutte le sue forme standard - 22)
  char clientAddress[INET_ADDRSTRLEN];
  // Il numero di porta del client corrente
  unsigned short clientPort;
  // La lista di client che non hanno concluso la loro "sessione"
  clientSimple clientsList[MAX_PENDING_CLIENTS];
  // Pulisce la zona di memoria contenente la lista di client
  memset(clientsList, 0, sizeof(clientsList));
  // Il numero di client che non hanno concluso la loro "sessione"
  int pendingClientsCount = 0;
  // la lunghezza parziale della lista di client (indica la posizione del punto più "in là" mai raggiunto nella lista - per motivi di efficienza a basso carico)
  size_t len = 0;
  // La posizione del client corrente
  int clientPosition = -1;
  // Il numero dato dal client corrente
  int clientGuess = -1;
  // Inizializza il seme della funzione rand basandosi sul tempo di runtime per generare i numeri da indovinare
  srand(time(NULL));
  while (1)
  {
    ssize_t nBytesRecieved = recvfrom( // Legge un datagramma dal buffer UDP della porta
        sockfd,
        buffer,                      // Dove scrive i dati ricevuti
        BUFFER_SIZE - 1,             // La lunghezza dei dati da leggere ("-1" toglie il terminatore)
        0,                           // Nessuna opzione di ricezione particolare
        (struct sockaddr *)&cliaddr, // Dove deposita i dati del client che ha inviato il datagramma
        &addrLen);
    if (nBytesRecieved < 0)
    {
      perror("Receive failed");
      break;
    }
    // Impone l'ultimo carattere a nullo per "far terminare" lì la stringa
    buffer[nBytesRecieved] = '\0';
    // Effettua il parsing della porta del client
    clientPort = ntohs(cliaddr.sin_port);
    // Pulisce l'area di memoria che conterrà l'indirizzo del client
    memset(clientAddress, 0, sizeof(clientAddress));
    // Effettua il parsing dell'indirizzo del client
    inet_ntop(AF_INET, &cliaddr.sin_addr, clientAddress, INET_ADDRSTRLEN);
    // Stampa a video l'indirizzo e la porta del client di cui ha appena letto il datagramma
    printf("[Client %s:%hu]: %s\n", clientAddress, clientPort, buffer);
    // Cerca se il client ha già una "pending session" o se è nuovo
    clientPosition = findInClientsList(clientsList, len, pendingClientsCount, clientAddress, clientPort);
    if (clientPosition >= 0)
    {
      // Client trovato nella lista
      if (strcmp(buffer, GREETING_MESSAGE) == 0)
      {
        // Il client ha reinviato il "saluto iniziale" corretto - la sua registrazione viene "rigenerata" (il "tempo" di iscrizione diventa questo stesso istante)
        clientsList[clientPosition].subTime = time(NULL);
        continue; // Passa al prossimo datagramma
      }
      clientGuess = str_to_int(buffer); // Ricava la "guess" del client
      if (clientGuess < 1 || clientGuess > 100)
      {
        // La "guess" è fuori dal range dei possibili valori - avvisa il client
        sendto(sockfd, MSG_GUESS_OUT_OF_RANGE, strlen(MSG_GUESS_OUT_OF_RANGE), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
        continue; // Passa al prossimo datagramma
      }
      else
      {
        // La "guess" è dentro il range dei possibili valori
        if (clientGuess > clientsList[clientPosition].rnd)
        {
          // La "guess" è troppo alta - avvisa il client
          sendto(sockfd, MSG_GUESS_TOO_HIGH, strlen(MSG_GUESS_TOO_HIGH), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
          continue; // Passa al prossimo datagramma
        }
        else if (clientGuess < clientsList[clientPosition].rnd)
        {
          // La "guess" è troppo bassa - avvisa il client
          sendto(sockfd, MSG_GUESS_TOO_LOW, strlen(MSG_GUESS_TOO_LOW), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
          continue; // Passa al prossimo datagramma
        }
        else
        {
          // La "guess" è azzeccata - avvisa il client (è implicita la sua rimozione dalla lista)
          sendto(sockfd, MSG_GUESS_MATCHED, strlen(MSG_GUESS_MATCHED), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
          // Rimuove dalla lista il client azzerandone tutti i dati
          removeClientFromList(clientsList, &len, clientPosition);
          // Decrementa il conteggio dei client
          pendingClientsCount--;
          continue; // Passa al prossimo datagramma
        }
      }
    }
    else
    {
      // Client NON trovato nella lista - è nuovo o è stato tolto dalla lista perhé era il più vecchio
      if (pendingClientsCount >= MAX_PENDING_CLIENTS)
      {
        // Ci sono troppi client in attesa - serve fare spazio per un client nuovo
        // L'indice del client "più vecchio" - candidato per la rimozione
        int idxOldest;
        // L'"età" del client più vecchio - per comparazione
        float oldestAge = 0;
        // L'"età" del client attuale nel ciclo
        int tempAge;
        // Trova la posizione del client con l'"età" maggiore
        for (size_t i = 0; i < len; i++)
        {
          if (clientsList[i].aAndP.addr[0] == '\0')
            continue;
          tempAge = difftime(time(NULL), clientsList[i].subTime);
          if (tempAge > oldestAge)
          {
            oldestAge = tempAge;
            idxOldest = i;
          }
        }
        // Toglie il client decretato il "più vecchio"
        removeClientFromList(clientsList, &len, idxOldest);
        // Decrementa il conteggio dei client
        pendingClientsCount--;
      }
      if (nBytesRecieved == strlen(GREETING_MESSAGE))
      {
        // Il client ha "salutato" correttamente
        if (strcmp(buffer, GREETING_MESSAGE) == 0)
        {
          // Si inizializza una nuova struttura temporanea per inserire il nuovo client nella lista
          clientSimple newCl;
          strcpy(newCl.aAndP.addr, clientAddress);
          newCl.aAndP.port = clientPort;
          newCl.subTime = time(NULL);
          newCl.rnd = rand() % 100 + 1;
          // Inserimento nella lista
          addClientToList(clientsList, &len, newCl);
          // Aumenta il conteggio dei client
          pendingClientsCount++;
          // Conferma la registrazione al client
          sendto(sockfd, MSG_REGISTERED, strlen(MSG_REGISTERED), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
          continue; // Passa al prossimo datagramma
        }
      }
      // Il client NON ha "salutato" correttamente - avvisarlo
      sendto(sockfd, MSG_INCORRECT_GREETING, strlen(MSG_INCORRECT_GREETING), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }
  }
  // "Pulisce" il File Descriptor del socket
  cleanup_socket(sockfd);
  // Chiude il programma
  return 0;
}

int findInClientsList(clientSimple clientsList[], size_t len, int pendingClientsCount, char clientAddress[INET_ADDRSTRLEN], int clientPort)
{
  if (pendingClientsCount == 0)
    // Non ci sono client registrati al momento, torna -1
    return -1;

  // Cerca il client nella lista
  for (size_t i = 0; i < len; i++)
  {
    if (clientsList[i].aAndP.port == clientPort)
      if (strcmp(clientsList[i].aAndP.addr, clientAddress) == 0)
        return i;
  }
  // Se non trova corrispondenze, torna -1
  return -1;
}

void removeClientFromList(clientSimple clientList[], size_t idx)
{
  // Pulisce la zona di memoria indicatagli
  memset(&clientList[idx], 0, sizeof(*clientList));
}

void addClientToList(clientSimple clientList[], size_t *len, clientSimple newClient)
{
  // Aumenta la "posizione ultima" mai scritta nella lista di client
  (*len)++;
  // Cerca il primo spazio libero ("a zero") nella lista
  for (size_t i = 0; i < *len; i++)
  {
    if (clientList[i].aAndP.addr[0] == '\0')
    {
      // Copia il client nella posizione vuota
      clientList[i] = newClient;
      return;
    }
  }
}

int str_to_int(const char *str)
{
  errno = 0;
  long result = strtol(str, NULL, 10); // Effettua il parsing in base 10 della stringa in intero
  if (errno == ERANGE)
  {
    perror("Errore: errore di conversione con strtol)");
    return 0;
  }
  if (result > INT_MAX || result < INT_MIN) // Conversione out of range per l'int
  {
    perror("Errore: errore di conversione con strtol (out of int range)");
    return 0;
  }
  // Ritorna il numero "parsato"
  return (int)result;
}
