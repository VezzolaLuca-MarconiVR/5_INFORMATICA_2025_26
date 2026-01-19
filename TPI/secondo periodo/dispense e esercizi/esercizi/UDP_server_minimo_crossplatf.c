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

  // fine della preparazione
  // ora si comunica. riceviamo con la primitiva recvfrom
  while (1)
  {
    ssize_t n = recvfrom( // la recvfrom ritorna il numero di byte effettivamente letti dal socket. ssize_t di fatto è un tipo intero, tanto che dopo lo casto a int per print-arlo
        sockfd,
        buffer,
        BUFFER_SIZE - 1, // il -1 è per lasciare agio per il terminatore nullo (\0), importante se stiamo trattando il contenuto del buffer come una stringa
        0,               // opzioni per la ricezione. 0 è nessuna opzione speciale
        (struct sockaddr *)&cliaddr,
        &len); // dopo la chiamata, len sarà aggiornato con la dimensione effettiva dell'indirizzo del client dal quale è stato ricevuto il messaggio

    if (n < 0)
    {
      perror("Receive failed");
      break;
    }

    buffer[n] = '\0'; // piazziamo il terminatore di stringa

    printf("Received %d bytes\n", (int)n); // mostro all'utente quanti byte ho ricevuto

    printf("Raw data: "); // e i byte effettivi in forma esadecimale
    for (int i = 0; i < n; i++)
    {
      printf("%02x ", (unsigned char)buffer[i]);
    }
    printf("\n");

    printf("Client: %s\n", buffer);

    
  } // e poi in forma di stringa

  cleanup_socket(sockfd);
  return 0;
}
