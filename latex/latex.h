#ifndef LATEX_H
#define LATEX_H
#include <fstream>

class LatexFile
{
    private:
        std::ofstream file;

    public:
        LatexFile(const char * filename);
        void addSection(const char * section);
        void addFigure(long double * data, unsigned long long size, int step = 1, const char * xLabel = "x", const char * yLabel = "y", const char * title = "title");
        void closeLatex();
};



#endif // LATEX