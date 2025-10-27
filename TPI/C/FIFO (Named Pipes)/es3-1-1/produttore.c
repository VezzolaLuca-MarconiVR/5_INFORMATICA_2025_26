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
    int myFifo = open("/tmp/myfifo", O_RDONLY);

    close(myFifo);

    return 0;
}