#include <iostream>
#include "rabbitCategory.hpp"


RabbitCategory::RabbitCategory(bool gender, int month) : 
    gender(gender), 
    month(month)
{
    survivalRate = getSurvivalRate();
}

double RabbitCategory::getSurvivalRate()
{
    if (getMonths() < 6)
    {
        return 0.35;
    }
    else if (getMonths() < 120)
    {
        return 0.6;
    }
    else if(getMonths() < 180)
    {
        return 0.1;
    }
    
    return 0.0;
}

void RabbitCategory::addRabbits(int nbRabbits)
{
    this->nbRabbits += nbRabbits;
}


int RabbitCategory::getMonths()
{
    return month;
}

bool RabbitCategory::getGender()
{
    return gender;
}

int RabbitCategory::getNbRabbits()
{
    return nbRabbits;
}
