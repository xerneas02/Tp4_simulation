#ifndef RABBIT_CATEGORY_H

#define RABBIT_CATEGORY_H

class RabbitCategory
{
private:
    int month;   //age in months
    int male; //number of male rabbit
    int female; //number of female rabbit
    int nbRabbits; //number of rabbits in the category
    double survivalRate; //survival rate

    double getSurvivalRate();

public:
    RabbitCategory(int month);
    int getMonths();
    bool getGender();
    int getNbRabbits();
    void transferRabbit(); 
    void addRabbits(int male, int female);
};

#endif


