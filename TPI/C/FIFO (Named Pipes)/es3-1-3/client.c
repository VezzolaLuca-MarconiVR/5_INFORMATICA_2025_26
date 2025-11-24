// client.c (corretto)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE_PATH "/tmp/chat_server"
#define BUFFER_SIZE 256

int main(void)
{
    char buffer[BUFFER_SIZE];

    int fd = open(PIPE_PATH, O_WRONLY);
    if (fd == -1)
    {
        perror("Errore nell'apertura della fifo");
        exit(1);
    }

    while (1)
    {
        printf("Scrivi qui il messaggio da inviare: ");

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            perror("Errore nella lettura dell'input");
            exit(1);
        }

        // rimuovi newline
        // size è per valori solo positivi o zero
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        // scrivi solo i byte effettivi
        // ssize indica una signed size, quindi anche valori negativi o zero
        ssize_t wr = write(fd, buffer, len);
        if (wr == -1)
        {
            perror("Errore nella scrittura");
            exit(1);
        }

        if (strcmp(buffer, "exit") == 0)
        {
            close(fd);
            exit(0);
        }
    }

    return 0;
}
