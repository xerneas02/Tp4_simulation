#ifndef RABBIT_CATEGORY_H

#define RABBIT_CATEGORY_H

class RabbitCategory
{
private:
    int month;   //age in months
    int male; //number of male rabbit
    int female; //number of female rabbit
    double survivalRate; //survival rate

    double getSurvivalRate();

public:
    RabbitCategory(int month);
    int getMonths();
    int getMale();
    int getFemale();
    int getNbRabbits();
    void transferRabbit(RabbitCategory category); 
    void addRabbits(int male, int female);
};

#endif


