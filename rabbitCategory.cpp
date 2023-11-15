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

    ecartType = 480;
}

double RabbitCategory::getSurvivalRate()
{
    if (getMonths() < MAJORITY)
        return pow(0.35, 1.0/MAJORITY); 
    else if (getMonths() < MONTH_PER_YEAR * 10)
        return pow(0.6, 1.0/MONTH_PER_YEAR);
    else if(getMonths() < MONTH_PER_YEAR * 15)
        return pow(0.6 - 0.1 * (15 - ((float)month)/MONTH_PER_YEAR), 1.0/MONTH_PER_YEAR);
    return 0.0;
}

void RabbitCategory::setRabbits(ull male, ull female)
{
    this->male = male;
    this->female = female;
}

void RabbitCategory::transferRabbit(RabbitCategory * category)
{
    ull maleTemp = 0; ull femaleTemp = 0;    
    
    if (male < MAX_LOOP) 
    {
        for (ull i = 0; i < male; i++)
        {
            maleTemp += (genrand_real1() < survivalRate);
        }
    }
    else
    {
        maleTemp = genererGaussienne(male*survivalRate, 480);
    }
    

    if (female < MAX_LOOP) 
    {
        for (ull i = 0; i < female; i++)
        {
            femaleTemp += (genrand_real1() < survivalRate);
        }
    }
    else
    {
        femaleTemp = genererGaussienne(female*survivalRate, 480);
    }

    category->setRabbits(maleTemp, femaleTemp);

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


