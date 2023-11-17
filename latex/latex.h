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
        void addFigure(long double * dataX, long double * dataY , unsigned long long size, int stepx, int stepy, unsigned long long xmin, unsigned long long xmax, unsigned long long ymin, unsigned long long ymax, const char * xLabel, const char * yLabel, const char * title);
        void closeLatex();
};



#endif // LATEX