#include "main.hpp"
#include "simulation.hpp"

int main()
{
    /*----------Initialisation Mersenne Twister----------*/
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, 
    length=4;
    init_by_array(init, length);
    
    Simulation * sim = new Simulation(5, 5);

    for (int i = 0; i < NUMBER_OF_YEAR*MONTH_PER_YEAR; i++)
    {
        printf("Month : %d - %llu\n", i, sim->getNbRabbits());
        sim->nextMonth();
        /*if (i == 220)
        {
            for (int j = 0; j < MAX_CATEGORY ; j++)
            {
                printf("Category : %d - %llu\n", j, sim->getCategory(j)->getNbRabbits());
            }
            
        }*/
        
    }

    
    

    return 0;
}
