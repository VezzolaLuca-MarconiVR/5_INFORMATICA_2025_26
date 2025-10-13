#include <stdio.h>
#include <time.h>

// Massimo e minimo di un array di 10 elementi
const int ARRAY_SIZE = 10;

int min(int *arr);
int max(int *arr);

int main()
{
    int arr[ARRAY_SIZE];
    srand(time(NULL)); // Setting the pseudo-random seed

    // Generate a random positive int array (values ranging from 1 to 100)
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % 100 + 1; // A random number between 1 and 100
    }

    // Print all the elements of the array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("pos %d: %d\n", i + 1, arr[i]);
    }

    // Print the min and max values
    printf("min:%d  max:%d\n", min(arr), max(arr));

    return 0;
}

int min(int *arr)
{
    int min = arr[0];
    for (int i = 0; i < ARRAY_SIZE; i++)
        if (min > arr[i])
            min = arr[i];

    return min;
}

int max(int *arr)
{
    int max = arr[0];
    for (int i = 0; i < ARRAY_SIZE; i++)
        if (max < arr[i])
            max = arr[i];

    return max;
}