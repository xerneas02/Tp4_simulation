#include "simulation.hpp"
#include "rabbitCategory.hpp"
#include  "mt.hpp"

Simulation::Simulation(ull nMales, ull nFemales)
{
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i] = new RabbitCategory(i);
    }

    categories[START_AGE]->addRabbits(nMales, nFemales);

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear[i] = 0;
        femaleNextYear[i] = 0;
    }
        
}


void Simulation::nextMonth()
{
    if (month%MONTH_PER_YEAR == 0)
    {
        month = 0;
        nbYears++;
        howManyBabys();
    }
    month++;

    for (int i = MAX_CATEGORY-2; i >= 0; i--)
    {
        categories[i]->transferRabbit(categories[i+1]);
    }

    categories[0]->addRabbits(maleNextYear[month], femaleNextYear[month]);
}

ull Simulation::getNbCouples()
{
    ull females = 0;
    for (ull i = MAJORITY; i < MAX_CATEGORY; i++)
    {
        females += categories[i]->getFemale();
    }
    
    return females;
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
        //prullf("%d : %d\n", i, categories[i]->getNbRabbits());
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

    for (ull i = 0; i < (MAX_LOOP < couples ? MAX_LOOP : couples); i++)
    {
        litters += genRandLitters();
    }

    litters *= (MAX_LOOP < couples ? (float) couples / MAX_LOOP : 1);

    ull littersPerMonth[MONTH_PER_YEAR];
    for (ull i = 0; i < MONTH_PER_YEAR; i++)
        littersPerMonth[i] = litters/MONTH_PER_YEAR;

    for (ull i = 0; i < litters%MONTH_PER_YEAR; i++)
        littersPerMonth[rand_int_uniform(0, MONTH_PER_YEAR)]++;
     
    ull babys;

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear  [i] = 0;
        femaleNextYear[i] = 0;
        for (ull j = 0; j < (MAX_LOOP < littersPerMonth[i] ? MAX_LOOP : littersPerMonth[i]); j++)
        {
            babys = genRandBabys() *  (MAX_LOOP < littersPerMonth[i] ? (float) littersPerMonth[i] / MAX_LOOP : 1);
            for (ull k = 0; k < (MAX_LOOP < babys ? MAX_LOOP : babys); k++)
            {
                if (rand_int_uniform(0, 2) == 0)
                    maleNextYear  [i] += (MAX_LOOP < babys ? (float) babys / MAX_LOOP : 1);
                else
                    femaleNextYear[i] += (MAX_LOOP < babys ? (float) babys / MAX_LOOP : 1);
            }
        }
    }
}