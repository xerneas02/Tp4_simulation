#include "main.hpp"
#include "simulation.hpp"
#include <fstream>
#include <ctime>
#include "math.h"
#include "latex/latex.h"

/**
 * @brief Extrait les deux premiers chiffres d'un nombre entier.
 *
 * Cette fonction prend un nombre entier en paramètre, le convertit en chaîne de caractères,
 * et extrait les deux premiers chiffres. Elle renvoie ces deux premiers chiffres sous forme d'entier.
 *
 * @param nombre Le nombre entier dont on veut extraire les deux premiers chiffres.
 * @return Les deux premiers chiffres du nombre.
 */
int extraireDeuxPremiersChiffres(int nombre) {
    char nombreStr[12];
    sprintf(nombreStr, "%d", nombre);

    nombreStr[2] = '\0';

    int deuxPremiersChiffres = atoi(nombreStr);

    return deuxPremiersChiffres;
}


int main() {
    /*----------Initialisation Mersenne Twister----------*/
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456},
                   length = 4;
    init_by_array(init, length);


    // Initialisation de la simulation avec 5 lapins mâles et 5 lapins femelles.
    Simulation *sim = new Simulation(5, 5);
    long double total = 0;
    int nbSimu = 1000;
    int numberOfYears = NUMBER_OF_YEAR;

    // Boucle principale pour différentes configurations de simulation.
    for (int i = 0; i < 4; i++) {
        if (i != 0)
            numberOfYears *= 2;

        // Allocation dynamique pour stocker les résultats des simulations.
        long double *resSimus = (long double *)malloc(sizeof(long double) * nbSimu);

        // Tableaux pour stocker les résultats par mois et par catégorie.
        long double totalPerMonth[numberOfYears * MONTH_PER_YEAR] = {0};
        long double totalPerCategory[MAX_CATEGORY] = {0};

        // Boucle pour effectuer les simulations.
        for (int j = 0; j < nbSimu; j++) {
            if (j % 100 == 0)
                printf("%d : %d/%d\n", i, j, nbSimu);

            // Simulation de l'évolution de la population sur plusieurs années.
            for (int k = 0; k < numberOfYears * MONTH_PER_YEAR; k++) {
                totalPerMonth[k] += (long double)sim->getNbRabbits() / nbSimu;
                sim->nextMonth();
            }

            // Collecte des résultats par catégorie.
            for (int k = 0; k < MAX_CATEGORY; k++) {
                totalPerCategory[k] += (long double)sim->getCategory(k)->getNbRabbits() / nbSimu;
            }

            // Stockage du nombre total de lapins pour chaque simulation.
            resSimus[j] = sim->getNbRabbits();
            total += (long double)sim->getNbRabbits() / nbSimu;

            // Réinitialisation de la simulation.
            sim->reset();
        }

        // Affichage du nombre moyen de lapins après un certain nombre d'années.
        printf("Nombre de lapin moyen après %d ans : %0.Lf (%0.LfM)\n", numberOfYears, total, total / 1000000000);

        // Création d'un fichier LaTeX pour générer des graphiques.
        char name[20];
        sprintf(name, "Graph%d.tex", numberOfYears);
        LatexFile *file = new LatexFile(name);

        int nbTranches = 4;
        int totalValid = 0;

        // Boucle pour générer des graphiques avec différentes précisions.
        for (int k = 0; k < 6; k++) {
            nbTranches *= 2;
            unsigned long long maxValue = total * 2;

            // Cas spécial pour la dernière itération.
            if (k == 5) {
                nbTranches = extraireDeuxPremiersChiffres(maxValue);
                printf("%d\n", nbTranches);
            }

            // Tableau pour stocker les valeurs de l'axe des x.
            long double x[nbTranches];

            // Remplissage du tableau avec les valeurs de l'axe des x.
            for (int i = 0; i < nbTranches; i++) {
                x[i] = (maxValue / nbTranches) * i;
            }

            // Tableau pour stocker les résultats par tranche.
            long double resByTranche[nbTranches] = {0};
            long long max = 0;

            // Boucle pour compter les occurrences dans chaque tranche.
            for (int j = 0; j < nbSimu; j++) {
                int index = (int)(resSimus[j] / (((float)maxValue) / nbTranches));

                // Vérification des indices valides.
                if (index < nbTranches && index >= 0) {
                    totalValid++;
                    resByTranche[index]++;

                    // Mise à jour de la valeur maximale.
                    if (resByTranche[index] > max) {
                        max = resByTranche[index];
                    }
                } else {
                    printf("%d : %Lf (%llu)\n", index, resSimus[j], maxValue);
                }
            }

            printf("max = %lld\n", max);

            // Création d'un graphique et ajout au fichier LaTeX.
            char titre[200];
            sprintf(titre, "Gaussienne précision : %d", nbTranches);
            char titrex[200];
            sprintf(titrex, "Nombre de lapins après %d ans", numberOfYears);

            file->addFigure(x, resByTranche, nbTranches, maxValue / 10, (max + max * 0.1) / 10, 0, maxValue, 0, max + max * 0.1, titrex, "Nombre de simulations", titre);
        }

        printf("Nombre total de résultats valides : %d\n", totalValid);
        file->closeLatex();

        // Libération de la mémoire allouée dynamiquement.
        free(resSimus);
    }

    return 0;
}
