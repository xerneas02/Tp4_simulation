#ifndef SIMULATION_H
#define SIMULATION_H

#define MAX_CATEGORY 20*12
#define START_AGE 12




#include "rabbitCategory.hpp"

class Simulation
{
private:
    ull maleNextYear  [MONTH_PER_YEAR];
    ull femaleNextYear[MONTH_PER_YEAR];
    ull nbYears; // simulation's number of years
    ull month; // current month
    ull nbRabbits; 

    ull maleStart;
    ull femaleStart;

    RabbitCategory * categories[MAX_CATEGORY]; // rabbits categories

    ull  getNbCouples();
    ull  genRandBabys();
    void howManyBabys();
    ull  genRandLitters();
    

public:
    Simulation(ull nMales, ull nFemales);
    void reset();
    void nextMonth();
    ull  getNbRabbits();
    RabbitCategory * getCategory(ull i);
};

#endif