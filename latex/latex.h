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
        void addFigure(long double * data, unsigned long long size, int stepx = 1, int stepy = 1, unsigned long long xmin = 0, unsigned long long xmax = 10, unsigned long long ymin = 0, unsigned long long ymax = 10, const char * xLabel = "x", const char * yLabel = "y", const char * title = "title");
        void closeLatex();
};



#endif // LATEX