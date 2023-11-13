#include <iostream>
#include "rabbitCategory.hpp"
#include "mt.hpp"
#include <math.h>



RabbitCategory::RabbitCategory(ull month) : 
    month(month)
{
    survivalRate = getSurvivalRate();
    male   = 0;
    female = 0;
}

double RabbitCategory::getSurvivalRate()
{
    if (getMonths() < MAJORITY)
        return pow(0.35, 1.0/MAJORITY); 
    else if (getMonths() < MONTH_PER_YEAR * 10)
        return pow(0.6, 1.0/MONTH_PER_YEAR);
    else if(getMonths() < MONTH_PER_YEAR * 15)
        return pow(0.6 - 0.1 * (15 - (float)month/MONTH_PER_YEAR), 1.0/MONTH_PER_YEAR);
    return 0.0;
}

void RabbitCategory::addRabbits(ull male, ull female)
{
    this->male = male;
    this->female = female;
}

void RabbitCategory::transferRabbit(RabbitCategory * category)
{
    ull maleTemp = 0; ull femaleTemp = 0;
    
    for (ull i = 0; i < (MAX_LOOP < male ? MAX_LOOP : male); i++)
    {
        maleTemp += (genrand_real1() < survivalRate);
    }

    maleTemp *= (MAX_LOOP < male ? (float) male / MAX_LOOP : 1);

    for (ull i = 0; i < (MAX_LOOP < female ? MAX_LOOP : female); i++)
    {
        femaleTemp += (genrand_real1() < survivalRate);
    }

    femaleTemp *= (MAX_LOOP < female ? (float) female / MAX_LOOP : 1);
    category->addRabbits(maleTemp, femaleTemp);

    male = 0;
    female = 0;
}

ull RabbitCategory::getMonths()
{
    return month;
}

ull RabbitCategory::getMale()
{
    return male;
}

ull RabbitCategory::getFemale()
{
    return female;
}

ull RabbitCategory::getNbRabbits()
{
    return male + female;
}


