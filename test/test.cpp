#include "mt.hpp"
#include <math.h>
#include <ctime>
#define ull unsigned long long
#define MAX 1000

ull genRandLitters()
{
    double r = genrand_real1();

    if (r < 0.125) return 4;
    else if (r < 0.25) return 8;
    return 5 + (r-0.25)/0.25;
}

ull genRandBabys()
{
    return rand_int_uniform(3, 7);
}

ull genDeath()
{
    double survivalRate = 0.35;
    return (genrand_real1() < survivalRate);
}

int main(void)
{
    init_genrand(time(NULL));

    //printf("%lf\n", 67.5774 * log2(11856-4.33514*loop)-553.521);

    ull loop = 100000;

    double sigmaLitters = 0;
    double meanLitters = 0;

    double sigmaBabys = 0;
    double meanBabys = 0;

    double sigmaSurvival = 0;
    double meanSurvival = 0;

    int valuesLitters[MAX] = {0};
    int valuesBabys[MAX] = {0};
    int valuesSurvival[MAX] = {0};
    for (ull k = 0; k < 1; k++, loop+=1000)
    {
        sigmaLitters = 0;
        meanLitters = 0;

        sigmaBabys = 0;
        meanBabys = 0;

        sigmaSurvival = 0;
        meanSurvival = 0;
        for (int j = 0; j < MAX; j++)
        {
            int litters = 0;
            int babys = 0;
            int survival = 0;
            
            for (ull i = 0; i < loop; i++)
            {
                litters += genRandLitters();
                babys   += genRandBabys();
                survival+= genDeath();
            }
            meanLitters += litters;
            meanBabys   += babys;
            meanSurvival += survival;

            //if(j%10000 == 0)printf("%d\n", litters);
            valuesLitters[j]  = litters;
            valuesBabys[j]    = babys;
            valuesSurvival[j] = survival;
        }

        meanLitters /= MAX;
        meanBabys   /= MAX;
        meanSurvival/= MAX;

        for (int i = 0; i < MAX; i++)
        {
            sigmaLitters += (valuesLitters[i] - meanLitters)*(valuesLitters[i] - meanLitters);
            sigmaBabys   += (valuesBabys[i] - meanBabys)*(valuesBabys[i] - meanBabys);
            sigmaSurvival+= (valuesSurvival[i] - meanSurvival)*(valuesSurvival[i] - meanSurvival);
        }
        
        sigmaLitters /= MAX;
        sigmaLitters = sqrt(sigmaLitters);

        sigmaBabys /= MAX;
        sigmaBabys = sqrt(sigmaBabys);

        sigmaSurvival /= MAX;
        sigmaSurvival = sqrt(sigmaSurvival);

        printf("Loop = %lld\nMoyenne Litters : %lf\nEcart type Litters : %lf\nMoyenne Babys : %lf\nEcart type Babys : %lf\nMoyenne Survival : %lf\nEcart type Survival : %lf\n\n", loop, meanLitters, sigmaLitters, meanBabys, sigmaBabys, meanSurvival, sigmaSurvival);
    }



    meanLitters = 0;
    meanBabys = 0;
    meanSurvival = 0;

    for(int i = 0; i < MAX; i++)
    {
        meanSurvival += genererGaussienne(loop*0.35, sigmaSurvival); 
        meanBabys    += genererGaussienne(loop*4.5, sigmaBabys);
        meanLitters  += genererGaussienne(loop*6, sigmaSurvival);
    }

    printf("Moyenne Litters : %lf\nMoyenne Babys : %lf\nMoyenne Survival : %lf\n", meanLitters/MAX, meanBabys/MAX, meanSurvival/MAX);


    return 0;
}
