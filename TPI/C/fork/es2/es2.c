#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Prendere in input un numero intero n. Il processo deve creare n figli (hint: usare un ciclo for).
gni figlio stampa il suo pid
il padre DEVE attendere la terminazione di tutti i figli
*/

int main()
{
    int n;
    int relID;

    printf("Type the number of children processes desired:\n");

    // Request a natural input for n
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("The number must be natural (a positive - or 0 - integer)");
        scanf("%d", &n);
    }

    // Creates n children
    for (int i = 0; i < n; i++)
    {
        relID = fork();
        if (relID == 0)
        {
            printf("My pid is %d\n", getpid());
            break;
        }
    }

    return 0;
}