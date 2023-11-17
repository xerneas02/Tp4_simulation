#ifndef MAIN_H

#define MAIN_H

#include <iostream>
#include <string.h>
#include <fstream>
#include "mt.hpp"

#define NUMBER_OF_YEAR 5

typedef struct {
    long double total;
    int numberOfYears;
    int nbSimu;
    unsigned long mtState[624];  // État du Mersenne Twister
    long double* totalPerMonth;
    long double* totalPerCategory;
    int i;
    int j;
} EtatSimulation;


#endif