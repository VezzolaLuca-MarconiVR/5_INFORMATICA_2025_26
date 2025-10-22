#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Prendere in input un array di n interi
    Creare 2 figli:
    - il primo calcola e stampa la somma dei primi n/2 elementi:
    - il secondo calcola e la somma degli elementi restanti
    - utilizzare due file 'somma1.txt' e 'somma2.txt' e sfruttarli per calcolare la somma totale nel padre e output
    - il padre aspetta che i figli terminino
*/

int main()
{
    int n;
    FILE *fptr;

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

        // Write the sum on its file sumA.txt
        fptr = fopen("sumA.txt", "w");
        fprintf(fptr, itoa(sum));
        fclose(fptr);

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

            // Write the sum on its file sumA.txt
            fptr = fopen("sumB.txt", "w");
            fprintf(fptr, itoa(sum));
            fclose(fptr);

            exit(0);
        }
    }

    // Il padre aspetta che i figli concludano
    wait(NULL);
    // Per poi leggere i file contenenti i risultati e sommarli
    fptr = fopen("sumA.txt", "r");
    char readA[100];
    fgets(readA, size(readA) / size(readA[0]), fptr);
    fclose(fptr);

    fptr = fopen("sumB.txt", "r");
    char readB[100];
    fgets(readB, size(readB) / size(readB[0]), fptr);
    fclose(fptr);

    int sumA = atoi(readA);
    int sumB = atoi(readB);
    int sumTot = sumA + sumB;

    printf("I miei figli hanno calcolato %d e %d, quindi la somma totale è %d\n",
           sumA, sumB, sumTot);

    return 0;
}