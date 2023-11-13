#include <fstream>
#include <iostream>
#include <cstring>
#include "latex.h"

char* escapeCharacters(const char* input) {
    size_t len = strlen(input);
    char* result = (char*)malloc(2 * len + 1);

    if (result == NULL) {
        perror("Allocation de mémoire échouée");
        exit(EXIT_FAILURE);
    }

    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == '%' || input[i] == '\\') {
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
    file << "\\begin{document}\n";
}

void LatexFile::addSection(const char * section)
{
    file << "\n\\section{" << section << "}\n";
}

void LatexFile::addFigure(long double * data, unsigned long long size, int step, const char * xLabel, const char * yLabel, const char * title)
{
    char * xLabelTmp = escapeCharacters(xLabel);
    char * yLabelTmp = escapeCharacters(yLabel);
    char * titleTmp  = escapeCharacters(title) ;
    
    file << "\n\\begin{figure}[htbp]\n";
    file << "\\centering\n";
    file << "\\begin{tikzpicture}";
    file << "\\begin{axis}[\n";
    file << "xlabel={" << xLabelTmp << "},\nylabel={" << yLabelTmp << "},\n";
    file << "title={" << titleTmp << "},\n";
    file << "width=0.8\\textwidth,\nheight=8cm,\n";
    file << "symbolic x coords = {";

    for (long long unsigned i = 0; i < size; i++)
    {
        if (i%step == 0)file << i;
        file << ", ";
    }
    file << "}\nxtick=data,\nybar,\nymin=0,\ngrid=major,\nyticklabel style={\n/pgf/number format/fixed,\n/pgf/number format/precision=3\n},\nenlarge x limits=0.1\n]\n";

    file << "\\addplot[file=blue] coordinates {\n";
    for (long long unsigned i = 0; i < size; i++)
    {
        file << "(" << i << ", " << data[i] << ")\n";
    }

    file << "};\n";

    file << "\\end{axis}\n\\end{tikzpicture}\n\\caption{" << titleTmp << "}\\label{fig:figName}\\end{figure}\n"; 


    free(xLabelTmp);
    free(yLabelTmp);
    free(titleTmp) ;
}

void LatexFile::closeLatex()
{
    file << "\\end{document};";
    file.close();
}