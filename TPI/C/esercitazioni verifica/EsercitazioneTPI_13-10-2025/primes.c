// 3) Prendere da input 10 numeri, inserirli in un array e stampare solo i numeri primi

#include <stdio.h>

#define ARR_SIZE 10

// Returns 1 if n is prime, otherwise return 0
int isPrime(unsigned int n)
{
    if (n == 0 || n == 1)
        return 0;

    for (unsigned int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    unsigned int arr[ARR_SIZE];

    int temp;
    // Chiede in input 10 numeri naturali
    for (int i = 0; i < ARR_SIZE; i++)
    {
        do
        {
            printf("#%d Inserire un numero (solo numeri naturali): ", i + 1);
            scanf("%d", &temp);
        } while (temp < 0);
        arr[i] = (unsigned int)temp;
    }

    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (isPrime(arr[i]))
            printf("%d\n", arr[i]);
    }

    return 0;
}