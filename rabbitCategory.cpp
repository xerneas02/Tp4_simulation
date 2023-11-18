#include <iostream>
#include "rabbitCategory.hpp"
#include "mt.hpp"
#include <math.h>

/**
 * @brief Constructeur de la classe RabbitCategory.
 *
 * @param month L'âge en mois de la catégorie de lapins.
 */
RabbitCategory::RabbitCategory(ull month) : 
    month(month)
{
    survivalRate = getSurvivalRate();
    male   = 0;
    female = 0;

    ecartType = 140;
}

/**
 * @brief Obtient le taux de survie en fonction de l'âge des lapins de la catégorie.
 *
 * Cette fonction est utilisée pour calculer le taux de survie de la catégorie en
 * se basant sur l'âge des lapins.
 *
 * @return Le taux de survie de la catégorie.
 */
double RabbitCategory::getSurvivalRate()
{
    if (getMonths() < MAJORITY)
        return pow(0.35, 1.0/MAJORITY); 
    else if (getMonths() < MONTH_PER_YEAR * 10)
        return pow(0.6, 1.0/MONTH_PER_YEAR);
    else if(getMonths() < MONTH_PER_YEAR * 15)
        return pow(0.6 - 0.1 * (15 - ((float)month)/MONTH_PER_YEAR), 1.0/MONTH_PER_YEAR);
    return 0.0;
}

/**
 * @brief Définit le nombre de lapins mâles et femelles dans la catégorie.
 *
 * @param male Le nombre de lapins mâles.
 * @param female Le nombre de lapins femelles.
 */
void RabbitCategory::setRabbits(ull male, ull female)
{
    this->male = male;
    this->female = female;
}

/**
 * @brief Transfère les lapins qui ont survécu vers la catégorie suivante.
 *
 * @param category La catégorie de lapins vers laquelle transférer les lapins survivants.
 */
void RabbitCategory::transferRabbit(RabbitCategory * category)
{
    ull maleTemp = 0; ull femaleTemp = 0;   
    double variances = (survivalRate - survivalRate*survivalRate); 
    
    if (male < MAX_LOOP) 
    {
        for (ull i = 0; i < male; i++)
        {
            maleTemp += (genrand_real1() < survivalRate);
        }
    }
    else
    {
        maleTemp = genererGaussienne(male*survivalRate, sqrt(male*variances));
    }
    

    if (female < MAX_LOOP) 
    {
        for (ull i = 0; i < female; i++)
        {
            femaleTemp += (genrand_real1() < survivalRate);
        }
    }
    else
    {
        femaleTemp = genererGaussienne(female*survivalRate, sqrt(female*variances));
    }

    category->setRabbits(maleTemp, femaleTemp);

    male = 0;
    female = 0;
}

/**
 * @brief Obtient l'âge en mois de la catégorie de lapins.
 *
 * @return L'âge en mois de la catégorie de lapins.
 */
ull RabbitCategory::getMonths()
{
    return month;
}

/**
 * @brief Obtient le nombre de lapins mâles dans la catégorie.
 *
 * @return Le nombre de lapins mâles.
 */
ull RabbitCategory::getMale()
{
    return male;
}

/**
 * @brief Obtient le nombre de lapins femelles dans la catégorie.
 *
 * @return Le nombre de lapins femelles.
 */
ull RabbitCategory::getFemale()
{
    return female;
}

/**
 * @brief Obtient le nombre total de lapins dans la catégorie.
 *
 * @return Le nombre total de lapins (mâles + femelles).
 */
ull RabbitCategory::getNbRabbits()
{
    return male + female;
}


