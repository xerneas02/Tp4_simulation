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
    
    for (int i = MAX_CATEGORY-1; i >= 0; i--)
    {
        categories[i]->transferRabbit(categories[i+1]);
    }

    categories[0]->addRabbits(maleNextYear[month], femaleNextYear[month]);
}

int Simulation::getNbCouples()
{
    int females = 0;
    for (int i = START_AGE; i < MAX_CATEGORY; i++)
    {
        females += categories[i]->getFemale();
    }
    
    return females;
}

int Simulation::genRandBabys()
{
    return (int) rand_reel_uniform(4, 7);
}

int Simulation::howManyBabys()
{
    int couples = getNbCouples();
    int nbBabys  = couples + couples*(7/12);
    int babys;

    for (int i = 0; i < MONTH_PER_YEAR; i++)
    {
        for (int j = 0; j < nbBabys/MONTH_PER_YEAR; j++)
        {
            babys = genRandBabys();
            for (int k = 0; k < babys; k++)
            {
                if (genrand_real1() > 0.5)
                    maleNextYear  [j]++;
                else
                    femaleNextYear[j]++;
            }
            
        }
    }
    
}