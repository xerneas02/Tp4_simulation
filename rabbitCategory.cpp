#include <iostream>
#include "rabbitCategory.hpp"
#include "mt.hpp"


RabbitCategory::RabbitCategory(int month) : 
    month(month)
{
    survivalRate = getSurvivalRate();
}

double RabbitCategory::getSurvivalRate()
{
    if (getMonths() < 6)
        return pow(0.35, 1/4096); 
    else if (getMonths() < 120)
        return pow(0.6, 1/4096);
    else if(getMonths() < 180)
        return pow(0.1, 1/4096);
    return 0.0;
}

void RabbitCategory::addRabbits(int male, int female)
{
    this->male = male;
    this->female = female;
}

void RabbitCategory::transferRabbit(RabbitCategory * category)
{
    int nbRabit = category->getNbRabbits();
    survivalRate = getSurvivalRate();
    int iterMax = (male > female) ? male : female;
    int maleTemp = 0; int femaleTemp = 0;
    
    for (int i = 0; i < iterMax; i++)
    {
        maleTemp += (i < male) && (genrand_real1() < survivalRate);
        femaleTemp += (i < female) && (genrand_real1() < survivalRate);
    }
    category->addRabbits(male, female);
}

int RabbitCategory::getMonths()
{
    return month;
}

int RabbitCategory::getMale()
{
    return male;
}

int RabbitCategory::getFemale()
{
    return female;
}

int RabbitCategory::getNbRabbits()
{
    return male + female;
}
