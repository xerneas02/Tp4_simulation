#include "mt.hpp"
#include <math.h>
#include <ctime>
#define ull unsigned long long
#define MAX 1000

ull genRandLitters()
{
    double survivalRate = 0.35;
    return (genrand_real1() < survivalRate);
}

int main(void)
{
    init_genrand(time(NULL));
    
    printf("%lf\n", 67.5774 * log2(11856-4.33514*couples)-553.521);
    
    ull couples = 2000;
    
    
    int values[MAX] = {0};
    for (ull k = 0; k < 1000; k++, couples+=1000)
    {
        double sigma = 0;
        double mean = 0;
        for (int j = 0; j < MAX; j++)
        {
            int litters = 0;
            
            for (ull i = 0; i < couples; i++)
            {
                litters += genRandLitters();
            }
            mean += litters;
            if(j%10000 == 0)printf("%d\n", litters);
            values[j] = litters;
        }

        mean /= MAX;

        for (int i = 0; i < MAX; i++)
        {
            sigma += (values[i] - mean)*(values[i] - mean);
        }
        
        sigma /= MAX;
        sigma = sqrt(sigma);

        printf("Couples = %lld\nMoyenne : %lf\nEcart type : %lf\n\n", couples, mean, sigma);
    }
    

   printf("%lf\n", genererGaussienne(couples*0.35, 1200)); 


    return 0;
}
