// 4) Prendere in input due matrici 3x3 e stampare la matrice somma

#include <stdio.h>

#define MATR_SIZE 3

void sum(int matrA2D[], int matrB2D[], int matrSum2D[], size_t C)
{
    for (int i = 0; i < C * C; i++)
        matrSum2D[i] = matrA2D[i] + matrB2D[i];
}

int main()
{
    int matrA[MATR_SIZE * MATR_SIZE];
    int matrB[MATR_SIZE * MATR_SIZE];
    int matrSum[MATR_SIZE * MATR_SIZE];

    printf("Type the first matrix's elements one by one (L to R, T to B):\n");
    for (int i = 0; i < MATR_SIZE * MATR_SIZE; i++)
        scanf("%d", &matrA[i]);

    printf("Type the second matrix's elements one by one (L to R, T to B):\n");
    for (int i = 0; i < MATR_SIZE * MATR_SIZE; i++)
        scanf("%d", &matrB[i]);

    sum(matrA, matrB, matrSum, MATR_SIZE);

    printf("Resulting matrix:\n");
    for (int r = 0; r < MATR_SIZE; r++)
    {
        printf("|");
        for (int c = 0; c < MATR_SIZE; c++)
        {
            printf("\t%d\t|", matrSum[r * MATR_SIZE + c]);
        }
        printf("\n");
    }
}