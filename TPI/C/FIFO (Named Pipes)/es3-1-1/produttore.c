#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

const int LIST_SIZE = 10;

int main()
{
    const char *pipe_path = "/tmp/mypipe";

    unlink(pipe_path);

    if (mkfifo(pipe_path, 0666) == -1)
    {
        perror("Errore nella creazione della FIFO!");
        return 1;
    }

    int myFifo = open(pipe_path, O_WRONLY);
    if (myFifo == -1)
    {
        perror("Errore nell'apertura del FIFO!");
        return 1;
    }

    char *listptr[LIST_SIZE];

    for (int i = 0; i < LIST_SIZE; i++)
    {
        int length = snprintf(NULL, 0, "%d", i);
        const char suffix[] = " CIAO\n";
        listptr[i] = malloc(length + sizeof(suffix));
        if (!listptr[i])
        {
            perror("malloc");
            for (int j = 0; j < i; j++)
                free(listptr[j]);
            return 1;
        }
        snprintf(listptr[i], length + sizeof(suffix), "%d%s", i, suffix);
    }

    for (int i = 0; i < LIST_SIZE; i++)
    {
        sleep(1);
        write(myFifo, listptr[i], strlen(listptr[i])); // ✅ usa strlen
        printf("%s", listptr[i]);
    }

    for (int i = 0; i < LIST_SIZE; i++)
        free(listptr[i]);

    close(myFifo);
    unlink(pipe_path); // ✅ rimuove la FIFO dopo l’uso

    printf("Produttore - OUT!\n");
    return 0;
}
