// server.c (corretto)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define PIPE_PATH "/tmp/chat_server"
#define BUFFER_SIZE 256

int main(void)
{
    unlink(PIPE_PATH);
    if (mkfifo(PIPE_PATH, 0666) == -1)
    {
        perror("Errore nella creazione della FIFO");
        exit(1);
    }

    int fd = open(PIPE_PATH, O_RDONLY);
    if (fd == -1)
    {
        perror("Errore nell'apertura della fifo");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    while (1)
    {
        ssize_t rd = read(fd, buffer, BUFFER_SIZE - 1); // lascia spazio per '\0'
        if (rd == -1)
        {
            perror("Errore nella lettura");
            exit(1);
        }

        if (strcmp(buffer, "exit") == 0)
        {
            close(fd);
            unlink(PIPE_PATH);
            exit(0);
        }

        printf("\nMessaggio : %s\n", buffer);
        fflush(stdout);
    }

    return 0;
}
