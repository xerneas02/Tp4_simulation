#include <fstream>
#include <iostream>
#include <cstring>
#include "latex.h"

int nFig = 0;

char* escapeCharacters(const char* input) {
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

void LatexFile::addSection(const char * section)
{
    file << "\n\\section{" << section << "}\n";
}

void LatexFile::addFigure(long double * data, unsigned long long size, int stepx, int stepy, unsigned long long xmin, unsigned long long xmax, unsigned long long ymin, unsigned long long ymax, const char * xLabel, const char * yLabel, const char * title)
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
        file << "(" << i << "," << data[i] << ")";
    }
    file << "\n};\n";
    

    file << "\\end{axis}\n\\end{tikzpicture}\n\\caption{" << titleTmp << "}\n\\label{fig:figName"<< nFig++ <<"}\n\\end{figure}\n"; 


    free(xLabelTmp);
    free(yLabelTmp);
    free(titleTmp) ;
}

void LatexFile::closeLatex()
{
    file << "\\end{document}";
    file.close();
}