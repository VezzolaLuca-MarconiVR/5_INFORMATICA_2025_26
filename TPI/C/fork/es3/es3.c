#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Lanciare un processo che genera due figli (A e B): - A a sua volta genera il figlio A1 - B genera i
figli B1 e B2 Ogni processo deve mostrare in output una cosa del tipo: "Sono B2, figlio di B".
N.B.: Bisogna far terminare i processi in modo ordinato utilizzando le opportune wait()
*/

int main()
{
    // Creates child A
    int relID = fork();

    // If this is child A
    if (relID == 0)
    {
        // Creates child A1
        relID = fork();
        if (relID == 0)
        {
            printf("Sono A1, il figlio di A\n");
            exit(0);
        }
    }
    // If this is the parent
    else
    {
        // Creates child B
        relID = fork();

        // If this is B
        if (relID == 0)
        {
            // Creates child B1
            relID = fork();
            if (relID == 0)
            {
                printf("Sono B1, il figlio di B\n");
                exit(0);
            }
            // If this is B
            else
            {
                // Creates child B1
                relID = fork();
                if (relID == 0)
                {
                    printf("Sono B2, il figlio di B\n");
                    exit(0);
                }
            }
        }
    }

    return 0;
}