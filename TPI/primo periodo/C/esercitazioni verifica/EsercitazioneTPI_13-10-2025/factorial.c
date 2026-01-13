// 2) Scrivere una funzione int fattoriale(int n) che stampi il fattoriale avendo in input il valore n

#include <stdio.h>

// Return the factorial of a natural int
unsigned long long fact(unsigned int n)
{
    unsigned long long fact = 1;
    if (n != 0 && n != 1)
        for (unsigned long long i = 2; i <= n; i++)
            fact *= i;
    return fact;
}

int main()
{
    int n;

    do
    {
        // Ask user to type n
        printf("Type the number desired (a natural number below 20 - the max computable limit for this program): ");
        scanf("%d", &n);
    } while (n < 0 || n > 20); // n must be positive (and under 20 for llu max)

    printf("%d!: %llu\n", n, fact(n));

    return 0;
}