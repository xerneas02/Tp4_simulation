#include <fstream>
#include <iostream>
#include <cstring>
#include "latex.h"

/**
 * @brief Constructeur de la classe LatexFile.
 *
 * @param filename Nom du fichier LaTeX à créer.
 */
LatexFile::LatexFile(const char *filename)
{
    file.open(filename);

    file << "\\documentclass{article}\n";
    file << "\\usepackage{graphicx}\n";
    file << "\\usepackage{pgf, tikz}\n";
    file << "\\usepackage[margin=0.25in]{geometry}\n";
    file << "\\usepackage{pgfplots}\n";
    file << "\\pgfplotsset{width=10cm,compat=1.9}\n";

    file << "\\usepgfplotslibrary{external}\n";
    file << "\\tikzexternalize\n";

    file << "\\begin{document}\n";
}

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
char* LatexFile::escapeCharacters(const char* input) {
    size_t len = strlen(input);
    char* result = (char*)malloc(2 * len + 1);

    if (result == NULL) {
        perror("Allocation de mémoire échouée");
        exit(EXIT_FAILURE);
    }

    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == '%' || input[i] == '\\' || input[i] == '_' || input[i] == '^' || input[i] == '\'' || input[i] == '"') {
            result[j++] = '\\';
        }
        result[j++] = input[i];
    }

    result[j] = '\0';

    return result;
}

/**
 * @brief Ajoute une section au fichier LaTeX.
 *
 * @param section Nom de la section à ajouter.
 */
void LatexFile::addSection(const char * section)
{
    file << "\n\\section{" << section << "}\n";
}

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
void LatexFile::addFigure(long double * dataX, long double * dataY , unsigned long long size, int stepx, int stepy, unsigned long long xmin, unsigned long long xmax, unsigned long long ymin, unsigned long long ymax, const char * xLabel, const char * yLabel, const char * title)
{
    char * xLabelTmp = escapeCharacters(xLabel);
    char * yLabelTmp = escapeCharacters(yLabel);
    char * titleTmp  = escapeCharacters(title) ;
    
    file << "\n\\begin{figure}[htbp]\n";
    file << "\\centering\n";
    file << "\\begin{tikzpicture}\n";
    file << "\\begin{axis}[\n";
    file << "title={" << titleTmp << "},\n";
    file << "xlabel={" << xLabelTmp << "},\n";
    file << "ylabel={" << yLabelTmp << "},\n";
    file << "xmin=" << xmin << ", xmax=" << xmax << ",\n";
    file << "ymin=" << ymin << ", ymax=" << ymax << ",\n";
    file << "xticks={";
    file << 0;
    for (unsigned long long i = 1; i < xmax/stepx; i++)
    {
        file << "," << i*stepx ;
    }
    file << "},\n";

    file << "yticks={";
    file << 0 ;
    for (unsigned long long i = 1; i < ymax/stepy; i++)
    {
        file << "," << i*stepy;
    }
    file << "},\n";

    file << "legend pos=north west,\nymajorgrids=true,\ngrid style=dashed,\n]\n\n";

    file << "\\addplot[color=blue, line width=3pt,]\n";

    file << "coordinates {\n";
    for (unsigned long long i = 0; i < size; i++)
    {
        file << "(" << dataX[i] << "," << dataY[i] << ")";
    }
    file << "\n};\n";
    

    file << "\\end{axis}\n\\end{tikzpicture}\n\\caption{" << titleTmp << "}\n\\label{fig:figName"<< nFig++ <<"}\n\\end{figure}\n"; 


    free(xLabelTmp);
    free(yLabelTmp);
    free(titleTmp) ;
}

/**
 * @brief Ferme le fichier LaTeX.
 */
void LatexFile::closeLatex()
{
    file << "\\end{document}";
    file.close();
}