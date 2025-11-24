#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
Passaggio di Strutture Dati Modificare l’esercizio precedente per passare una struttura (es. struct record {int id; float valore;}),
non solo stringhe. Il Produttore deve inviare 5 record generati casual- mente. Il Consumatore riceve e stampa i campi di ciascun record.
*/

#define PIPE_PATH "/tmp/mypipe"
#define N_MESSAGES 5

int function(int id, float value)
{
    return
}

struct Record
{
    int id;
    float value;
};

int main()
{
    // CREAZIONE E APERTURA FIFO
    unlink(PIPE_PATH);

    if (mkfifo(PIPE_PATH, 0666) == -1)
    {
        perror("Errore nella creazione della FIFO!");
        return 1;
    }

    int fd = open(PIPE_PATH, O_WRONLY);
    if (fd == -1)
    {
        perror("Errore nell'apertura del FIFO!");
        return 1;
    }

    // CREAZIONE E POPOLAMENTO (randomico) DELLE STRUCT
    struct Record for (int i = 0; i < N_MESSAGES; i++)
    {
    }

    for (int i = 0; i < N_MESSAGES; i++)
    {
        sleep(1);
        write(fd, listptr[i], strlen(listptr[i])); // usa strlen
        printf("%s", listptr[i]);
    }

    for (int i = 0; i < N_MESSAGES; i++)
        free(listptr[i]);

    close(fd);
    unlink(PIPE_PATH); // rimuove la FIFO dopo l’uso

    printf("Produttore - OUT!\n");
    return 0;
}
