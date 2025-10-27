#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Prendere in input un array di n interi
    Creare 2 figli:
    - il primo calcola e stampa la somma dei primi n/2 elementi:
    - il secondo calcola e la somma degli elementi restanti
    - utilizzare delle pipe per permettere una 'diretta' tra padre e figlio
*/

int main()
{
    int n;
    int fdes1[2]; // file descriptor => [0] is the reading side; [1] is the writing side
    int fdes2[2];

    if (pipe(fdes1) < 0 || pipe(fdes2) < 0)
        exit(1);

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
        close(fdes1[0]);

        int sum = 0;
        // Sum the first half of the array
        for (int i = 0; i < n / 2; i++)
        {
            sum += inputArr[i];
        }

        // Write the half-sum on the pipe
        write(fdes1[1], &sum, sizeof(sum));

        close(fdes1[1]);

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
            close(fdes2[0]);

            int sum = 0;
            // Sum the second half of the array
            for (int i = n / 2; i < n; i++)
            {
                sum += inputArr[i];
            }

            // Write the half-sum on the pipe
            write(fdes2[1], &sum, sizeof(sum));

            close(fdes2[1]);

            exit(0);
        }
    }

    // chiudi lati pipe inutilizzati
    close(fdes1[1]);
    close(fdes1[1]);

    // Il padre aspetta che i figli concludano
    wait(NULL);

    int sumA;
    int sumB;
    int sumTot;

    // Per poi leggere i pipe contenenti i risultati e sommarli
    read(fdes1[0], &sumA, sizeof(sumA));
    close(fdes1[0]);

    read(fdes2[0], &sumB, sizeof(sumB));
    close(fdes2[0]);

    sumTot = sumA + sumB;

    printf("I miei figli hanno calcolato %d e %d, quindi la somma totale è %d\n",
           sumA, sumB, sumTot);

    return 0;
}