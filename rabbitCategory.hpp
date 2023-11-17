#ifndef RABBIT_CATEGORY_H

#define RABBIT_CATEGORY_H

#define MAJORITY 8
#define MONTH_PER_YEAR 12
#define MAX_LOOP 10000

#define ull unsigned long long

/**
 * @brief Classe représentant une catégorie de lapins (tous les lapins d'un même âge en mois).
 *
 * Cette classe maintient des informations sur une catégorie spécifique de lapins,
 * tels que l'âge en mois, le nombre de lapins mâles et femelles, le taux de survie,
 * et l'écart type.
 */
class RabbitCategory
{
private:
    ull month;             // Âge en mois
    ull male;              // Nombre de lapins mâles
    ull female;            // Nombre de lapins femelles
    double survivalRate;   // Taux de survie
    double ecartType;      // Écart type

    /**
     * @brief Obtient le taux de survie en fonction de l'âge des lapins de la catégorie.
     *
     * Cette fonction est utilisée pour calculer le taux de survie de la catégorie en
     * se basant sur l'âge des lapins.
     *
     * @return Le taux de survie de la catégorie.
     */
    double getSurvivalRate();

public:
    /**
     * @brief Constructeur de la classe RabbitCategory.
     *
     * @param month L'âge en mois de la catégorie de lapins.
     */
    RabbitCategory(ull month);

    /**
     * @brief Obtient l'âge en mois de la catégorie de lapins.
     *
     * @return L'âge en mois de la catégorie de lapins.
     */
    ull getMonths();

    /**
     * @brief Obtient le nombre de lapins mâles dans la catégorie.
     *
     * @return Le nombre de lapins mâles.
     */
    ull getMale();

    /**
     * @brief Obtient le nombre de lapins femelles dans la catégorie.
     *
     * @return Le nombre de lapins femelles.
     */
    ull getFemale();

    /**
     * @brief Obtient le nombre total de lapins dans la catégorie.
     *
     * @return Le nombre total de lapins (mâles + femelles).
     */
    ull getNbRabbits();

    /**
     * @brief Transfère les lapins qui ont survécu vers la catégorie suivante.
     *
     * @param category La catégorie de lapins vers laquelle transférer les lapins survivants.
     */
    void transferRabbit(RabbitCategory *category);

    /**
     * @brief Définit le nombre de lapins mâles et femelles dans la catégorie.
     *
     * @param male Le nombre de lapins mâles.
     * @param female Le nombre de lapins femelles.
     */
    void setRabbits(ull male, ull female);
};


#endif


