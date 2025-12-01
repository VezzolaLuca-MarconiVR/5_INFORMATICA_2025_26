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

    // [DONE!] TODO: aprire in lettura
    int fd = open(FIFO_PATH, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    struct sensore s;

    for (int i = 0; i < 8; i++)
    {
        // [DONE!] TODO: leggere la struttura dalla FIFO
        read(fd, &s, sizeof(s));

        printf("[ID: %d] Temp: %.2f °C; Umidità : %.2f %%\n", s.id, s.temperatura, s.umidita);
        // [DONE!] TODO: inserire id,
        // [DONE!] TODO: inserire temperatura ,
        // [DONE!] TODO: inserire umidita );
    }

    close(fd);

    printf("Receiver: terminato.\n");
    return 0;
}