#include <stdio.h>

// Fattoriale di n

double fact(int n);

int main()
{
    int n;
    srand(time(NULL)); // Setting the pseudo-random seed

    // Generate a random natural number (values ranging from 1 to 10)
    n = rand() % 10 + 1;

    // Print "n" and its factorial
    printf("n: %d fact: %lf\n", n, fact(n));

    return 0;
}

double fact(int n)
{
    double fact = 1; // Using double for larger numbers
    if (n == 0 || n == 1)
    {
        fact = 1;
    }
    else
    {
        for (int i = 2; i <= n; i++)
            fact *= i;
    }

    return fact;
}