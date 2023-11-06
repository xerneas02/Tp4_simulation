#include "simulation.hpp"
#include "rabbitCategory.hpp"
#include  "mt.hpp"

Simulation::Simulation(int nMales, int nFemales)
{
    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i] = new RabbitCategory(i);
    }

    categories[START_AGE]->addRabbits(nMales, nFemales);
}


void Simulation::nextMonth()
{
    month++;
    if (month%MONTH_PER_YEAR == 0)
    {
        month = 0;
        nbYears++;
        howManyBabys();
    }
    
    for (int i = MAX_CATEGORY-2; i >= 0; i--)
    {
        categories[i]->transferRabbit(categories[i+1]);
    }

    categories[0]->addRabbits(maleNextYear[month], femaleNextYear[month]);
}

int Simulation::getNbCouples()
{
    int females = 0;
    for (int i = MAJORITY; i < MAX_CATEGORY; i++)
    {
        females += categories[i]->getFemale();
    }
    
    return females;
}

int Simulation::genRandBabys()
{
    return (int) rand_int_uniform(3, 7);
}

int Simulation::genRandLitters()
{
    double r = genrand_real1();

    if (r < 0.125) return 4;
    else if (r < 0.25) return 8;
    return 5 + (r-0.25)/0.25;
}

void Simulation::howManyBabys()
{
    int couples = getNbCouples();
    int litters = 0;
    for (int i = 0; i < couples; i++)
    {
        litters += genRandLitters();
    }

    int littersPerMonth[MONTH_PER_YEAR];
    for (int i = 0; i < MONTH_PER_YEAR; i++)
        littersPerMonth[i] = litters/MONTH_PER_YEAR;

    for (int i = 0; i < litters%MONTH_PER_YEAR; i++)
        littersPerMonth[rand_int_uniform(0, MONTH_PER_YEAR)]++;
     
    int babys;

    for (int i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear  [i] = 0;
        femaleNextYear[i] = 0;
        for (int j = 0; j < littersPerMonth[i]; j++)
        {
            babys = genRandBabys();
            for (int k = 0; k < babys; k++)
            {
                if (rand_int_uniform(0, 2) == 0)
                    maleNextYear  [i]++;
                else
                    femaleNextYear[i]++;
            }
        }
    }
}