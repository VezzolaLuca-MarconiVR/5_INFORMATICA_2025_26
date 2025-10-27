#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

/*
Programma consumatore di consumatore e produttore
1. Produttore e Consumatore Semplice (Base)
Scrivere due programmi C, produttore.c e consumatore.c.
    • Il Produttore crea una FIFO chiamata "/tmp/dati_fifo" con permessi 0666.
    • Il Produttore invia 10 stringhe (es. "Messaggio X") al Consumatore, attendendo 1 secondo tra un invio e l’altro.
    • Il Consumatore apre la FIFO, legge le 10 stringhe e le stampa a video.
    • Il Produttore, dopo aver terminato, chiude la FIFO e usa unlink() per rimuoverla.
    • Istruzioni per l’alunno: Eseguire i due programmi in due terminali separati
*/

const int LIST_SIZE = 10;

int main()
{
    char myFifoPath[] = "/tmp/myfifo";
    mkfifo(myFifoPath, 0666);
    int myFifo = open(myFifoPath, O_WRONLY, O_NONBLOCK);

    char *listptr[LIST_SIZE];

    // Writes the list of messages to send
    for (int i = 0; i < LIST_SIZE; i++)
    {
        int length = snprintf(NULL, 0, "%d", i); // returns the lengh of the parsed string
        const char suffix[] = " CIAO\n";
        /* allocate space for the digits, the suffix and the terminating '\0' */
        listptr[i] = malloc(length + sizeof(suffix));
        if (listptr[i] == NULL)
        {
            perror("malloc");
            /* free previously allocated pointers */
            for (int j = 0; j < i; j++)
                free(listptr[j]);
            return 1;
        }
        /* build the final string */
        snprintf(listptr[i], length + sizeof(suffix), "%d%s", i, suffix);
    }

    // Writes one message per second on the FIFO
    for (int i = 0; i < LIST_SIZE; i++)
    {
        sleep(1);
        write(myFifo, listptr[i], sizeof(listptr[i]));
        printf("%d", (int)sizeof(listptr[i]));
    }

    /* free allocated memory */
    for (int i = 0; i < LIST_SIZE; i++)
        free(listptr[i]);

    return 0;
}