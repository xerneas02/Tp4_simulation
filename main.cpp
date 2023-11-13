#include "main.hpp"
#include "simulation.hpp"
#include <ctime>

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

    for (int j = 0; j < nbSimu; j++)
    {
        printf("%d/%d\n", j, nbSimu);
        for (int i = 0; i < NUMBER_OF_YEAR*MONTH_PER_YEAR; i++)
        {
            //printf("Month : %d - %llu\n", i, sim->getNbRabbits());
            sim->nextMonth();        
        }
        total += (long double)sim->getNbRabbits()/nbSimu;

        sim->reset();
    }

    printf("Nombre de lapin moyen apres %dans : %0.Lf (%0.LfM)\n", NUMBER_OF_YEAR, total, total/1000000000);

    
    

    return 0;
}
