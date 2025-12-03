/******************************************************
 * consegna separatamente come COGNOME_FIFO_receiver.c *
 *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/fifo_sensori"

struct sensore
{
    int id;
    double temperatura;
    double umidita;
};

int main()
{
    printf("Receiver: apro la FIFO...\n");

    // TODO: aprire in lettura
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    struct sensore s;

    for (int i = 0; i < 8; i++)
    {
        // TODO: leggere la struttura dalla FIFO

        printf("[ID: %d] Temp: %.2f Â°C â€” UmiditÃ : %.2f %%\n",
        // TODO: inserire id,
        // TODO: inserire temperatura ,
        // TODO: inserire umidita );
    }

    close(fd);

    printf("Receiver: terminato.\n");
    return 0;
}

/****************************************************
 * consegna separatamente come COGNOME_FIFO_sender.c *
 *****************************************************/

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
        // TODO: gestire il caso in cui la FIFO esiste giÃ
    }

    printf("Sender: apro la FIFO...\n");

    // TODO: aprire in scrittura
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    struct sensore s;

    for (int i = 0; i < 8; i++)
    {
        // TODO: genera id in maniera progressiva
        // TODO: genera temp randomicamento (10Â°-40Â°)
        // TODO: genera umiditÃ  randomicamento (20-90%)

        printf("Sender: invio struttura %d...\n", s.id);

        // TODO: scrivere la struttura nella FIFO

        sleep(1);
    }

    // TODO:  chiudi ed elimina la FIFO

    printf("Sender: terminato.\n");
    return 0;
}
