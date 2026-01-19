/*
Creazione di n figli che calcolano un valore
Leggere da input un numero intero. Il processo padre deve creare n figli; ogni figlio deve:
- calcolare il quadrato del proprio indice (1, 2, 3, ...)
- stampare: "Figlio i: il quadrato è ..."
Il padre attende tutti i figli e al termine stampa: "Tutti i figli sono terminati."
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Ritorna il quadrato di un numero (un intero positivo)
unsigned int squared(int n)
{
    return n * n;
}

int main()
{
    int n;

    do
    {
        printf("Digitare il numero (naturale, non-zero) di figli quadrati desiderato: ");
        scanf("%d", &n);
    } while (n <= 0);

    for (int i = 0; i < n; i++)
    {
        int relativePID = fork();
        if (relativePID == 0)
        {
            // Processo figlio
            printf("Figlio %d: il quadrato è %u\n", i + 1, squared(i + 1)); // %u è per l'intero unsigned
            exit(0);
        }
        else if (relativePID == -1)
        {
            // Errore nella fork
            perror("Errore nella creazione della fork");
            exit(-1);
        }
        // Processo padre
    }

    // Attende i figli fino a quando wait non trova più alcun figlio (ritorna -1)
    while (wait(NULL) > 0)
        ;

    printf("Padre: Tutti i figli sono terminati.\n");

    return 0;
}