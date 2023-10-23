#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation
{
private:
    int nbYears; // simulation's number of years
    int nbRabbits; 

public:
    Simulation(int nbYears, int nbRabbits);
    int getMonths();
    bool getGender();
    int getNbRabbits();
    int nbAged(); 
    void addRabbits(int nbRabbits);
};

#endif