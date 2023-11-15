#include "simulation.hpp"
#include "rabbitCategory.hpp"
#include  "mt.hpp"
#include <math.h>

Simulation::Simulation(ull nMales, ull nFemales)
{
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i] = new RabbitCategory(i);
    }

    categories[START_AGE]->setRabbits(nMales, nFemales);

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear[i] = 0;
        femaleNextYear[i] = 0;
    }

    maleStart = nMales;
    femaleStart = nFemales;

    ecartType = 1200;
        
}

void Simulation::reset()
{
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i]->setRabbits(0, 0);
    }

    categories[START_AGE]->setRabbits(maleStart, femaleStart);

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear[i] = 0;
        femaleNextYear[i] = 0;
    }
}


void Simulation::nextMonth()
{
    if (month == 0)
    {
        nbYears++;
        howManyBabys();
    }

    for (int i = MAX_CATEGORY-2; i >= 0; i--)
    {
        categories[i]->transferRabbit(categories[i+1]);
    } 

    categories[0]->setRabbits(maleNextYear[month], femaleNextYear[month]);

    month = (month + 1) % MONTH_PER_YEAR;
}

ull Simulation::getNbCouples()
{
    ull females = 0;
    ull males   = 0;
    for (ull i = MAJORITY; i < MAX_CATEGORY; i++)
    {
        females += categories[i]->getFemale();
        males   += categories[i]->getMale();
    }
    males *= 10;

    return females < males ? females : males;
}

RabbitCategory * Simulation::getCategory(ull i)
{
    return categories[i];
}

ull Simulation::getNbRabbits()
{
    ull rabbits = 0;
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        rabbits += categories[i]->getNbRabbits();
    }
    
    
    return rabbits;
}

ull Simulation::genRandBabys()
{
    return rand_int_uniform(3, 7);

}

ull Simulation::genRandLitters()
{
    double r = genrand_real1();

    if (r < 0.125) return 4;
    else if (r < 0.25) return 8;
    return 5 + (r-0.25)/0.25;
}

void Simulation::howManyBabys()
{
    ull couples = getNbCouples();
    ull litters = 0;

    if (couples < MAX_LOOP)
    {
        for (ull i = 0; i < couples; i++)
        {
            litters += genRandLitters();
        }
    }
    else 
    {
        litters = genererGaussienne(couples*6, ecartType);
    }
    
        

    ull littersPerMonth[MONTH_PER_YEAR];
    for (ull i = 0; i < MONTH_PER_YEAR; i++){
        littersPerMonth[i] = litters/MONTH_PER_YEAR;
    }

    for (ull i = 0; i < litters%MONTH_PER_YEAR; i++){
        littersPerMonth[rand_int_uniform(0, MONTH_PER_YEAR)]++;
    }
     
    ull babys;

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        babys = 0;
        maleNextYear  [i] = 0;
        femaleNextYear[i] = 0;
        if (littersPerMonth[i] < MAX_LOOP)
        {
            for (ull j = 0; j < littersPerMonth[i]; j++)
            {
                babys += genRandBabys();
                
            }
        }
        else
        {
            babys = genererGaussienne(littersPerMonth[i]*4.5, ecartType);
        }                
        maleNextYear  [i] += babys/2;
        femaleNextYear[i] += babys/2;
    }
}