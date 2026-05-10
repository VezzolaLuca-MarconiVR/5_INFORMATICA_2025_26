#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
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

// La porta del server
#define PORT 7890
// L'IPv4 del server
#define SERVER_IP "127.0.0.1"

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

// Le dimensioni del buffer di ricezione
#define BUFFER_SIZE 1024

// Funzione che fa il parsing di una stringa in intero
int str_to_int(const char *str);
// Getline personalizzata (windows non la prevede)
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

// Funzione principale
int main()
{
  // Il File Descriptor del socket
  int sockfd;
  // Il socket del server
  struct sockaddr_in servaddr;
  int addrLen = sizeof(servaddr);
  // Il buffer di ricezione
  char buffer[BUFFER_SIZE];
  // "Svuota" subito il buffer
  buffer[0] = '\0';
  // Inizializza winsock (solo per Windows)
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
  servaddr.sin_family = AF_INET;                   // Famiglia indirizzo: IPv4
  servaddr.sin_port = htons(PORT);                 // Converte in formato adeguato per la struct la porta del server e la assegna
  servaddr.sin_addr.s_addr = inet_addr(SERVER_IP); // Converte in formato adeguato per la struct l'indirizzo del server e la assegna

  // Alloca la memoria per contenere l'input dell'utente
  char *lastUserInput = malloc(16);
  if (!lastUserInput) // Allocazione non andata a buon fine
    abort();
  // Imposta l'ultimo input a "new"
  strcpy(lastUserInput, "new");
  // La lunghezza dell'input dell'utente
  size_t lUInSize = 0;
  // Storage per il return della getline personalizzata
  ssize_t lUInRead;

  // Il messaggio ricevuto è MSG_REGISTERED
  boolean mR = FALSE;
  // Il messaggio ricevuto è MSG_GUESS_MATCHED
  boolean mGM = FALSE;
  // Il messaggio ricevuto è MSG_GUESS_TOO_LOW
  boolean mGTL = FALSE;
  // Il messaggio ricevuto è MSG_GUESS_TOO_HIGH
  boolean mGTH = FALSE;

  // Info per l'utente
  printf("\n***Info: type 'quit' at any time to exit the game***\n\n");

  // Finchè l'utente (o il programma stesso) non scrive "quit" continua il gioco
  while (strcmp(lastUserInput, "quit") != 0)
  {
    // Il programma è appena stato avviato - oppure si è "riavviato" da solo
    if (strcmp(lastUserInput, "new") == 0)
    {
      // Invia il "saluto" al server
      sendto(
          sockfd,
          GREETING_MESSAGE,
          strlen(GREETING_MESSAGE),
          0,
          (struct sockaddr *)&servaddr,
          sizeof(servaddr));
      // Svuota l'ultimo input dell'utente
      strcpy(lastUserInput, "");
    }
    else
    {
      // Reimposta tutti i "flag"
      mR = FALSE;
      mGM = FALSE;
      mGTL = FALSE;
      mGTH = FALSE;
      // Riceve il messaggio del server
      ssize_t nBytesRecieved = recvfrom(
          sockfd,
          buffer,
          BUFFER_SIZE - 1,
          0,
          (struct sockaddr *)&servaddr,
          &addrLen);
      if (strcmp(buffer, MSG_INCORRECT_GREETING) == 0)
      {
        // Il "saluto" inviato era errato
        perror("Error: greeting message incorrect\n");
        return 0; // Chiude il programma
      }

      // Trova quale dei codici ha inviato il server
      mR = strcmp(buffer, MSG_REGISTERED) == 0;
      if (!mR)
      {
        mGM = strcmp(buffer, MSG_GUESS_MATCHED) == 0;
        if (!mGM)
        {
          mGTL = strcmp(buffer, MSG_GUESS_TOO_LOW) == 0;
          if (!mGTL)
          {
            mGTH = strcmp(buffer, MSG_GUESS_TOO_HIGH) == 0;
          }
        }
      }
      if (mR || mGM || mGTL || mGTH)
      {
        if (mGM)
        {
          // Il client ha indovinato
          printf("Esatto! Hai indovinato!\n\nGiocare ancora? (S/N): ");

          // Ciclo per chiedere all'utente se vuole giocare ancora
          do
          {
            lUInRead = my_getline(&lastUserInput, &lUInSize, stdin);
            lastUserInput[lUInRead - 1] = '\0';
            if (lUInRead < 0)
            {
              perror("Error: my_getline input invalid");
            }
            else if (strcmp(lastUserInput, "S") != 0 && strcmp(lastUserInput, "N") != 0)
            {
              printf("Inserire un numero intero: ");
            }
          } while (lUInRead <= 0 || strcmp(lastUserInput, "S") != 0 && strcmp(lastUserInput, "N") != 0);
          if (strcmp(lastUserInput, "S") == 0)
          {
            // L'utente vuole giocare ancora - "new"
            strcpy(lastUserInput, "new");
          }
          else
          {
            // L'utente NON vuole giocare ancora - "quit"
            strcpy(lastUserInput, "quit");
          }
          continue; // Va avanti (prosegue il gioco o esce)
        }
        else if (mGTL)
        {
          // La "guess" era troppo bassa
          printf("No, più alto!\n");
        }
        else if (mGTH)
        {
          // La "guess" era troppo alta
          printf("No, più basso!\n");
        }

        // Continua se l'input dell'utente è nullo
        do
        {
          // (Ri)prova a indovinare il numero
          printf("Prova a indovinare il numero (tra 1 e 100, entrambi inclusi): ");
          lUInRead = my_getline(&lastUserInput, &lUInSize, stdin);
          if (lUInRead >= 0)
          {
            if (lastUserInput[lUInRead - 1] == '\n')
              lastUserInput[lUInRead - 1] = '\0'; // Sostituisce il carattere nullo alla fine della stringa
            sendto(                               // Invia il messaggio appena scritto dall'utente al server
                sockfd,
                lastUserInput,
                strlen(lastUserInput),
                0,
                (struct sockaddr *)&servaddr,
                sizeof(servaddr));
          }
          else
          {
            perror("Error: my_getline input invalid");
          }
        } while (lUInRead <= 0);
      }
      // Il numero è fuori range
      else if (strcmp(buffer, MSG_GUESS_OUT_OF_RANGE) == 0)
      {
        printf("You must type a number between 1 and 100 (both included)!\n");
        strcpy(lastUserInput, "quit");
      }
    }
  }
  // Libera lo spazio allocato per l'input del client
  free(lastUserInput);
  // "Pulisce" il socket
  cleanup_socket(sockfd);
  return 0;
}

int str_to_int(const char *str)
{
  errno = 0;
  long result = strtol(str, NULL, 10);
  if (errno == ERANGE)
  {
    perror("Errore: errore di conversione con strtol)");
    return 0;
  }
  if (result > INT_MAX || result < INT_MIN)
  {
    perror("Errore: errore di conversione con strtol (out of int range)");
    return 0;
  }
  return (int)result;
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
  {
    if (len + 1 >= buffer_size)
    {
      if (buffer_size > SIZE_MAX / 2)
      {
        errno = ENOMEM;
        return -1;
      }
      size_t new_size = buffer_size * 2;
      char *new_buffer = realloc(buffer, new_size);
      if (new_buffer == NULL)
      {
        errno = ENOMEM;
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
    return -1;
  }
  buffer[len] = '\0';
  return (ssize_t)len;
}
