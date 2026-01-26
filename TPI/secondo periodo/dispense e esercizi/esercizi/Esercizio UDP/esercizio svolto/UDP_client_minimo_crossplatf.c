// mi si compila sul w7 con
// gcc UDP_client_minimo_crossplatf.c -lws2_32 -o UDP_client_minimo_crossplatf.exe
// su linux niente -lws2_32
// gcc UDP_client_minimo_crossplatf.c -o UDP_client_minimo_crossplatf

#define _GNU_SOURCE
#include <errno.h>
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

// ADDED BY Luca
#include "constants.h"

#define BUFFER_SIZE 1024

int str_to_int(const char *str);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

// per i commenti, vedi il server, qua c'è poco d'altro e si può intuire
int main()
{
  int sockfd;
  struct sockaddr_in servaddr;

  int addrLen = sizeof(servaddr);

  char buffer[BUFFER_SIZE];
  buffer[0] = '\0';

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

  char *lastUserInput = malloc(16);
  if (!lastUserInput)
    abort();
  strcpy(lastUserInput, "new");

  size_t lUInSize = 0;
  ssize_t lUInRead;

  // MSG_REGISTERED recieved
  boolean mR = FALSE;
  // MSG_GUESS_MATCHED recieved
  boolean mGM = FALSE;
  // MSG_GUESS_TOO_LOW recieved
  boolean mGTL = FALSE;
  // MSG_GUESS_TOO_HIGH recieved
  boolean mGTH = FALSE;

  printf("\n***Info: type 'quit' at any time to exit the game***\n\n");

  while (strcmp(lastUserInput, "quit") != 0)
  {
    if (strcmp(lastUserInput, "new") == 0)
    {
      // Sending the request for a new "subscription" - or, if already in list, the renewal of the subscription time
      sendto(
          sockfd,
          GREETING_MESSAGE,
          strlen(GREETING_MESSAGE),
          0,
          (struct sockaddr *)&servaddr,
          sizeof(servaddr));

      strcpy(lastUserInput, "");
    }
    else
    {
      // Resetting the variables
      mR = FALSE;
      mGM = FALSE;
      mGTL = FALSE;
      mGTH = FALSE;

      ssize_t nBytesRecieved = recvfrom( // la recvfrom ritorna il numero di byte effettivamente letti dal socket. ssize_t di fatto è un tipo intero, tanto che dopo lo casto a int per print-arlo
          sockfd,
          buffer,
          BUFFER_SIZE - 1, // il -1 è per lasciare agio per il terminatore nullo (\0), importante se stiamo trattando il contenuto del buffer come una stringa
          0,               // opzioni per la ricezione. 0 è nessuna opzione speciale
          (struct sockaddr *)&servaddr,
          &addrLen); // dopo la chiamata, len sarà aggiornato con la dimensione effettiva dell'indirizzo del client dal quale è stato ricevuto il messaggio

      if (strcmp(buffer, MSG_INCORRECT_GREETING) == 0)
      {
        // Incorrect greeting
        perror("Error: greeting message incorrect\n");
        return 0;
      }

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
          // Guessed successfully
          printf("Esatto! Hai indovinato!\n\nGiocare ancora? (S/N): ");
          do
          {
            // Asking user if he wants to continue
            lUInRead = my_getline(&lastUserInput, &lUInSize, stdin);
            lastUserInput[lUInRead - 1] = '\0';
            if (lUInRead < 0)
            {
              // Getline error
              perror("Error: my_getline input invalid");
            }
            else if (strcmp(lastUserInput, "S") != 0 && strcmp(lastUserInput, "N") != 0)
            {
              printf("Inserire un numero intero: ");
            }

          } while (lUInRead <= 0 || strcmp(lastUserInput, "S") != 0 && strcmp(lastUserInput, "N") != 0);

          if (strcmp(lastUserInput, "S") == 0)
          {
            strcpy(lastUserInput, "new");
          }
          else
          {
            strcpy(lastUserInput, "quit");
          }
          continue;
        }
        else if (mGTL)
        {
          // Inform the user that the guess was too low
          printf("No, piu' alto!\n");
        }
        else if (mGTH)
        {
          // Inform the user that the guess was too high
          printf("No, piu' basso!\n");
        }

        do
        {
          // User inputs their guess
          printf("Prova a indovinare il numero (tra 1 e 100, entrambi inclusi): ");

          lUInRead = my_getline(&lastUserInput, &lUInSize, stdin);
          if (lUInRead >= 0)
          {
            // Removing the newline character before sending
            if (lastUserInput[lUInRead - 1] == '\n')
              lastUserInput[lUInRead - 1] = '\0';

            // Getline succeded
            sendto(
                sockfd,
                lastUserInput,
                strlen(lastUserInput),
                0,
                (struct sockaddr *)&servaddr,
                sizeof(servaddr));
          }
          else
          {
            // Getline error
            perror("Error: my_getline input invalid");
          }
        } while (lUInRead <= 0);
      }
      else if (strcmp(buffer, MSG_GUESS_OUT_OF_RANGE) == 0)
      {
        // Guess out of range [1; 100]
        printf("You must type a number between 1 and 100 (both included)!\n");
        strcpy(lastUserInput, "quit");
      }
    }
  }

  free(lastUserInput);

  cleanup_socket(sockfd); // win only
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