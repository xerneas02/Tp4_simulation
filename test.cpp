#include "mt.hpp"
#include <math.h>
#include <ctime>
#define ull unsigned long long
#define MAX 100000

ull genRandLitters()
{
    double r = genrand_real1();

    if (r < 0.125) return 4;
    else if (r < 0.25) return 8;
    return 5 + (r-0.25)/0.25;
}

int main(void)
{
    init_genrand(time(NULL));
    double mean = 0;
    int values[MAX] = {0};
    double sigma = 0;

    for (int j = 0; j < MAX; j++)
    {
        int litters = 0;
        ull couples = 500;
        for (ull i = 0; i < couples; i++)
        {
            litters += genRandLitters();
        }
        mean += litters;
        if(j%1000 == 0)printf("%d\n", litters);
        values[j] = litters;
    }

    mean /= MAX;

    for (int i = 0; i < MAX; i++)
    {
        sigma += (values[i] - mean)*(values[i] - mean);
    }
    
    sigma /= MAX;
    sigma = sqrt(sigma);

    printf("Moyenne : %lf\nEcart type : %lf\n", mean, sigma);

    return 0;
}
