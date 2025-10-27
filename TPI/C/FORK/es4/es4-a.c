#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Prendere in input un array di n interi
   Creare 2 figli:
   - il primo calcola e stampa la somma dei primi n/2 elementi:
   - il secondo calcola e stampa la somma degli elementi restanti
   - il padre aspetta che i figli terminino
*/

int main()
{
    int n;

    // Request a natural input for n
    printf("Howm many numbers do you want to sum?");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("The number must be natural (a positive - or 0 - integer)");
        scanf("%d", &n);
    }

    // Request n numbers o fill the array
    int inputArr[n];

    for (int i = 0; i < n; i++)
    {
        printf("Type the value:");
        scanf("%d", &inputArr[i]);
    }

    // Creates the first child
    int relID = fork();
    // If this is the first child
    if (relID == 0)
    {
        int sum = 0;
        // Sum the first half of the array
        for (int i = 0; i < n / 2; i++)
        {
            sum += inputArr[i];
        }
        exit(0);
    }
    // If this is the parent
    else
    {
        // Creates the second child
        int relID = fork();
        // If this is the second child
        if (relID == 0)
        {
            int sum = 0;
            // Sum the second half of the array
            for (int i = n / 2; i < n; i++)
            {
                sum += inputArr[i];
            }
            printf("The sum of the last n/2 (%d) elements is: %d\n", n / 2 + 1, sum);
            exit(0);
        }
    }

    wait(NULL);

    printf("I miei figli hanno finito di sommare!\n");

    return 0;
}