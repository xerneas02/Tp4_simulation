#include <iostream>
#include "rabbitCategory.hpp"


RabbitCategory::RabbitCategory(int month) : 
    month(month)
{
    survivalRate = getSurvivalRate();
    male   = 0;
    female = 0;
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
    // TODO
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
