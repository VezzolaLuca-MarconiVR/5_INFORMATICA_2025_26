#include <stdio.h>
#include <stdbool.h>

// Inserire due matrici 3x3 e stamparne la matrice somma

#define MATR_SIZE 3 // The length of the matrices (total matrix size: MATR_SIZE*MATR_SIZE)

void sumMatrices(int matrA[MATR_SIZE][MATR_SIZE], int matrB[MATR_SIZE][MATR_SIZE], int matrSum[MATR_SIZE][MATR_SIZE]);

int main()
{
  int matrA[MATR_SIZE][MATR_SIZE], matrB[MATR_SIZE][MATR_SIZE], matrSum[MATR_SIZE][MATR_SIZE];

  // Input the values for the matrices
  printf("Type the first matrix values (left to right, top to bottom):\n");
  for (int i = 0; i < MATR_SIZE; i++)
  {
    for (int j = 0; j < MATR_SIZE; j++)
    {
      scanf("%d", &matrA[i][j]);
    }
  }
  printf("Type the second matrix values (left to right, top to bottom):\n");
  for (int i = 0; i < MATR_SIZE; i++)
  {
    for (int j = 0; j < MATR_SIZE; j++)
    {
      scanf("%d", &matrB[i][j]);
    }
  }

  // Calculate the sum of the matrices
  sumMatrices(matrA, matrB, matrSum);

  // Print the matrices
  printf("______\n");
  for (int i = 0; i < MATR_SIZE; i++)
  {
    for (int j = 0; j < MATR_SIZE; j++)
    {
      printf("%d ", matrA[i][j]);
    }
    printf("\n");
  }
  printf("+\n");
  for (int i = 0; i < MATR_SIZE; i++)
  {
    for (int j = 0; j < MATR_SIZE; j++)
    {
      printf("%d ", matrB[i][j]);
    }
    printf("\n");
  }
  printf("=\n");
  for (int i = 0; i < MATR_SIZE; i++)
  {
    for (int j = 0; j < MATR_SIZE; j++)
    {
      printf("%d ", matrSum[i][j]);
    }
    printf("\n");
  }

  return 0;
}

void sumMatrices(int matrA[MATR_SIZE][MATR_SIZE], int matrB[MATR_SIZE][MATR_SIZE], int matrSum[MATR_SIZE][MATR_SIZE])
{
  for (int i = 0; i < MATR_SIZE; i++)
  {
    for (int j = 0; j < MATR_SIZE; j++)
    {
      matrSum[i][j] = matrA[i][j] + matrB[i][j];
    }
  }
}