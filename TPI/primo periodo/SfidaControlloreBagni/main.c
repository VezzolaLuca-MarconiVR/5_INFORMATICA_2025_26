#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double uniform()
{
    return (rand() + 1.0) / (RAND_MAX + 1.0);
}

double exp_rand(double lambda)
{
    double u = uniform();
    return -log(1.0 - u) / lambda;
}

double normal_rand(double mu, double sigma)
{
    static int have = 0;
    static double z2;
    if (have)
    {
        have = 0;
        return mu + sigma * z2;
    }
    double u1 = uniform(), u2 = uniform();
    double r = sqrt(-2.0 * log(u1));
    double z1 = r * cos(2.0 * M_PI * u2);
    z2 = r * sin(2.0 * M_PI * u2);
    have = 1;
    return mu + sigma * z1;
}

int main(void)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < 5; ++i)
    {
        printf("exp=%.4f, normal=%.4f\n", exp_rand(1.0), normal_rand(5.0, 1.5));
    }
    return 0;
}
