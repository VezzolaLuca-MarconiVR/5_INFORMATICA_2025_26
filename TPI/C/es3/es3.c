#include <stdio.h>
#include <stdbool.h>

// Input di 10 numeri, stamoare solo quelli primi

const int ARRAY_SIZE = 10;

bool prime(int n);

int main()
{
    int arr[ARRAY_SIZE];
    // Input the value for "arr"
    printf("Type a list of natural numbers:\n");

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        scanf("%d", &arr[i]);
        while (arr[i] < 0)
        {
            printf("The number must be natural (a positive - or 0 - integer)");
            scanf("%d", &arr[i]);
        }
    }

    // Print the prime numbers
    printf("The prime numbers are:\t");
    bool firstEl = true;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (prime(arr[i]))
        {
            printf(firstEl ? "%d" : ", %d", arr[i]);
            if (firstEl)
                firstEl = false;
        }
    }

    return 0;
}

bool prime(int n)
{
    bool prime = true;
    if (n == 0 || n == 1 || n == 2)
    {
        prime = false;
    }
    else
    {
        for (int i = 2; prime && i < n; i++)
            if (n % i == 0)
                prime = false;
    }

    return prime;
}