#include "main.hpp"
#include "simulation.hpp"
#include <fstream>
#include <ctime>
#include "latex/latex.h"

int main()
{
    /*----------Initialisation Mersenne Twister----------*/
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, 
    length=4;
    init_by_array(init, length);
    init_genrand(time(NULL));

    Simulation * sim = new Simulation(5, 5);
    long double total = 0;
    int nbSimu = 1000;

    long double totalPerMonth[NUMBER_OF_YEAR*MONTH_PER_YEAR] = {0};
    long double totalPerCategory[MAX_CATEGORY] = {0};

    for (int j = 0; j < nbSimu; j++)
    {
        printf("%d/%d\n", j, nbSimu);
        for (int i = 0; i < NUMBER_OF_YEAR*MONTH_PER_YEAR; i++)
        {
            totalPerMonth[i] += (long double)sim->getNbRabbits()/nbSimu;
            sim->nextMonth();
        }

        for (int i = 0; i < MAX_CATEGORY; i++)
        {
            totalPerCategory[i] += (long double)sim->getCategory(i)->getNbRabbits()/nbSimu;
        }
        
        total += (long double)sim->getNbRabbits()/nbSimu;

        sim->reset();
    }

    printf("Nombre de lapin moyen apres %dans : %0.Lf (%0.LfM)\n", NUMBER_OF_YEAR, total, total/1000000000);
    for (int i = 0; i < NUMBER_OF_YEAR*MONTH_PER_YEAR; i++)
    {
        printf("Month : %d - %Lf\n", i, totalPerMonth[i]);       
    }

    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        printf("Category: %d - %Lf\n", i, totalPerCategory[i]);       
    }


    LatexFile *file = new LatexFile("LatexTest.tex");
    file->addSection("Test");

    file->addFigure(totalPerMonth, NUMBER_OF_YEAR*MONTH_PER_YEAR, 10);

    file->closeLatex();
    

    return 0;
}
