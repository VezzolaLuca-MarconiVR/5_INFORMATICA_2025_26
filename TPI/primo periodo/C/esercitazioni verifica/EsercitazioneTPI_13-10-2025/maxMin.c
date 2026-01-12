// 1) Stampare il valore massimo e il valore minimo di un array di 10 elementi

#include <stdio.h>

#define ARR_SIZE 10

// Returns the max value of an int array
int max(int arr[], int size)
{
    int maxValue = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > maxValue)
            maxValue = arr[i];

    return maxValue;
}

// Returns the minimum value of an int array
int min(int arr[], int size)
{
    int minValue = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < minValue)
            minValue = arr[i];

    return minValue;
}

int main()
{
    // Istanzia l'array
    int arr[ARR_SIZE] = {4, 10, 5, 1, 2, 7, 8, 9, 5, 9};

    printf("max: %d\n", max(arr, ARR_SIZE));
    printf("min: %d\n", min(arr, ARR_SIZE));

    return 0;
}