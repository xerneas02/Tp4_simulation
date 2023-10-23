#include <iostream>
#include "rabbitCategory.hpp"


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

RabbitCategory::RabbitCategory(bool gender, int month) : 
    gender(gender), 
    month(month)
{
    survivalRate = getSurvivalRate();
}