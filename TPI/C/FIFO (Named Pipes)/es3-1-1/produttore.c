#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

/*
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
    const char *pipe_path = "/tmp/mypipe";

    unlink(pipe_path);

    if(mkfifo(pipe_path, 0666) == -1) {
        perror("Errore nella creazione della FIFO!");
        return 0;
    }

    int myFifo = open(pipe_path, O_WRONLY); // Apre la FIFO (ritorna 0 se riesce, -1 in caso di errore)

    if (myFifo == -1)
    {
        printf("Erroe nell'apertura del FIFO!");
        return 0;
    }

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
        printf("SLEPT 1 SEC\n");
        write(myFifo, listptr[i], sizeof(listptr[i]));
        printf("%d", (int)sizeof(listptr[i]));
    }

    /* free allocated memory */
    for (int i = 0; i < LIST_SIZE; i++)
        free(listptr[i]);

    unlink(pipe_path);

    return 0;
}
