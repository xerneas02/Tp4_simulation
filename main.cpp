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
    int nbSimu = 20000;

    for (int i = 0; i < 10; i++)
    {  
        int numberOfYears = NUMBER_OF_YEAR+(i);
        long double * resSimus = (long double*) malloc(sizeof(long double) * nbSimu);
        long double totalPerMonth[numberOfYears*MONTH_PER_YEAR] = {0};
        long double totalPerCategory[MAX_CATEGORY] = {0};

        for (int j = 0; j < nbSimu; j++)
        {
            if(j%10000 == 0)printf("%d : %d/%d\n", i, j, nbSimu);
            for (int k = 0; k < numberOfYears*MONTH_PER_YEAR; k++)
            {
                totalPerMonth[k] += (long double)sim->getNbRabbits()/nbSimu;
                sim->nextMonth();
            }

            for (int k = 0; k < MAX_CATEGORY; k++)
            {
                totalPerCategory[k] += (long double)sim->getCategory(k)->getNbRabbits()/nbSimu;
            }
            
            resSimus[j] = sim->getNbRabbits();
            total += (long double)sim->getNbRabbits()/nbSimu;

            sim->reset();
        }

        printf("Nombre de lapin moyen apres %dans : %0.Lf (%0.LfM)\n", numberOfYears, total, total/1000000000);
        /*
        for (int j = 0; j < numberOfYears*MONTH_PER_YEAR; j++)
        {
            printf("Month : %d - %Lf\n", j, totalPerMonth[j]);       
        }

        for (int j = 0; j < MAX_CATEGORY; j++)
        {
            printf("Category: %d - %Lf\n", j, totalPerCategory[j]);       
        }
        */
        char name[20];
        sprintf(name, "Graph%d.tex", i+NUMBER_OF_YEAR);

        LatexFile *file = new LatexFile(name);
        /*
        file->addFigure(totalPerMonth, numberOfYears*MONTH_PER_YEAR, 10, 1000000000, 0, numberOfYears*MONTH_PER_YEAR, 0, 30000000000, "Mois", "Milliard de lapins", "Evolution du nombre de lapin sur 20ans");

        file->addFigure(totalPerCategory, MAX_CATEGORY, 10, 100000000, 0, MAX_CATEGORY, 0, 1000000000, "Age en mois", "Millions de lapins", "Nombre de lapin dans chaques categories d'age après 20ans");

        long double logTotalPerMonth[numberOfYears*MONTH_PER_YEAR];
        long double sum = 0;
        for (int j = 0; j < numberOfYears*MONTH_PER_YEAR; j++)
        {
            logTotalPerMonth[j] = totalPerMonth[j] > 0 ? log10(totalPerMonth[j]) : 0;
            sum += totalPerMonth[j];
        }
        
        file->addFigure(logTotalPerMonth, numberOfYears*MONTH_PER_YEAR, 10, 1, 0, numberOfYears*MONTH_PER_YEAR, 0, 12, "Mois", "log(nombres de lapins)", "Evolution du nombre de lapin sur 20ans (echelle log)");
        */    
        int nbTranches = 4;
        int totalValid = 0;

        for (int k = 0; k < 5; k++)
        {
            nbTranches *= 2;
            long double resByTranche[nbTranches] = {0};
            long long max = 0;
            unsigned long long maxValue = total*2;
            
            for (int j = 0; j < nbSimu; j++)
            {
                int index = (int) (resSimus[j]/(((float)maxValue)/nbTranches));
                
                if (index < nbTranches && index >= 0) 
                {
                    totalValid++;
                    resByTranche[index]++;
                
                    if (resByTranche[index] > max) 
                    {
                        max = resByTranche[index];
                    }
                }     

                else
                {
                    printf("%d : %Lf (%llu)\n", index, resSimus[j], maxValue);
                }           
                
            }
            
            printf("max = %lld\n", max);

            char titre[200];
            sprintf(titre, "Gaussienne pressision : %d", nbTranches);

            file->addFigure(resByTranche, nbTranches, 1, 100, 0, nbTranches, 0, max + 200, "Nombre de lapins aprés 20ans", "Nombre de simulation", titre);
        }

        printf("Nombre total de resultat valide : %d / %d\n", totalValid, 5*nbSimu);
        file->closeLatex();

        free(resSimus);
    }

    return 0;
}
