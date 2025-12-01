#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define FIFO_PATH "/tmp/fifo_sensori"

struct sensore
{
    int id;
    double temperatura;
    double umidita;
};

int main()
{
    srand(time(NULL));

    if (mkfifo(FIFO_PATH, 0666) == -1)
    {
        perror("mkfifo");
        // [DONE!] TODO: gestire il caso in cui la FIFO esiste già
        unlink(FIFO_PATH);
        exit(1);
    }

    printf("Sender: apro la FIFO...\n");

    // [DONE!] TODO: aprire in scrittura
    int fd = open(FIFO_PATH, O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    struct sensore s;

    for (int i = 0; i < 8; i++)
    {
        // [DONE!] TODO: genera id in maniera progressiva
        s.id = i;
        // [DONE!] TODO: genera temp randomicamente (10°C-40°C)
        s.temperatura = 10 + (rand() % 3000) / 100.0;
        // [DONE!] TODO: genera umidità  randomicamente (20-90%)
        s.umidita = 20 + (rand() % 7000) / 100.0;

        printf("Sender: invio struttura %d...\n", s.id);

        // [DONE!] TODO: scrivere la struttura nella FIFO
        write(fd, &s, sizeof(s));

        sleep(1);
    }

    // [DONE!] TODO:  chiudi ed elimina la FIFO
    close(fd);
    unlink(FIFO_PATH);

    printf("Sender: terminato.\n");
    return 0;
}
