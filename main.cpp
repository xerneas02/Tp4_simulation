#include "main.hpp"
#include "simulation.hpp"
#include <fstream>
#include <ctime>
#include "math.h"
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


    LatexFile *file = new LatexFile("Graph.tex");
    file->addFigure(totalPerMonth, NUMBER_OF_YEAR*MONTH_PER_YEAR, 10, 1000000000, 0, NUMBER_OF_YEAR*MONTH_PER_YEAR, 0, 30000000000, "Mois", "Milliard de lapins", "Evolution du nombre de lapin sur 20ans");

    file->addFigure(totalPerCategory, MAX_CATEGORY, 10, 100000000, 0, MAX_CATEGORY, 0, 1000000000, "Age en mois", "Millions de lapins", "Nombre de lapin dans chaques categories d'age après 20ans");

    long double logTotalPerMonth[NUMBER_OF_YEAR*MONTH_PER_YEAR];
    long double sum = 0;
    for (int i = 0; i < NUMBER_OF_YEAR*MONTH_PER_YEAR; i++)
    {
        logTotalPerMonth[i] = totalPerMonth[i] > 0 ? log10(totalPerMonth[i]) : 0;
        sum += totalPerMonth[i];
    }
    
    file->addFigure(logTotalPerMonth, NUMBER_OF_YEAR*MONTH_PER_YEAR, 10, 1, 0, NUMBER_OF_YEAR*MONTH_PER_YEAR, 0, 12, "Mois", "log(nombres de lapins)", "Evolution du nombre de lapin sur 20ans (echelle log)");

    long double percentageTotalPerMonth[NUMBER_OF_YEAR*MONTH_PER_YEAR];
    for (int i = 0; i < NUMBER_OF_YEAR*MONTH_PER_YEAR; i++)
    {
        percentageTotalPerMonth[i] = totalPerMonth[i]/sum * 100;
    }

    file->addFigure(percentageTotalPerMonth, NUMBER_OF_YEAR*MONTH_PER_YEAR, 10, 10, 0, NUMBER_OF_YEAR*MONTH_PER_YEAR, 0, 100, "Mois", "Pourcentage de lapins", "Evolution du nombre de lapin sur 20ans en %");

    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        sum += totalPerCategory[i];
    }

    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        percentageTotalPerMonth[i] = totalPerCategory[i]/sum * 100;
    }

    file->addFigure(percentageTotalPerMonth, MAX_CATEGORY, 10, 10, 0, MAX_CATEGORY, 0, 100, "Age en mois", "Pourcentage de lapins", "Pourcentage de lapin dans chaques categories d'age après 20ans");


    file->closeLatex();
    

    return 0;
}
