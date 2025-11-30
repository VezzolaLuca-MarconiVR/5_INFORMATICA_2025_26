// 7) Leggi da un file numeri.txt una lista di numeri interi (uno per riga) e calcola la loro media

#include <stdio.h>

#define FILE_PATH "numeri.txt"

int main()
{
    FILE *fptr = fopen(FILE_PATH, "r");
    int buffer;
    size_t fscanfReturn;
    size_t numbersRead = 0;
    int totalSum = 0;

    if (fptr == NULL)
    {
        perror("The file could not be open");
        return 1;
    }

    do
    {
        fscanfReturn = fscanf(fptr, "%d", &buffer);
        if (fscanfReturn == 1)
        {
            numbersRead++;
            totalSum += buffer;
        }
    } while (fscanfReturn == 1);

    fclose(fptr);

    printf("La media di tutti i numeri è %d\n", (int)(totalSum / numbersRead));

    return 0;
}