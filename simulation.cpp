#include "simulation.hpp"
#include "rabbitCategory.hpp"
#include  "mt.hpp"
#include <math.h>

/**
 * @brief Constructeur de la classe Simulation.
 *
 * @param nMales Le nombre initial de lapins mâles.
 * @param nFemales Le nombre initial de lapins femelles.
 */
Simulation::Simulation(ull nMales, ull nFemales)
{
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i] = new RabbitCategory(i);
    }

    categories[START_AGE]->setRabbits(nMales, nFemales);

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear[i] = 0;
        femaleNextYear[i] = 0;
    }

    maleStart = nMales;
    femaleStart = nFemales;   
}

/**
 * @brief Réinitialise la simulation.
 *
 * Cette fonction réinitialise tous les paramètres de la simulation à leurs valeurs initiales.
 */
void Simulation::reset()
{
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        categories[i]->setRabbits(0, 0);
    }

    categories[START_AGE]->setRabbits(maleStart, femaleStart);

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        maleNextYear[i] = 0;
        femaleNextYear[i] = 0;
    }
}

/**
 * @brief Passe au mois suivant dans la simulation.
 *
 * Cette fonction simule l'évolution de la population de lapins d'un mois à l'autre.
 */
void Simulation::nextMonth()
{
    if (month == 0)
    {
        nbYears++;
        howManyBabys();
    }

    for (int i = MAX_CATEGORY-2; i >= 0; i--)
    {
        categories[i]->transferRabbit(categories[i+1]);
    } 

    categories[0]->setRabbits(maleNextYear[month], femaleNextYear[month]);

    month = (month + 1) % MONTH_PER_YEAR;
}

/**
 * @brief Obtient le nombre de couples de lapins.
 * 
 * Cette fonction considère qu'il faut au moins 1 mâle pour 10 femelles.
 * Si le nombre de mâles est 10 fois moins que le nombre de femelles, la fonction retourne
 * 10 fois le nombre de mâles; sinon, elle retourne le nombre de femelles.
 *
 * @return Le nombre de couples.
 */
ull Simulation::getNbCouples()
{
    ull females = 0;
    ull males   = 0;
    for (ull i = MAJORITY; i < MAX_CATEGORY; i++)
    {
        females += categories[i]->getFemale();
        males   += categories[i]->getMale();
    }
    males *= 10;

    return females < males ? females : males;
}

 /**
 * @brief Obtient un pointeur vers la catégorie de lapins à l'indice spécifié.
 *
 * @param i L'indice de la catégorie de lapins à récupérer (le mois).
 * @return Un pointeur vers la catégorie de lapins à l'indice spécifié.
 */
RabbitCategory * Simulation::getCategory(ull i)
{
    return categories[i];
}

/**
 * @brief Obtient le nombre total de lapins dans la population.
 *
 * @return Le nombre total de lapins.
 */
ull Simulation::getNbRabbits()
{
    ull rabbits = 0;
    for (ull i = 0; i < MAX_CATEGORY; i++)
    {
        rabbits += categories[i]->getNbRabbits();
    }
    
    
    return rabbits;
}

/**
 * @brief Génère un nombre aléatoire de bébés entre 3 et 6.
 *
 * @return Le nombre de bébés.
 */
ull Simulation::genRandBabys()
{
    return rand_int_uniform(3, 7);

}

/**
 * @brief Génère un nombre aléatoire de portées entre 4 et 8, avec une plus grande probabilité d'avoir 5, 6 ou 7.
 *
 * @return Le nombre de portées.
 */
ull Simulation::genRandLitters()
{
    double r = genrand_real1();

    if (r < 0.125) return 4;
    else if (r < 0.25) return 8;
    return 5 + (r-0.25)/0.25;
}

/**
 * @brief Génère le nombre total de bébés pour l'année suivante et les répartit pour chaque mois.
 */
void Simulation::howManyBabys()
{
    ull couples = getNbCouples();
    ull litters = 0;

    if (couples < MAX_LOOP)
    {
        for (ull i = 0; i < couples; i++)
        {
            litters += genRandLitters();
        }
    }
    else 
    {
        litters = genererGaussienne(couples*6, 380);
    }    

    ull littersPerMonth[MONTH_PER_YEAR];
    for (ull i = 0; i < MONTH_PER_YEAR; i++){
        littersPerMonth[i] = litters/MONTH_PER_YEAR;
    }

    for (ull i = 0; i < litters%MONTH_PER_YEAR; i++){
        littersPerMonth[rand_int_uniform(0, MONTH_PER_YEAR)]++;
    }
     
    ull babys;

    for (ull i = 0; i < MONTH_PER_YEAR; i++)
    {
        babys = 0;
        maleNextYear  [i] = 0;
        femaleNextYear[i] = 0;
        if (littersPerMonth[i] < MAX_LOOP)
        {
            for (ull j = 0; j < littersPerMonth[i]; j++)
            {
                babys += genRandBabys();
                
            }
        }
        else
        {
            babys = genererGaussienne(littersPerMonth[i]*4.5, 330);
        }                
        maleNextYear  [i] += babys/2;
        femaleNextYear[i] += babys/2;
    }
}