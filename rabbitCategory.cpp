#include <iostream>
#include "rabbitCategory.hpp"


RabbitCategory::RabbitCategory(int month) : 
    month(month)
{
    survivalRate = getSurvivalRate();
}

double RabbitCategory::getSurvivalRate()
{
    if (getMonths() < 6)
        return 0.35; 
    else if (getMonths() < 120)
        return 0.6;
    else if(getMonths() < 180)
        return 0.1;
    
    return 0.0;
}

void RabbitCategory::addRabbits(int male, int female)
{
    this->male = male;
    this->female = female;
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
