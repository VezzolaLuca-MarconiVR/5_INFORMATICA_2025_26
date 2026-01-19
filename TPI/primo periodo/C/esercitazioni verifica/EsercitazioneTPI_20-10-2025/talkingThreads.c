/*
1) Lanciare un processo che genera un figlio:
     - il padre stampa 'Sono il padre'
     - il figlio stampa 'Sono il figlio'
     - il padre DEVE attendere la terminazione del figlio
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    if (fork() == 0)
    {
        // this is the child thread
        printf("Sono il figlio\n");
        exit(0);
    }

    printf("Sono il padre\n");

    // The father waits for the child to end
    wait(NULL);

    return 0;
}