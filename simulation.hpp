#ifndef SIMULATION_H
#define SIMULATION_H

#define MAX_CATEGORY 20*12
#define START_AGE 12
#define MONTH_PER_YEAR 12
#define MAJORITY 8



#include "rabbitCategory.hpp"

class Simulation
{
private:
    int maleNextYear  [MONTH_PER_YEAR];
    int femaleNextYear[MONTH_PER_YEAR];
    int nbYears; // simulation's number of years
    int month; // current month
    int nbRabbits; 
    RabbitCategory * categories[MAX_CATEGORY]; // rabbits categories

    int  getNbCouples();
    int  genRandBabys();
    void howManyBabys();
    

public:
    Simulation(int nMales, int nFemales);
    void nextMonth();
    
};

#endif