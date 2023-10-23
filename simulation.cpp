#include "simulation.hpp"
#include "rabbitCategory.hpp"
#include  "mt.hpp"

Simulation::Simulation(int nMales, int nFemales) :
{
    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i] = new RabbitCategory(i);
    }

    categories[START_AGE]->addRabbits(nMales, nFemales);
}


void Simulation::nextMonth()
{
    for (int i = 0; i < MAX_CATEGORY-1; i++)
    {
        categories[i]->transferRabbit(categories[i+1]);
    }
    
}

int Simulation::getNbCouples()
{
    int males   = 0;
    int females = 0;
    int limiter;
    for (int i = START_AGE; i < MAX_CATEGORY; i++)
    {
        males   += categories[i]->getMale  ();
        females += categories[i]->getFemale();
    }
    
    limiter = males > females ? females : males;
    return limiter;
}

int Simulation::genRandBabys()
{
    return (int) rand_reel_uniform(4, 7);
}

int Simulation::howManyBabys()
{
    
}