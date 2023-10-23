#ifndef RABBIT_CATEGORY_H

#define RABBIT_CATEGORY_H

class RabbitCategory
{
private:
    int month;   //age in months
    bool gender; //gender of rabbits
    int nbRabbits; //number of rabbits in the category
    double survivalRate; //survival rate

    double getSurvivalRate();

public:
    RabbitCategory(bool gender, int months);
    int getMonths();
    bool getGender();
    int nbAged(); 
    void addRabbits(int nbRabbits);
};

#endif


