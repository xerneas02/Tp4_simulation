#ifndef SIMULATION_H
#define SIMULATION_H

#define MAX_CATEGORY 20*12
#define START_AGE 7

#include "rabbitCategory.hpp"

class Simulation
{
private:
    int nbYears; // simulation's number of years
    int month; // current month
    int nbRabbits; 
    RabbitCategory * categories[MAX_CATEGORY]; // rabbits categories

    int getNbCouples();
    int howManyBabys();
    int genRandBabys();

public:
    Simulation(int nMales, int nFemales);
    void nextMonth();
    
};

#endif