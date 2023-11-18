#ifndef LATEX_H
#define LATEX_H

#include <fstream>

/**
 * @brief Classe représentant un fichier LaTeX pour générer des documents avec des graphiques.
 */
class LatexFile
{
private:
    std::ofstream file; ///< Flux de sortie pour écrire dans le fichier LaTeX.
    int nFig = 0; ///< Numero de la figure actuel

    /**
     * @brief Échappe certains caractères spéciaux dans une chaîne de caractères.
     *
     * Cette fonction prend en entrée une chaîne de caractères et retourne une nouvelle chaîne
     * dans laquelle certains caractères spéciaux tels que '%', '\', '_', '^', ''', et '"' sont échappés
     * avec un caractère '\' pour éviter toute interprétation spéciale dans un contexte particulier.
     *
     * @param input La chaîne de caractères d'origine.
     * @return Une nouvelle chaîne de caractères avec les caractères spéciaux échappés.
     */
    char* escapeCharacters(const char* input);

public:
    /**
     * @brief Constructeur de la classe LatexFile.
     *
     * @param filename Nom du fichier LaTeX à créer.
     */
    LatexFile(const char *filename);

    /**
     * @brief Ajoute une section au fichier LaTeX.
     *
     * @param section Nom de la section à ajouter.
     */
    void addSection(const char *section);

    /**
     * @brief Ajoute un graphique au fichier LaTeX.
     *
     * @param dataX Tableau de données pour l'axe des x.
     * @param dataY Tableau de données pour l'axe des y.
     * @param size Taille des tableaux de données.
     * @param stepx Pas pour l'axe des x.
     * @param stepy Pas pour l'axe des y.
     * @param xmin Valeur minimale de l'axe des x.
     * @param xmax Valeur maximale de l'axe des x.
     * @param ymin Valeur minimale de l'axe des y.
     * @param ymax Valeur maximale de l'axe des y.
     * @param xLabel Étiquette de l'axe des x.
     * @param yLabel Étiquette de l'axe des y.
     * @param title Titre du graphique.
     */
    void addFigure(long double *dataX, long double *dataY, unsigned long long size, int stepx = 1, int stepy = 1, unsigned long long xmin = 0, unsigned long long xmax = 10, unsigned long long ymin = 0, unsigned long long ymax = 10, const char *xLabel = "x", const char *yLabel = "y", const char *title = "");

    /**
     * @brief Ferme le fichier LaTeX.
     */
    void closeLatex();
};

#endif // LATEX_H
