#ifndef SIMULATION_H
#define SIMULATION_H

#define MAX_CATEGORY 20*12
#define START_AGE 12

#include "rabbitCategory.hpp"

/**
 * @class Simulation
 * @brief Classe représentant une simulation de population de lapins.
 *
 * La classe Simulation gère la simulation de l'évolution d'une population de lapins
 * en fonction de différentes catégories d'âge et de genres. Elle maintient des informations
 * telles que le nombre de lapins mâles et femelles pour chaque mois, le nombre total de lapins,
 * l'écart type, etc.
 */
class Simulation
{
private:
    ull maleNextYear[MONTH_PER_YEAR];        // Nombre de lapins mâles pour l'année suivante (par mois)
    ull femaleNextYear[MONTH_PER_YEAR];      // Nombre de lapins femelles pour l'année suivante (par mois)
    ull nbYears;                             // Nombre d'années de simulation
    ull month;                               // Mois actuel
    ull nbRabbits;                           // Nombre total de lapins

    ull maleStart;                           // Nombre initial de lapins mâles
    ull femaleStart;                         // Nombre initial de lapins femelles

    RabbitCategory *categories[MAX_CATEGORY]; // Tableau de pointeurs vers des objets RabbitCategory

    /**
     * @brief Obtient le nombre de couples de lapins.
     * 
     * Cette fonction considère qu'il faut au moins 1 mâle pour 10 femelles.
     * Si le nombre de mâles est 10 fois moins que le nombre de femelles, la fonction retourne
     * 10 fois le nombre de mâles; sinon, elle retourne le nombre de femelles.
     *
     * @return Le nombre de couples.
     */
    ull getNbCouples();

    /**
     * @brief Génère un nombre aléatoire de bébés entre 3 et 6.
     *
     * @return Le nombre de bébés.
     */
    ull genRandBabys();

    /**
     * @brief Génère un nombre aléatoire de portées entre 4 et 8, avec une plus grande probabilité d'avoir 5, 6 ou 7.
     *
     * @return Le nombre de portées.
     */
    ull genRandLitters();

    /**
     * @brief Génère le nombre total de bébés pour l'année suivante et les répartit pour chaque mois.
     */
    void howManyBabys();

public:
    /**
     * @brief Constructeur de la classe Simulation.
     *
     * @param nMales Le nombre initial de lapins mâles.
     * @param nFemales Le nombre initial de lapins femelles.
     */
    Simulation(ull nMales, ull nFemales);

    /**
     * @brief Réinitialise la simulation.
     *
     * Cette fonction réinitialise tous les paramètres de la simulation à leurs valeurs initiales.
     */
    void reset();

    /**
     * @brief Passe au mois suivant dans la simulation.
     *
     * Cette fonction simule l'évolution de la population de lapins d'un mois à l'autre.
     */
    void nextMonth();

    /**
     * @brief Obtient le nombre total de lapins dans la population.
     *
     * @return Le nombre total de lapins.
     */
    ull getNbRabbits();

    /**
     * @brief Obtient un pointeur vers la catégorie de lapins à l'indice spécifié.
     *
     * @param i L'indice de la catégorie de lapins à récupérer (le mois).
     * @return Un pointeur vers la catégorie de lapins à l'indice spécifié.
     */
    RabbitCategory *getCategory(ull i);
};


#endif